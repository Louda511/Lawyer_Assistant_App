#include "loginandsignupdialog.h"
#include "todocomponent.h"
#include "todosboardwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    loginAndSignUpDialog w;
    w.show();
*/
    /*
    QMainWindow mainWindow;

    // Create a toDoComponent
    toDoComponent *todoComponent = new toDoComponent(&mainWindow);

    // Set the toDoComponent as the central widget of the main window
    mainWindow.setCentralWidget(todoComponent);

    // Show the main window
    mainWindow.show();
    //todoComponent->performDeleteToDo();

    */
    /*
    toDosBoardWindow mainWindow;

    // Create a toDoComponent
    mainWindow.show();
    */
    // Set the toDoComponent as the central widget of toDosBoardWindow


    // You can call methods on todoComponent as needed
   // qDebug() << "toDoComponent size:" << todoComponent->size();
    // Create the main window
    toDosBoardWindow mainWindow;

    // Create some toDoComponent objects for testing
    toDoComponent *component1 = new toDoComponent(nullptr);
    toDoComponent *component2 = new toDoComponent(nullptr);
    toDoComponent *component3 = new toDoComponent(nullptr);
    toDoComponent *component4 = new toDoComponent(nullptr);

    // Create a QList to hold the toDoComponent objects
    QList<toDoComponent *> toDoComponentsList;
    toDoComponentsList << component1 << component2 << component3 << component4;

    // Test the addToDoComponents function
    //mainWindow.addSingleToDoComponent(component1);
    mainWindow.addToDoComponents(toDoComponentsList);
    // Set up the main window layout

    // Set the main window layout

    // Show the main window
    mainWindow.show();

    return a.exec();
}
