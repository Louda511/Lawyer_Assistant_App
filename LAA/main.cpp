#include "mainwindow.h"

#include <QApplication>
#include <Qfile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile("./Adaptic.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);


    MainWindow w;
    w.show();
    return a.exec();
}
