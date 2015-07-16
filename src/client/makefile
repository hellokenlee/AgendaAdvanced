#参数设定
CC=g++
FLAG= -c -std=c++11  -lboost_system -lboost_filesystem
EXEC=Agenda
OBJECTS = Agenda.o AgendaUI.o \
Date.o User.o Meeting.o client.o

#可执行文件
$(EXEC): $(OBJECTS) 
	$(CC) -o $(EXEC) $(OBJECTS) -lboost_system -lboost_filesystem
#中间文件
Agenda.o: Agenda.cpp 
	$(CC) $(FLAG) Agenda.cpp

AgendaUI.o: AgendaUI.h AgendaUI.cpp
	$(CC) $(FLAG)  AgendaUI.cpp

Meeting.o: Meeting.h Meeting.cpp
	$(CC) $(FLAG) Meeting.cpp

User.o: User.h User.cpp
	$(CC) $(FLAG) User.cpp

Date.o: Date.h Date.cpp
	$(CC) $(FLAG) Date.cpp

client.o: client.h client.cpp
	$(CC) $(FLAG)  client.cpp

.PHONY: clean
clean:
	-rm -f Agenda *.o *~

.PHONY: run
run:
	./$(EXEC)

