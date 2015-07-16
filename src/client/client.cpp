#include "client.h"

/*
client send socket  command message in a json format string like:

{"name":"xxxx","password":"xxxxx","op":"xx","participator":"xxxx","title":"xxx",
"startDate":"xxxx","endDate":"xxxx","email":"xxxxx","phone":"xxxx"}
*/

string cmdPacker(string name,string password,string op,string participator,string title,
	string startDate,string endDate,string email,string phone){
	string cmd("");
	cmd+="{";

	cmd+="\"name\":\"";
	cmd+=name;
	cmd+="\",";

	cmd+="\"password\":\"";
	cmd+=password;
	cmd+="\",";

	cmd+="\"op\":\"";
	cmd+=op;
	cmd+="\",";

	cmd+="\"participator\":\"";
	cmd+=participator;
	cmd+="\",";

	cmd+="\"title\":\"";
	cmd+=title;
	cmd+="\",";

	cmd+="\"startDate\":\"";
	cmd+=startDate;
	cmd+="\",";

	cmd+="\"endDate\":\"";
	cmd+=endDate;
	cmd+="\",";

	cmd+="\"email\":\"";
	cmd+=email;
	cmd+="\",";

	cmd+="\"phone\":\"";
	cmd+=phone;
	cmd+="\"";

	cmd+="}";
	return cmd;
}
/*
client recive result message in a json format string like:
x:0 or 1
{"opResult":x,"meetingResult":"[{Meeting1},{Meeting2},{Meeting3}....]",
"userResult":[{User1},{User2}...]}

Meeting is like:
{"sponsor":"xxxx","participator":"xxxxx","startDate":"xxxx","endDate":"xxxxxx","title":"xxxxx"}

User is like:(no psd for safty!)
{"name":"xxxx",email:"xxxxx","phone":"xxxxx"}
*/

Msg messageExplainer(string message){
	stringstream ss;
	ss<<message;
	using namespace boost::property_tree;
	ptree pt,meetingPt,userPt;
	//cout<<"asdasd"<<endl;
	read_json<ptree>(ss,pt);
	//cout<<"sad"<<endl;
	Msg msg;
	msg.opResult=pt.get<int>("opResult");
	//cout<<"opResult:"<<msg.opResult<<endl;
	//Meeting 
	meetingPt=pt.get_child("meetingResult");
	for(ptree::iterator it=meetingPt.begin();it!=meetingPt.end();++it){
		ptree mpt;
		mpt=it->second;
		string sponsor,participator,startDate,endDate,title;
		sponsor=mpt.get<string>("sponsor");
		participator=mpt.get<string>("participator");
		startDate=mpt.get<string>("startDate");
		endDate=mpt.get<string>("endDate");
		title=mpt.get<string>("title");

		//cout<<"M:"<<sponsor<<"  "<<participator<<"  "<<startDate;
		//cout<<"  "<<endDate<<"  "<<title<<endl; 
		msg.meetingList.push_back(Meeting(sponsor,participator,
			Date::stringToDate(startDate),Date::stringToDate(endDate),title));
	}
	//User
	userPt=pt.get_child("userResult");
	for(ptree::iterator it=userPt.begin();it!=userPt.end();++it){
		ptree upt;
		upt=it->second;
		string name,email,phone;
		name=upt.get<string>("name");
		email=upt.get<string>("email");
		phone=upt.get<string>("phone");
		//cout<<"U:"<<name<<"  "<<email<<"  "<<phone<<endl;
		msg.userList.push_back(User(name,"",email,phone));
	}
	return msg;
}
using namespace boost;
using boost::asio::ip::tcp;
string communicateWithServer(string cmd){
	boost::asio::io_service io_service;
	tcp::socket socket(io_service);
	tcp::endpoint end_point(boost::asio::ip::address::from_string("127.0.0.1"), 3200);
	socket.connect(end_point);
	std::array<char, 1000> buf;
	boost::system::error_code error;
	system::error_code ignored_error;

	socket.write_some(asio::buffer(cmd), error);
	size_t len = socket.read_some(boost::asio::buffer(buf), error);
	string msg(buf.data(),len);
	return msg;
}

Msg sendAndGet(string name,string password,string op,string participator,string title,
	string startDate,string endDate,string email,string phone){

	string cmd("");
	cmd=cmdPacker(name,password,op,participator,title,startDate,endDate,email,phone);
	string msgStr("");
	//cout<<"[system]"<<"sending: "<<cmd<<endl;
	msgStr=communicateWithServer(cmd);
	//cout<<"[system]"<<"recived: "<<msgStr<<endl;
	Msg msg=messageExplainer(msgStr);
	return msg;
}
/*
//client Test
main(){
	while(1){
		string message;
		cin>>message;
		Msg msg;
		msg=messageExplainer(message);
		cout<<"Explained:"<<endl;
		cout<<"opResult:"<<msg.opResult<<endl;
		cout<<"Meeting:"<<endl;
		for(list<Meeting>::iterator it=msg.meetingList.begin();it!=msg.meetingList.end();++it){
			cout<<it->getTitle()<<endl;
		}
		cout<<"User:"<<endl;
		for(list<User>::iterator it=msg.userList.begin();it!=msg.userList.end();++it){
			cout<<it->getName()<<endl;
		}

	}
}
*/
