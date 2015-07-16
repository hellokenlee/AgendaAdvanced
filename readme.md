# Agenda Advanced Project#
> ### Software Design Comprehensive Experiment Project ###
> #### SS.SYSU.2015 ####

----------

#### Design by ####
- 12330173 Li Xiaoliang  
- 12330180 Li Yucheng  
- 12330277 Shui Zemin


----------
### Directory Description ###
- ./bin　　　　　　　 　　　　　　　　　 　　——(binary executable files directory)
	- `Agenda_client_GUI`:　 　　　　　　　　　——(QT-GUI client executable file)
	- `Agenda_client_TUI`:　 　　　　　　　　　——(terminal version client executable file)
	- `Agenda_server`:　 　　　　　　　　　——(server executable file)
- ./doc　　　　　　 　　　　　　　　　　　 　——(documents directory)
- ./src　　　　　　 　　　　　　　　　　　 　——(source code directory)
	- AgendaQT:　 　　　　　　　　　　　　——(QT-GUI client project[with QtCreator])
	- client:　 　　　　　　　　　　　　　　 ——(client project[with makefile])
	- server:　 　　　　　　　　　　　　　　——(server project[with makefile])


----------
### How to execute? ###
1. `$ cd ./bin`
2. `$ ./server`
3. double click `Agenda_client_GUI` or `$ ./Agenda_client_TUI`


----------
### How to compile? ###
1. server: `$(cd ./src/server,make)`
2. TUI-client: `$(cd ./src/client,make)`
3. GUI-client: use QT-creator to open `AgendaQT.pro.user` or compile with Qmake

----------
### Dependency ###
- depend on QT library
- depend on boost::asio library