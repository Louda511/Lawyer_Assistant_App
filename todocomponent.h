// todocomponent.h
#ifndef TODOCOMPONENT_H
#define TODOCOMPONENT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QMainWindow>
#include "user.h"
#include "toDo.h"

class toDoComponent : public QWidget {
    Q_OBJECT
public:
    toDoComponent(QWidget *parent = nullptr);
    bool performDeleteToDo();
    void setTextBrowserDescription(QString text);
    void setDeadLineLabel(QString deadline);
    void setLawyerOrSupervisorLabel(QString label);



private:
    QCheckBox *checkbox;
    QTextBrowser *description;
    QLabel *deadLine;
    QLabel *lawyerOrSupervisorLabel;
    QPushButton *deleteButton;
    QString userType;
};

#endif // TODOCOMPONENT_H

