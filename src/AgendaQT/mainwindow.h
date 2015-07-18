#define WIN32_LEAN_AND_MEAN
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "classes/client.h"
#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cstdlib>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnLog_clicked();

    void on_btnReg_clicked();

    void on_btnLogIn_2_clicked();

    void on_btnBack_2_clicked();

    void on_btnBack_reg_2_clicked();

    void on_btnReg_reg_2_clicked();

    void on_btnQM_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_btnGo_clicked();

    void on_btnGo_2_clicked();

    void on_btnBack_clicked();

    void on_btnLO_clicked();

    void on_btnCM_clicked();

    void on_btn_cmCancel_clicked();

    void on_btnDC_clicked();

    void on_btn_cmCreate_clicked();

    void on_btnLU_clicked();

    void on_btn_LUback_clicked();

    void on_btnDM_clicked();

    void on_btn_back_clicked();

    void on_btn_dm_clicked();

    void on_btn_dam_clicked();

private:
    Ui::MainWindow *ui;
    std::string userName_;
    std::string userPassword_;
};

#endif // MAINWINDOW_H
