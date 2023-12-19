#ifndef TODO_H
#define TODO_H

#include <QString>

class toDo {
private:
    int id;
    QString title;
    QString description;
    QString deadline;
    int l_id;

public:
    // Constructors
    toDo();

    // Setters
    void setId(int newId);
    void setTitle(const QString& newTitle);
    void setDescription(const QString& newDescription);
    void setDeadline(const QString& newDeadline);
    void setListId(int newListId);

    // Getters
    int getId() const;
    const QString& getTitle() const;
    const QString& getDescription() const;
    const QString& getDeadline() const;
    int getListId() const;
};

#endif // TODO_H
