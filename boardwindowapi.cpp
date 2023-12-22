#include "boardwindowapi.h"
#include "todosboardwindow.h"

boardWindowApi::boardWindowApi()
{
}
boardWindowApi* boardWindowApi::instance = nullptr;

boardWindowApi* boardWindowApi::getInstance() {
    // Create the instance if it doesn't exist yet
    if (instance == nullptr) {
        instance = new boardWindowApi();
    }
    return instance;
}
void boardWindowApi::toDosComponentsListInitializer(QList<toDo> *td)
{
    QList<toDo>::iterator it;
    for (it = td->begin(); it != td->end(); ++it) {
        // Create QSharedPointer and add it to the list
        QSharedPointer<toDoComponent> todoComponent = QSharedPointer<toDoComponent>::create(&(*it));
        toDosComponentList.append(todoComponent);
    }
}
/*
void boardWindowApi::addToDoComponents(const QList<toDoComponent *> &toDoComponents)
{
    // Add ToDoComponents to the main grid layout
    int row = 0;
    int col = 0;
    QGridLayout* toDosGridLayout = toDosBoardWindow::getInstance()->getToDosGridLayout();

    for (toDoComponent *component : toDoComponents) {
        toDosGridLayout->addWidget(component, row, col);

        // Adjust the row and column for the next component
        col++;
        if (col >= 3) {
            col = 0;
            row++;
        }
    }
}
*/
