#ifndef CLIENT_H
#define CLIENT_H
#define WIN32_LEAN_AND_MEAN
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Meeting.h"
#include "User.h"
#include <boost/asio.hpp>
using namespace std;
//Message dataStructures
struct Msg
{	
	list<Meeting> meetingList;
	list<User> userList;
	bool opResult;
	Msg(){
		meetingList.clear();
		userList.clear();
		opResult=false;
	}
	Msg(list<Meeting> meetingList_, list<User> userList_,bool opResult_){
		meetingList=meetingList_;
		userList=userList_;
		opResult=opResult_;
	}
};


string cmdPacker(string name,string password,string op,string participator,string title,
	string startDate,string endDate,string email,string phone);

Msg messageExplainer(string message);

string communicateWithServer(string cmd);

Msg sendAndGet(string name,string password,string op,string participator,string title,
	string startDate,string endDate,string email,string phone);
#endif
