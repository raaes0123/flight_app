#include "registerwindow.h"
#include "ui_registerwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    //Connect the registerButton of RegisterWindow to the backToLogin slot
    connect(ui->registerButton,&QPushButton::clicked,this,&RegisterWindow::backToLogin);
}

void RegisterWindow::backToLogin(){
    // Connect to Database
    QSqlDatabase flightdb = QSqlDatabase::addDatabase("QSQLITE");
    flightdb.setDatabaseName("C:/Users/raaes/OneDrive/Documents/C++/Qt/Flight_Booking_App/FlightDB.db");
    QString passid,fname,lname,email,uname,pword;
    passid = "P10016";
    fname = ui->firstName->text();
    lname = ui->lastName->text();
    email = ui->emailId->text();
    uname = ui->userName->text();
    pword = ui->password->text();
    if(flightdb.open()){
        QSqlQuery query(flightdb);
        query.prepare("insert into Passenger (PassId,FirstName,LastName,EmailId,Password,Username) values(:passid,:fname,:lname,:email,:uname,:pword)");
        //query.prepare("insert into Passenger (PassId,FirstName,LastName,EmailId,Password,Username) Values(P10016,Rajesh,Shah,rshah09,rajesh,123))");
        query.bindValue(":passid",passid);
        query.bindValue(":fname",fname);
        query.bindValue(":lname",lname);
        query.bindValue(":email",email);
        query.bindValue(":uname",uname);
        query.bindValue(":pword",pword);
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
    }
    flightdb.close();
    //Emit a signal that loginWindow can catch to unhide itself
    emit switchToLogin();
    this->close();
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}
