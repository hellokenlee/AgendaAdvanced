#include "mainwindow.h"
#include "ui_mainwindow.h"
#define showme(a) cout<<a<<endl
void printMeetings(std::list<Meeting> meetings,QTextBrowser* tBtitle,QTextBrowser* tBSponsor,
                   QTextBrowser* tBParticipator,QTextBrowser* tBStartTime,QTextBrowser* tBEndTime) {
    list<Meeting>::iterator it;
    tBtitle->setText("Title:");
    tBSponsor->setText("Sponsor:");
    tBParticipator->setText("Participator:");
    tBStartTime->setText("Start Time:");
    tBEndTime->setText("End Time:");
    for (it = meetings.begin(); it != meetings.end(); it++) {
        tBtitle->append(QString::fromStdString(it->getTitle()));
        tBSponsor->append(QString::fromStdString(it->getSponsor()));
        tBParticipator ->append(QString::fromStdString(it->getParticipator()));
        tBStartTime ->append(QString::fromStdString(Date::dateToString(it->getStartDate())));
        tBEndTime ->append(QString::fromStdString(Date::dateToString(it->getEndDate())));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widgetLog->hide();
    ui->widgetWelcome->show();
    ui->widgetReg->hide();
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*************welcomeP --> loginP******************/
void MainWindow::on_btnLog_clicked()
{
    ui->widgetWelcome->hide();
    ui->widgetLog->show();
}
/*************loginP --> welcomeP******************/
void MainWindow::on_btnBack_2_clicked()
{
    ui->widgetWelcome->show();
    ui->widgetLog->hide();
}

/*************welcomeP --> RegisterP******************/
void MainWindow::on_btnReg_clicked()
{
    ui->widgetReg->show();
    ui->widgetWelcome->hide();
}
/*************registerP --> welcomeP******************/
void MainWindow::on_btnBack_reg_2_clicked()
{
    ui->widgetWelcome->show();
    ui->widgetReg->hide();
}


/*************loginP : login******************/
void MainWindow::on_btnLogIn_2_clicked()
{
    string name=ui->lineEditUserName_2->text().toStdString();
    string password=ui->lineEditPassword_2->text().toStdString();
    cout<<name<<" "<<password<<endl;
    Msg msg=sendAndGet(name,password,"l","","","","","","");
    bool flag=msg.opResult;
    if(!flag){
        QMessageBox::information(this,"Login Fail!","Please check your  imformations!");
    } else {
        userName_=name;
        userPassword_=password;
        ui->stackedWidget->setCurrentIndex(1);

       QDesktopWidget* desktopWidget = QApplication::desktop();
       int winWidth=desktopWidget->screenGeometry().width();
       int winHeight=desktopWidget->screenGeometry().height();
       QRect winRect((winWidth-520)/2,(winHeight-300)/2,520,300);
       this->setGeometry(winRect);
       this->setFixedSize(520,300);
    }
}

/*************registerP : register******************/
void MainWindow::on_btnReg_reg_2_clicked()
{
    string name=ui->lineEditUsername_reg_2->text().toStdString();
    string password=ui->lineEditPSW_reg_2->text().toStdString();
    string email=ui->lineEditEmail_reg_2->text().toStdString();
    string phone=ui->lineEditPhone_reg_2->text().toStdString();
    //cout<<name<<password<<email<<phone<<endl;
    Msg msg=sendAndGet(name,password,"r","","","","",email,phone);
    bool flag=msg.opResult;
    if(flag){
             QMessageBox::information(this,"Register Succeed!","Register succeed! \n\n Click OK to login!");
             this->on_btnBack_reg_2_clicked();
             this->on_btnLog_clicked();
    } else{
             QMessageBox::information(this,"Register Fail!","Please check your imformations!");
    }
}

/*************ClientP: query******************/
void MainWindow::on_btnQM_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->widgetTitleInput->hide();
    ui->widgetTimeInput->hide();
    list<Meeting> m;
    Msg msg=sendAndGet(userName_,"","la","","","","","","");
    m=msg.meetingList;
    printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
}
/*************ClientP: query: selcect filter******************/
void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    string selector=arg1.toStdString();
    ui->widgetTitleInput->hide();
    ui->widgetTimeInput->hide();
    list<Meeting> m;
    if(selector=="All"){
        showme("all");
        Msg msg=sendAndGet(userName_,"","la","","","","","","");
        m=msg.meetingList;
        printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
    }else if(selector=="As Sponsor"){
        showme("sp");
        Msg msg=sendAndGet(userName_,"","las","","","","","","");
        m=msg.meetingList;
        printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
    }else if(selector=="As Participator"){
        showme("pa");
        Msg msg=sendAndGet(userName_,"","lap","","","","","","");
        m=msg.meetingList;
        printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
    }else if(selector=="Title"){
        ui->widgetTitleInput->show();
    }else if(selector=="Time Interval"){
        ui->widgetTimeInput->show();
    }
}
/*************ClientP: query: query by time interval******************/
void MainWindow::on_btnGo_clicked()
{
    string sTime = ui->timeInputFrom->dateTime().toString("yyyy-MM-dd/hh:mm").toStdString();
    string eTime = ui->timeInputTo->dateTime().toString("yyyy-MM-dd/hh:mm").toStdString();
    showme(sTime);
    showme(eTime);
    Date sDate, eDate;
    sDate = Date::stringToDate(sTime);
    eDate = Date::stringToDate(eTime);
    if (sDate >eDate) {
        cout << "[error] wrong time interval!" << endl;
    }
    list<Meeting> m;
    Msg msg=sendAndGet(userName_,"","qt","","",sTime,eTime,"","");
    m=msg.meetingList;
    printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
}
/*************ClientP: query: query by title******************/
void MainWindow::on_btnGo_2_clicked()
{
    string title =ui->lineEditTitle->text().toStdString();
    showme(title);
    list<Meeting> m;
    Msg msg=sendAndGet(userName_,"","qm","",title,"","","","");
    m=msg.meetingList;
    printMeetings(m,ui->tBTitle,ui->tBSponsor,ui->tBParticipator,ui->tBStartTime,ui->tBEndTime);
}
/*************ClientP: query: back to CliengP******************/
void MainWindow::on_btnBack_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/*************ClientP: log out******************/
void MainWindow::on_btnLO_clicked()
{
  ui->stackedWidget->setCurrentIndex(0);
  ui->widgetWelcome->show();
  ui->widgetLog->hide();
  QDesktopWidget* desktopWidget = QApplication::desktop();
  int winWidth=desktopWidget->screenGeometry().width();
  int winHeight=desktopWidget->screenGeometry().height();
  QRect winRect((winWidth-400)/2,(winHeight-300)/2,400,300);
  this->setGeometry(winRect);
  this->setFixedSize(400,300);
  userName_="";
  userPassword_="";
}
/*************ClientP: to create******************/
void MainWindow::on_btnCM_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}
/*************ClientP: create : back to ClientP******************/
void MainWindow::on_btn_cmCancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/*************ClientP: Delete Acc******************/
void MainWindow::on_btnDC_clicked()
{
    QMessageBox message(QMessageBox::Warning,"Are you sure?","Once it did, it can not be undo!",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
       showme("yes!");
       Msg msg=sendAndGet(userName_,userPassword_,"dc","","","","","","");
       bool flag=msg.opResult;
       if(!flag){
           showme("Error in delete User");
       }
       ui->stackedWidget->setCurrentIndex(0);
       ui->widgetWelcome->show();
       ui->widgetLog->hide();
       QDesktopWidget* desktopWidget = QApplication::desktop();
       int winWidth=desktopWidget->screenGeometry().width();
       int winHeight=desktopWidget->screenGeometry().height();
       QRect winRect((winWidth-400)/2,(winHeight-300)/2,400,300);
       this->setGeometry(winRect);
       this->setFixedSize(400,300);
       userName_="";
       userPassword_="";
    }
    else
    {
        showme("no!");
    }
}
/*************ClientP: create meeting******************/
void MainWindow::on_btn_cmCreate_clicked()
{
    string name, title, participator, sTime, eTime;
    name=userName_;
    title=ui->lineEdit_cmTitle->text().toStdString();
    participator=ui->lineEdit_cmParticipator->text().toStdString();
    sTime=ui->dateTimeEdit_Starttime->dateTime().toString("yyyy-MM-dd/hh:mm").toStdString();
    eTime=ui->dateTimeEdit_Endtime->dateTime().toString("yyyy-MM-dd/hh:mm").toStdString();
    Msg msg=sendAndGet(name,"","cm",participator,title,sTime,eTime,"","");
    bool flag=msg.opResult;
    if(flag){
        QMessageBox::information(this,"Meeting has been created!","create succeed!");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else{
        QMessageBox::information(this,"Failed to create!","please check your imformation!");
    }
}
/***********clientP: list all user*****************/
void MainWindow::on_btnLU_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    list<User>::iterator it;
    list<User> u;
    Msg msg=sendAndGet("","","lu","","","","","","");
    u=msg.userList;
    char num[256];
    sprintf(num,"%ld",u.size());
    string num_=num;
    ui->label_usercount->setText(QString::fromStdString("There are "+num_+" Users:"));
    ui->tB_name->setText("Name");
    ui->tB_email->setText("Email:");
    ui->tB_phone->setText("Phone:");
    for (it = u.begin(); it != u.end(); it++) {
            ui->tB_name->append(QString::fromStdString(it->getName()));
            ui->tB_email->append(QString::fromStdString(it->getEmail()));
            ui->tB_phone->append(QString::fromStdString(it->getPhone()));
     }
}
/***********clientP: list all user:back*****************/
void MainWindow::on_btn_LUback_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/***********clientP: to delete meeting*****************/
void MainWindow::on_btnDM_clicked()
{
     ui->stackedWidget->setCurrentIndex(5);
}
/***********clientP: DM: back to clientP*****************/
void MainWindow::on_btn_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/***********clientP: DM: Delete meeting by title*****************/
void MainWindow::on_btn_dm_clicked()
{
    string title;
    title=ui->lineEdit_dmTitle->text().toStdString();
    Msg msg=sendAndGet(userName_,"","dm","",title,"","","","");
    bool flag=msg.opResult;
    QString ms1=QString::fromStdString("You have no meeting called: <"+title+">");
    QString ms2=QString::fromStdString("Meeting <"+title+"> has been deteled!");
    if(!flag){
        QMessageBox::information(this,"Delete Failed",ms1);
    }
    else{
        QMessageBox::information(this,"Delete succeed!",ms2);
    }
}
/***********clientP: DM: Delete all meeting*****************/
void MainWindow::on_btn_dam_clicked()
{

    QMessageBox message(QMessageBox::Warning,"Are you sure?","Once it did, it can not be undo!",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        Msg msg=sendAndGet(userName_,"","da","","","","","","");
         QMessageBox::information(this,"All meeting has been deleted!","delete succeed!");
    }
}
