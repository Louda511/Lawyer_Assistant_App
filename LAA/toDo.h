
#ifndef TODO_H
#define TODO_H

#include <QString>

class toDo {
private:
    int id;
    QString title;
    QString description;
    QString deadline;
    QString toDoAuthorName;
    int l_id;
    bool done;

public:
    // Constructors
    toDo();
    toDo(int newId, const QString& newTitle, const QString& newDescription, const QString& newDeadline, int newLawyerId, bool done, const QString& toDoAuthorName);

    // Setters
    void setId(int newId);
    void setTitle(const QString& newTitle);
    void setDescription(const QString& newDescription);
    void setDeadline(const QString& newDeadline);
    void setToDoAuthorId(int newListId);
    void setToDoAuthorName(const QString& newSupervisor); // New setter for supervisor
    void setDone(bool newDone); // New setter for done



    // Getters
    int getId() const;
    const QString& getTitle() const;
    const QString& getDescription() const;
    const QString& getDeadline() const;
    int getToDoAuthorId() const;
    const QString& getToDoAuthorName() const; // New getter for supervisor
    bool isDone() const; // New getter for done


};

#endif // TODO_H

