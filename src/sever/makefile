#参数设定
CC=g++
FLAG= -c -std=c++0x  -lboost_system -lboost_filesystem -lpthread
EXEC=server
OBJECTS = AgendaService.o Date.o User.o Meeting.o Storage.o server.o

#可执行文件
$(EXEC): $(OBJECTS) 
	$(CC) -o $(EXEC) $(OBJECTS) -lboost_system -lboost_filesystem -lpthread
#中间文件
server.o: server.cpp 
	$(CC) $(FLAG) server.cpp

AgendaService.o: AgendaService.h AgendaService.cpp
	$(CC) $(FLAG)  AgendaService.cpp

Meeting.o: Meeting.h Meeting.cpp
	$(CC) $(FLAG) Meeting.cpp

User.o: User.h User.cpp
	$(CC) $(FLAG) User.cpp

Date.o: Date.h Date.cpp
	$(CC) $(FLAG) Date.cpp

Storage.o: Storage.h Storage.cpp
	$(CC) $(FLAG)  Storage.cpp

.PHONY: clean
clean:
	-rm -f  server *.o *~

.PHONY: run
run:
	./$(EXEC)

