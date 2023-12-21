#ifndef BOARDWINDOWAPI_H
#define BOARDWINDOWAPI_H

#include <QObject>
#include <todo.h>
#include <todocomponent.h>

class boardWindowApi : public QObject
{
    Q_OBJECT
public:
    boardWindowApi();

public slots:
    void toDosComponentsListInitializer(QList<toDo> *td);

private:
    QList<QSharedPointer<toDoComponent>> toDosComponentList;
};

#endif // BOARDWINDOWAPI_H
