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
    boardWindowApi* getInstance();

public slots:
    void toDosComponentsListInitializer(QList<toDo> *td);

private:
    QList<QSharedPointer<toDoComponent>> toDosComponentList;
    static boardWindowApi *instance;

};

#endif // BOARDWINDOWAPI_H
