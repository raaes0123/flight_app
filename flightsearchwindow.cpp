#include "flightsearchwindow.h"
#include "ui_flightsearchwindow.h"

FlightSearchWindow::FlightSearchWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FlightSearchWindow)
{
    ui->setupUi(this);
    bw = new BookingWindow();
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->tableWidget->setMinimumHeight(100);
    ui->tableWidget->hide();
    // Open Database
    QSqlDatabase flightdb = QSqlDatabase::addDatabase("QSQLITE");
    flightdb.setDatabaseName("C:/Users/raaes/OneDrive/Documents/C++/Qt/Flight_Booking_App/FlightDB.db");
    // Select city from Airport table into the origin combo input
    if(flightdb.open()){
        QSqlQuery query(flightdb);
        query.prepare("select City from Airport");
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        else{
            qDebug() << "Executing query:";
            while(query.next()){
                ui->origin->addItem(query.value(0).toString());
                ui->destination->addItem(query.value(0).toString());
            }
        }
        flightdb.close();
    }
    else{
        qDebug()<<"Error opening database";
    }
}

FlightSearchWindow::~FlightSearchWindow()
{
    delete ui;
}



void FlightSearchWindow::on_searchButton_clicked()
{
    ui->tableWidget->show();
    QString origin = ui->origin->currentText();
    QString destination = ui->destination->currentText();
    // Open Database
    if (QSqlDatabase::contains("QSQLITE"))
    {
        QSqlDatabase::removeDatabase("QSQLITE");
    }

    QSqlDatabase flightdb = QSqlDatabase::addDatabase("QSQLITE");
    flightdb.setDatabaseName("C:/Users/raaes/OneDrive/Documents/C++/Qt/Flight_Booking_App/FlightDB.db");
    // Select orgin and destination airport id, Departurea and arrival date and cost from Flight table
    // where
    QVector<QString> departure;
    QVector<QString> arrival;
    QVector<QString> date;
    QVector<QString> cost;
    QVector<QString> flightno;
    QVector<QString> airlineid;
    if(flightdb.open()){
        QSqlQuery query(flightdb);
        query.prepare("select DepartureAirportId,ArrivalAirportId,DepartureDate,Cost,FlightNo,AirlineId from (select DepartureAirportId,ArrivalAirportId,DepartureDate,Cost,FlightNo,AirlineId from Flight,Airport where Flight.ArrivalAirportId = Airport.AirportId and City = :destination) as newTable,Airport where newTable.DepartureAirportId = Airport.AirportId and Airport.City = :origin");
        query.bindValue(":origin",origin);
        query.bindValue(":destination",destination);
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
        }
        else{
            qDebug() << "Executing query now:";
            // Clear previous data
            QVector<QPushButton*> options;
            int rowCount = ui->tableWidget->rowCount();
            for(int i = rowCount ; i >= 0 ;i--){
                ui->tableWidget->removeRow(i);
            }
            ui->tableWidget->setColumnCount(1);
            ui->tableWidget->setHorizontalHeaderLabels({"Flights"});
            rowCount = 0;
            while(query.next()){
                // Add items in the listwidgets DepartureAirportId,ArrivalAirportId,DepartureDate,ArrivalDate,Cost
                departure.push_back(query.value(0).toString());
                arrival.push_back(query.value(1).toString());
                date.push_back(query.value(2).toString());
                cost.push_back(query.value(3).toString());
                flightno.push_back(query.value(4).toString());
                airlineid.push_back(query.value(5).toString());
                ui->tableWidget->insertRow(rowCount);
                QPushButton *button = new QPushButton(departure.back()+"->"+arrival.back()+"\n"+date.back()+"\n$"+cost.back());
                //button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                // Set the minimum size of the button
                button->setMinimumSize(150, 50);

                ui->tableWidget->setCellWidget(rowCount, 0, button);
                ui->tableWidget->resizeRowsToContents();
                options.append(button);

                // Connect the button's clicked signal to a lambda function
                connect(button, &QPushButton::clicked, [rowCount,departure,arrival,date,cost,flightno,airlineid, this]() {
                    qDebug() << "Button" << rowCount + 1 << "clicked";
                    // Go to bookingWindow on the basis of the option clicked
                    flightOption = rowCount + 1;
                    // Close register window and open the booking window
                    this->close();

                    // The booking window displays the flight selected: Flight no, Arrival airport id, Departure Airport id,Cost seat capacity and Airline
                    this->bw->departure = departure[rowCount];
                    this->bw->arrival = arrival[rowCount];
                    this->bw->date = date[rowCount];
                    this->bw->cost = cost[rowCount];
                    this->bw->flightno = flightno[rowCount];

                    //ui->flight->setText(this->flightno);
                    this->bw->displayBookingData();
                    this->bw->show();
                });
                rowCount++;
            }
        }
    }
    else{
        qDebug()<<"Error opening database";
    }
    //
    flightdb.close();
}

