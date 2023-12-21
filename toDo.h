
#ifndef TODO_H
#define TODO_H

#include <QString>

class toDo {
private:
    int id;
    QString title;
    QString description;
    QString deadline;
    QString supervisor;
    int l_id;

public:
    // Constructors
    toDo();
    toDo(int newId, const QString& newTitle, const QString& newDescription, const QString& newDeadline, int newLawyerId);

    // Setters
    void setId(int newId);
    void setTitle(const QString& newTitle);
    void setDescription(const QString& newDescription);
    void setDeadline(const QString& newDeadline);
    void setListId(int newListId);
    void setSupervisor(const QString& newSupervisor); // New setter for supervisor


    // Getters
    int getId() const;
    const QString& getTitle() const;
    const QString& getDescription() const;
    const QString& getDeadline() const;
    int getListId() const;
    const QString& getSupervisor() const; // New getter for supervisor

};

#endif // TODO_H

