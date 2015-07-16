#include "Storage.h"
Storage *Storage::instance_ = nullptr;

Storage::Storage() {
	if (readFromFile("agenda.data") == false) {
		userList_.clear();
		meetingList_.clear();
	}
}

Storage* Storage::getInstance(void) {
	if (!instance_) {
		instance_ = new Storage();
	}
	return instance_;
}

Storage::~Storage() {
	writeToFile("agenda.data");
}

bool Storage::sync(void) {
	return writeToFile("agenda.data");
}

void Storage::createUser(const User& user_) {
	userList_.push_back(user_);
	sync();
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
	std::list<User> v;
	for (auto i : userList_) {
		if (filter(i))
			v.push_back(i);
	}
	return v;
}

int Storage::updateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
	int result = 0;
	for (auto i : userList_) {
		if (filter(i)) {
			switcher(i);
			result++;
		}
	}
	sync();
	return result;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
	int result = 0;
	for (auto i = userList_.begin(); i != userList_.end();) {
		if (filter(*i)) {
			userList_.erase(i++);
			result++;
		}
	else
		++i;
	}
	sync();
	return result;
}

void Storage::createMeeting(const Meeting& meeting_) {
	meetingList_.push_back(meeting_);
	sync();
}

std::list<Meeting> Storage::queryMeeting(std::function<bool(const Meeting&)> filter) {
	std::list<Meeting> v;
	for (auto i : meetingList_) {
		if (filter(i))
			v.push_back(i);
	}
	return v;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
	int result = 0;
	for (auto i : meetingList_) {
		if (filter(i)) {
			switcher(i);
			result++;
		}
	}
	sync();
	return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)> filter) {
	int result = 0;
	for (auto i = meetingList_.begin(); i != meetingList_.end();) {
		if (filter(*i)) {
			meetingList_.erase(i++);
			result++;
		}
		else
		{
			++i;
		}
	}
	sync();
	return result;
}
using namespace std;
bool Storage::readFromFile(const char *filename) {
	std::ifstream fin(filename);
	if(!fin.good()){
		return false;
	}
	using namespace boost::property_tree;
	std::string raw_str;
	//read each collection's name and their value
	while(fin>>raw_str){
		ptree pt;
		std::stringstream ss;
		std:string collection;
		ss<<raw_str;
		read_json<ptree>(ss,pt);
		collection = pt.get<std::string>("collection");
		int total = pt.get<int>("total");
		if(collection=="User"){
			for(int i=0;i<total;++i){
				fin>>raw_str;
				std::stringstream s;
				s<<raw_str;
				ptree p;
				read_json<ptree>(s,p);
				std::string name=p.get<std::string>("name");
				std::string pwd=p.get<std::string>("password");
				std::string email=p.get<std::string>("email");
				std::string phone=p.get<string>("phone");
				userList_.push_back(User(name,pwd,email,phone));
			}
		}
		if(collection=="Meeting"){
			for(int i=0;i<total;++i){
				fin>>raw_str;
				std::stringstream s;
				s<<raw_str;
				ptree p;
				read_json<ptree>(s,p);
				std::string sponsor=p.get<std::string>("sponsor");
				std::string participator=p.get<std::string>("participator");
				std::string sdate=p.get<std::string>("sdate");
				std::string edate=p.get<std::string>("edate");
				std::string title=p.get<std::string>("title");
				meetingList_.push_back(Meeting(sponsor,participator,
					Date::stringToDate(sdate),Date::stringToDate(edate),title));
			}
		}
	}
	return true;
}

bool Storage::writeToFile(const char *filename) {
	std::ofstream fout(filename);
	if (!fout.good())
		return false;
	fout << "{\"collection\":\"User\",\"total\":" << userList_.size() << "}" << std::endl;
	for (auto user : userList_) {
		fout << "{";
		fout << "\"name\":\"" << user.getName() << "\",";
		fout << "\"password\":\"" << user.getPassword() << "\",";
		fout << "\"email\":\"" << user.getEmail() << "\",";
		fout << "\"phone\":\"" << user.getPhone() << "\"";
		fout << "}" << std::endl;
	}
	fout << "{\"collection\":\"Meeting\",\"total\":" << meetingList_.size() << "}" << std::endl;
	for (auto meeting : meetingList_) {
		fout << "{";
		fout << "\"sponsor\":\"" << meeting.getSponsor() << "\",";
		fout << "\"participator\":\"" << meeting.getParticipator() << "\",";
		fout << "\"sdate\":\"" << Date::dateToString(meeting.getStartDate()) << "\",";
		fout << "\"edate\":\"" << Date::dateToString(meeting.getEndDate()) << "\",";
		fout << "\"title\":\"" << meeting.getTitle() << "\"";
		fout << "}" << std::endl;
	}
	return true;
}


