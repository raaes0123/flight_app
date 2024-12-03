#include "loginwindow.h"
#include "QFile"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Set the app style sheet
    //QFile styleSheetFile("C:/Users/raaes/OneDrive/Documents/C++/Qt/Project_2/Ubuntu.qss");
    QFile styleSheetFile("C:/Users/raaes/OneDrive/Documents/C++/Qt/Project_2/MacOS.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    LoginWindow w;
    w.show();
    return a.exec();
}
