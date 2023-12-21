#include "loginandsignupdialog.h"
#include "todocomponent.h"
#include "todosboardwindow.h"
#include <QApplication>
#include <assigntodo.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginAndSignUpDialog w;
    w.show();

    // Create the main window
    user *u = user::getInstance();
    u->setType("lawyer");
    int taskId = 1;
    QString taskTitle = "Complete Assignment";
    QString taskDescription = "Finish the project before the deadline";
    QString taskDeadline = "2023-12-31";
    int lawyerId = 123;
    bool done = true;
    QString name = "Ahmed Khaled";

    toDo *td = new toDo(taskId, taskTitle, taskDescription, taskDeadline, lawyerId, done, name);

    toDosBoardWindow *mainWindow = toDosBoardWindow::getInstance();

    // Create some toDoComponent objects for testing
    toDoComponent *component1 = new toDoComponent(td);
    toDoComponent *component2 = new toDoComponent(td);
    toDoComponent *component3 = new toDoComponent(td);
    toDoComponent *component4 = new toDoComponent();

    // Create a QList to hold the toDoComponent objects
    QList<toDoComponent *> toDoComponentsList;
    toDoComponentsList << component1 << component2 << component3 << component4;

    // Test the addToDoComponents function
    //mainWindow.addSingleToDoComponent(component1);
    mainWindow->addToDoComponents(toDoComponentsList);
    // Set up the main window layout

    // Set the main window layout

    // Show the main window
    mainWindow->show();

    /*
    assignToDo *atd = new assignToDo();
    atd->show();
*/
    return a.exec();
}
