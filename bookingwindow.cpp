#include "bookingwindow.h"
#include "ui_bookingwindow.h"

BookingWindow::BookingWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookingWindow)
{
    ui->setupUi(this);
}

BookingWindow::~BookingWindow()
{
    delete ui;
}

void BookingWindow::displayBookingData(){
    ui->label->setText("Flight");
    ui->textBrowser->setText(this->flightno+" "+this->departure+" "+this->arrival);
}
