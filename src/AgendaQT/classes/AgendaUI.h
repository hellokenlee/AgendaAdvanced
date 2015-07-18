#ifndef AGENDAUI_H
#define AGENDAUI_H

#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "client.h"

class AgendaUI {
 public:
  AgendaUI();
  void getOperation(void);

 private:
  // task functions
  void startAgenda(void);
  bool executeOperation(std::string op);
  void userLogIn(void);
  void userRegister(void);
  void quitAgenda(void);
  void userLogOut(void);
  void deleteUser(void);
  void listAllUsers(void);
  void createMeeting(void);
  void listAllMeetings(void);
  void listAllSponsorMeetings(void);
  void listAllParticipateMeetings(void);
  void queryMeetingByTitle(void);
  void queryMeetingByTimeInterval(void);
  void deleteMeetingByTitle(void);
  void deleteAllMeetings(void);
  void printMeetings(std::list<Meeting> meetings);
  // own functions
  std::string getCmd(void);
  // dates
  std::string userName_;
  std::string userPassword_;
};

#endif
