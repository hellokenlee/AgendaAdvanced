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
//ʹ������������
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
//����Ѿ���ͬ����User�Ļ�ֱ�ӷ���false
bool AgendaService::userRegister(std::string userName, std::string password,std::string email, std::string phone) {
	User newUser(userName,password,email,phone);
	if(storage_->queryUser([&](const User &user){
		if(user.getName()==userName)
			return true;
		return false;
	}).empty()){//û��������User
		storage_->createUser(newUser);
		return true;
	}
	return false;
}
//��meeting�Ļ�����ɾ
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
	//�������user�Ͳ����ߵĲ��ҳ���list���Ȳ�Ϊ2�Ļ�,˵�����û������ڻ��߲���������
	if(storage_->queryUser([&](const User user){
		if(user.getName()==userName || user.getName()==participator)
			return true;
		return false;
	}).size()!=2)
		return false;
	//����Ѿ���ͬ���Ļ���
	if(!this->meetingQuery(title).empty())
		return false;
	//���ʱ�䲻�Ϸ�
	Date sDate=Date::stringToDate(startDate);
	Date eDate=Date::stringToDate(endDate);
	if(sDate>eDate || !Date::isValid(sDate) || !Date::isValid(eDate))
		return false;
	//��������
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
	//���û�����User
	if (storage_->queryUser([&](const User user){
			return user.getName()==userName;
	}).empty())
		return false;
	//ɾ��
	return storage_->deleteMeeting([&](const Meeting meeting){
		if(meeting.getSponsor()==userName && meeting.getTitle()==title)
			return true;
		else
			return false;
	});
}
bool AgendaService::deleteAllMeetings(std::string userName) {
	//û������û�
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
