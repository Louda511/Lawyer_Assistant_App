#include "boardwindowapi.h"

boardWindowApi::boardWindowApi()
{
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

