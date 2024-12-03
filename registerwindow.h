#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QtSql/QSql>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include <QSqlError>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

private slots:
    void backToLogin();

signals:
    void switchToLogin();

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();

private:
    Ui::RegisterWindow *ui;
};

#endif // REGISTERWINDOW_H
