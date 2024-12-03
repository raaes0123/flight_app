#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include "QtSql/qsqldatabase.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow),rw(nullptr)
{
    loginCredential = false;
    ui->setupUi(this);
    // Create a connection connecting signal Register button clicked and slot openRegisterWindow
    connect(ui->Register,&QPushButton::clicked,this,&LoginWindow::openRegisterWindow);
    // Create a connection connecting signal Login button clicked and slot openFlightBookingWindow
    connect(ui->Login,&QPushButton::clicked,this,&LoginWindow::openFlightBookingWindow);
    ui->Password->setEchoMode(QLineEdit::Password);
}

void LoginWindow::openRegisterWindow(){
    //Create a new instance of registerwindow if not already
    rw = new RegisterWindow();
    //Show that window
    rw->show();
    // Connect the registerwindow's switchToLogin signal to show the LoginWindow
    connect(rw, &RegisterWindow::switchToLogin, this,&LoginWindow::backFromRegister);
    //Hide the loginWindow
    this->hide();
    //}
}

void LoginWindow::openFlightBookingWindow(){
    //If loginCredential is true
    //Create a new instance of FlightBookingWindow
    if(loginCredential){
        fw = new FlightSearchWindow();
        //Show that window
        fw->show();
        this->hide();
    }
    // Connect the flightbooking window's switchToLogin signal to go back to the LoginWindow
    //connect(rw, &RegisterWindow::switchToLogin, this,&LoginWindow::backFromRegister);
    //Hide the loginWindow
    //}
}

void LoginWindow::backFromRegister(){
    this->show();  // Show the LoginWindow
    rw->hide();    // Hide the registerwindow
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Login_clicked()
{
    // Connect to Database
    QSqlDatabase flightdb = QSqlDatabase::addDatabase("QSQLITE");
    flightdb.setDatabaseName("C:/Users/raaes/OneDrive/Documents/C++/Qt/Flight_Booking_App/FlightDB.db");
    QString uname = ui->Username->text(); //Passenger ID
    QString pword = ui->Password->text();
    if(flightdb.open()){
        QSqlQuery query(flightdb);
        query.prepare("select Password from Passenger where Username=:name");
        //query.bindValue(":name",uname);
        query.bindValue(":name",uname);
        if(query.exec()){
            query.next();
            pword = query.value(0).toString();
            if(pword == ui->Password->text() and pword != ""){
                loginCredential = true;
            }
            else{
                ui->loginStatus->setText("Invalid Username and Password");
                //ui->loginStatus->setPlainText("Invalid Username and Password");
            }
        }
        flightdb.close();
    }
    else{
        ui->Password->setText("Error opening database");
    }
}


