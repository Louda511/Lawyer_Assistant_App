#include "loginandsignupdialog.h"
#include "todocomponent.h"
#include "todosboardwindow.h"
#include <QApplication>
#include <assigntodo.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginAndSignUpDialog *w = loginAndSignUpDialog::getInstance();

    w->show();

    /*
    QNetworkAccessManager manager;

    // URL of the endpoint
    QUrl juniorsUrl("https://lawyerassistant.up.railway.app/juniors");

    // Create a request
    QNetworkRequest request(juniorsUrl);

    // Perform the GET request
    QNetworkReply *reply = manager.get(request);

    // Create an event loop to wait for the reply to finish
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Check for errors
    if (reply->error() == QNetworkReply::NoError) {
        // Request was successful
        QByteArray responseData = reply->readAll();
        qDebug() << responseData;

    }
*/

    // Assuming you have some juniors added to the user instance


    // Other main code...

/*
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

    //toDosBoardWindow *mainWindow = toDosBoardWindow::getInstance();

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
    // Set up the main window layout

    // Set the main window layout

    // Show the main window
    //mainWindow->show();


    assignToDo *atd = new assignToDo();
    atd->show();
    user *currentUser = user::getInstance();
    toDosBoardWindow *mainWindow = toDosBoardWindow::getInstance();

    QList<toDo*> todos = currentUser->getToDos();

    // Iterate through the todos
    qDebug() << "User's Todos:";
    for (const toDo* todo : todos) { // Use a pointer here
        qDebug() << "u_Todo ID:" << todo->getId(); // Dereference the pointer to access members
        qDebug() << "u_Title:" << todo->getTitle();
        qDebug() << "u_Description:" << todo->getDescription();
        qDebug() << "u_Deadline:" << todo->getDeadline();
        // Add more fields as needed
        qDebug() << "------------------------";
    }
    for (auto todo : todos)
    {

          toDoComponent *component1 = new toDoComponent(todo);
        toDoComponentsList << component1;


    }
    mainWindow->addToDoComponents(toDoComponentsList);
    mainWindow->show();
*/
    return a.exec();




}
