#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>

namespace Ui {
class BookingWindow;
}

class BookingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BookingWindow(QWidget *parent = nullptr);
    ~BookingWindow();
    QString departure;
    QString arrival;
    QString date;
    QString cost;
    QString flightno;
    QString airlineId;
    void displayBookingData();
private:
    Ui::BookingWindow *ui;
};

#endif // BOOKINGWINDOW_H
