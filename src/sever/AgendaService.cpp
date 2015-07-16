// Copyright @2014KenLee
#include "AgendaService.h"
#include <iostream>
using std::list;
using std::string;

AgendaService::AgendaService() {
	storage_=Storage::getInstance();
}
AgendaService::~AgendaService() {
	delete storage_;
}
//使用匿名函数体
bool AgendaService::userLogIn(std::string userName, std::string password) {
	
	list<User> cUserList=storage_->queryUser([&](const User &user){
		if(user.getName()==userName && user.getPassword()== password)
			return true;
		return false;
	});
	if(cUserList.empty())
		return false;
	else
		return true;

}
//如果已经有同名的User的话直接返回false
bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
	User newUser(userName,password,email,phone);
	if(storage_->queryUser([&](const User &user){
		if(user.getName()==userName)
			return true;
		return false;
	}).empty()){//没有重名的User
		storage_->createUser(newUser);
		return true;
	}
	return false;
}
//有meeting的话不能删
bool AgendaService::deleteUser(std::string userName, std::string password) {
	if(this->listAllMeetings(userName).empty()){
		std::cout<<"deleting: "<<userName<<"  "<<password<<std::endl;
		return storage_->deleteUser([&](const User user){
			if(user.getName()==userName && user.getPassword()==password)
				return true;
			return false;
		});
	}
	else
		return false;
}
std::list<User> AgendaService::listAllUsers(void) {
	return storage_->queryUser([&](const User user){
		return true;
	});
}
bool AgendaService::createMeeting(std::string userName, std::string title,std::string participator,std::string startDate, std::string endDate){
	//如果查找user和参与者的查找出来list长度不为2的话,说明有用户不存在或者参与者重名
	if(storage_->queryUser([&](const User user){
		if(user.getName()==userName || user.getName()==participator)
			return true;
		return false;
	}).size()!=2)
		return false;
	//如果已经有同名的会议
	if(!this->meetingQuery(title).empty())
		return false;
	//如果时间不合法
	Date sDate=Date::stringToDate(startDate);
	Date eDate=Date::stringToDate(endDate);
	if(sDate>eDate || !Date::isValid(sDate) || !Date::isValid(eDate))
		return false;
	//创建会议
	storage_->createMeeting(Meeting(userName,participator,sDate,eDate,title));
	return true;
}
std::list<Meeting> AgendaService::meetingQuery(std::string title) {
	return storage_->queryMeeting([&](const Meeting meeting){
		if (meeting.getTitle()==title)
			return true;
		else
			return false;
	});
}
std::list<Meeting> AgendaService::meetingQuery(std::string userName, std::string startDate,std::string endDate) {
	Date sDate=Date::stringToDate(startDate);
	Date eDate=Date::stringToDate(endDate);
	return storage_->queryMeeting([&](const Meeting meeting){
		if(sDate<meeting.getEndDate() && meeting.getStartDate()<eDate &&
			(meeting.getSponsor()==userName || meeting.getParticipator()==userName))
			return true;
		else
			return false;
	});
}
std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
	return storage_->queryMeeting([&](const Meeting meeting){
		if(meeting.getSponsor()==userName || meeting.getParticipator()==userName)
			return true;
		else
			return false;
	});
}
std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
	return storage_->queryMeeting([&](const Meeting meeting){
		if(meeting.getSponsor()==userName)
			return true;
		else
			return false;
	});
}
std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string userName) {
	return storage_->queryMeeting([&](const Meeting meeting){
		if(meeting.getParticipator()==userName)
			return true;
		else
			return false;
	});
}
bool AgendaService::deleteMeeting(std::string userName, std::string title) {
	//如果没有这个User
	if (storage_->queryUser([&](const User user){
			return user.getName()==userName;
	}).empty())
		return false;
	//删除
	return storage_->deleteMeeting([&](const Meeting meeting){
		if(meeting.getSponsor()==userName && meeting.getTitle()==title)
			return true;
		else
			return false;
	});
}
bool AgendaService::deleteAllMeetings(std::string userName) {
	//没有这个用户
	if (storage_->queryUser([&](const User user){
		return user.getName()==userName;
	}).empty())
		return false;

	return storage_->deleteMeeting([&](const Meeting meeting){
		if(meeting.getSponsor()==userName)
			return true;
		else
			return false;
	});
}

void AgendaService::startAgenda(void) {
	
}
void AgendaService::quitAgenda(void) {
	storage_->sync();
}
