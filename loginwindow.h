#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "registerwindow.h"
#include "flightsearchwindow.h"
#include <QtSql/QSql>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
class RegisterWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool loginCredential;

private slots:
    void openRegisterWindow();
    void openFlightBookingWindow();
    void backFromRegister();

    void on_Login_clicked();

private:
    Ui::LoginWindow *ui;
    RegisterWindow *rw;
    FlightSearchWindow *fw;
};

#endif // LOGINWINDOW_H
