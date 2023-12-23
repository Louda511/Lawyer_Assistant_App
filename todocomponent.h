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

    toDoComponent(toDo *td, QWidget *parent = nullptr); // New constructor
    toDoComponent(QWidget *parent = nullptr);
    ~toDoComponent(); // Destructor to handle memory cleanup

    bool performDeleteToDo();
    void setTextBrowserDescription(QString text);
    void setDeadLineLabel(QString deadline);
    void setLawyerOrSupervisorLabel(QString label);
    QString getInitials(const QString& fullName);

signals:
    void deleteToDo(toDo *td);

private:
    QString userType;
    toDo *todo;

    QCheckBox *checkbox;
    QTextBrowser *description;
    QLabel *deadLine;
    QLabel *lawyerOrSupervisorLabel;
    QPushButton *deleteButton;


};

#endif // TODOCOMPONENT_H

