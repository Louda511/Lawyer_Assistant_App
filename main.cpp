#include "loginandsignupdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginAndSignUpDialog w;
    w.show();
    return a.exec();
}
