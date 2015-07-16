#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "AgendaService.h"
/*
server recive socket  command message in a json format string like:
{"name":"xxxx","password":"xxxxx","op":"xx","participator":"xxxx","title":"xxx",
"startDate":"xxxx","endDate":"xxxx","email":"xxxxx","phone":"xxxx"}
*/
std::string name,password,op,participator,title,startDate,endDate,email,phone;
AgendaService as;
void cmdExplainer(std::string cmd_message){
	std::stringstream ss;
	ss<<cmd_message;
	using namespace boost::property_tree;
	ptree pt;
	read_json<ptree>(ss,pt);
	name=pt.get<std::string>("name");
	password=pt.get<std::string>("password");
	op=pt.get<std::string>("op");
	participator=pt.get<std::string>("participator");
	title=pt.get<std::string>("title");
	startDate=pt.get<std::string>("startDate");
	endDate=pt.get<std::string>("endDate");
	email=pt.get<std::string>("email");
	phone=pt.get<std::string>("phone");
}


/*
server send result message in a json format string like:
x:0 or 1
{"opResult":x,"meetingResult":"[{Meeting1},{Meeting2},{Meeting3}....]",
"userResult":[{User1},{User2}...]}

Meeting is like:
{"sponsor":"xxxx","participator":"xxxxx","startDate":"xxxx","endDate":"xxxxxx","title":"xxxxx"}

User is like:(no psd for safty!)
{"name":"xxxx",email:"xxxxx","phone":"xxxxx"}
*/
 std::string resultPacker(bool opResult,std::list<Meeting> meetingList, std::list<User> userList){
 	std::string message("");
 	//opResult
 	message+="{\"opResult\":";
 	if(opResult){
 		message+="1";
 	}
 	else{
 		message+="0";
 	}
 	//meetingResult
 	message+=",\"meetingResult\":[";

 	if(!meetingList.empty()){
 		bool firstFlag=0;
 		std::list<Meeting>::iterator it;
	 	for(it=meetingList.begin();it!=meetingList.end();++it){
	 		if(firstFlag==0){
	 			firstFlag=1;
	 		}
	 		else{
	 			message+=",";
	 		}
	 		message+="{\"sponsor\":\"";
	 		message+=it->getSponsor();
	 		message+="\",";

	 		message+="\"participator\":\"";
	 		message+=it->getParticipator();
	 		message+="\",";

	 		message+="\"startDate\":\"";
	 		message+=Date::dateToString(it->getStartDate());
	 		message+="\",";

	 		message+="\"endDate\":\"";
	 		message+=Date::dateToString(it->getEndDate());
	 		message+="\",";

	 		message+="\"title\":\"";
	 		message+=it->getTitle();
	 		message+="\"}";
	 	}
 	}
 	message+="],";

	//userResult
	message+="\"userResult\":[";
	if(!userList.empty()){
		std::cout<<"ULsize: "<<userList.size()<<std::endl;
		std::list<User>::iterator it2;
		bool firstFlag=0;
	 	for(it2=userList.begin();it2!=userList.end();++it2){
	 		if(firstFlag==0){
	 			firstFlag=1;
	 		}
	 		else{
	 			message+=",";
	 		}
	 		message+="{\"name\":\"";
	 		message+=it2->getName();
	 		message+="\",";

	 		message+="\"email\":\"";
	 		message+=it2->getEmail();
	 		message+="\",";

	 		message+="\"phone\":\"";
	 		message+=it2->getPhone();
	 		message+="\"}";
 		}
	}
 	message+="]}";
	return message;
 }
 std::string excuteAndGetMessage(){
 	bool opResult=false;
 	std::list<Meeting> meetingList;
 	std::list<User> userList;
 	meetingList.clear();
 	userList.clear();
 	if (op == "l") {
		opResult=as.userLogIn(name,password);
		if(opResult)
			meetingList=as.listAllMeetings(name);
	}
	else if (op == "r") {
		opResult=as.userRegister(name,password,email,phone);
	}
	else if (op == "q") {
		as.quitAgenda();
		op=true;
	}
	else if (op == "dc") {
		opResult=as.deleteUser(name,password);
	}
	else if (op == "lu") {
		opResult=true;
		userList=as.listAllUsers();
	}
	else if (op == "cm") {
		opResult=as.createMeeting(name,title,participator,startDate,endDate);
	}
	else if (op == "la") {
		meetingList=as.listAllMeetings(name);
		opResult=true;
	}
	else if (op == "las") {
		meetingList=as.listAllSponsorMeetings(name);
		opResult= true;
	}
	else if (op == "lap") {
		meetingList=as.listAllParticipateMeetings(name);
		opResult= true;
	}
	else if (op == "qm") {
		meetingList=as.meetingQuery(title);
		opResult=true;
	}
	else if (op == "qt") {
		opResult=true;
		meetingList=as.meetingQuery(name,startDate,endDate);
	}
	else if (op == "dm") {
		opResult=as.deleteMeeting(name,title);
	}
	else if (op == "da") {
		opResult=as.deleteAllMeetings(name);
	}
	else if (op == "o") {

	}
	else if (op == "q") {
		as.quitAgenda();
		opResult=true;
	}
	return resultPacker(opResult, meetingList,userList);
 }
using namespace boost;
using boost::asio::ip::tcp;
 int main(){
 	
 	asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 3200));
	as.startAgenda();
	std::cout<<"[Agenda Server is running!]\nHave Fun!\n\n";
	while(1){
		name="";
		password="";
		op="";
		participator="";
		title="";
		startDate="";
		endDate="";
		email="";
		phone="";
		system::error_code ignored_error;
		system::error_code error;
		boost::array<char,1000> buf;
		tcp::socket socket(io_service);
		acceptor.accept(socket);

		size_t len=socket.read_some(boost::asio::buffer(buf), error);
		std::string recive(buf.data(),len);
		std::cout<<"[system] recived commad:("<<recive<<") len:("<<len<<")\n\n";
		cmdExplainer(recive);
		std::string message(excuteAndGetMessage());
		std::cout<<"[system] send message:("<<message<<")\n\n";
		socket.write_some(asio::buffer(message), ignored_error);
	}
	as.quitAgenda();
 }