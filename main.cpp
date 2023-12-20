#include "loginandsignupdialog.h"
#include "todocomponent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loginAndSignUpDialog w;
    w.show();
    /*
    QMainWindow mainWindow;

    // Create a toDoComponent
    toDoComponent *todoComponent = new toDoComponent(&mainWindow);

    // Set the toDoComponent as the central widget of the main window
    mainWindow.setCentralWidget(todoComponent);

    // Show the main window
    mainWindow.show();
    todoComponent->performDeleteToDo();
    */
    return a.exec();
}
