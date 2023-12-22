#ifndef USER_H
#define USER_H

#include <QString>
#include "todo.h"
#include <QList>

class user {
private:
    int id;
    QString name;
    QString password;
    QString job_title;
    QString type;
    QString email;
    int sup_id;
    static user *instance;
    QList<toDo*> todos;

    // Private constructor to prevent external instantiation
    user();
    ~user();

public:


    // Setters
    void setId(int newId);
    void setName(const QString& newName);
    void setPassword(const QString& newPassword);
    void setJobTitle(const QString& newJobTitle);
    void setType(const QString& newType);
    void setEmail(const QString& newEmail);
    void setSupervisorId(int newSupId);
    void setToDos(const QList<toDo*>& newToDos);

    // Getters
    int getId() const;
    const QString& getName() const;
    const QString& getPassword() const;
    const QString& getJobTitle() const;
    const QString& getType() const;
    const QString& getEmail() const;
    int getSupervisorId() const;
    const QList<toDo*>& getToDos() const;
    // Function to get the instance of the singleton class
    static user* getInstance();
    void appendToDo(toDo* newToDo);


};

#endif // USER_H
