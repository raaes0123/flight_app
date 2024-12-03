#ifndef FLIGHTSEARCHWINDOW_H
#define FLIGHTSEARCHWINDOW_H

#include <QWidget>
#include <QtSql/QSql>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QSqlError>
#include "bookingwindow.h"

namespace Ui {
class FlightSearchWindow;
}

class FlightSearchWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FlightSearchWindow(QWidget *parent = nullptr);
    ~FlightSearchWindow();

private slots:
    void on_searchButton_clicked();

private:
    Ui::FlightSearchWindow *ui;
    BookingWindow *bw;
    int flightOption;

};

#endif // FLIGHTSEARCHWINDOW_H
