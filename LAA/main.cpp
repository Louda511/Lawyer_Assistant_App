#include "mainwindow.h"

#include <QApplication>
#include <Qfile>
#include "loginandsignupdialog.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile styleSheetFile(":/stylesheet/Adaptic.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);


    loginAndSignUpDialog::getInstance()->show();
    MainWindow::getInstance()->getInstance()->getInstance()->show();



    return a.exec();
}
