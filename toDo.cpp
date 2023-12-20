#include "todo.h"

// Constructors
toDo::toDo() {
    // Initialize member variables if needed
}

toDo::toDo(int newId, const QString& newTitle, const QString& newDescription, const QString& newDeadline, int newLawyerId)
    : id(newId), title(newTitle), description(newDescription), deadline(newDeadline), l_id(newLawyerId)
{
    // Additional initialization if needed
}

// Setters
void toDo::setId(int newId) {
    id = newId;
}

void toDo::setTitle(const QString& newTitle) {
    title = newTitle;
}

void toDo::setDescription(const QString& newDescription) {
    description = newDescription;
}

void toDo::setDeadline(const QString& newDeadline) {
    deadline = newDeadline;
}

void toDo::setListId(int newListId) {
    l_id = newListId;
}

// Getters
int toDo::getId() const {
    return id;
}

const QString& toDo::getTitle() const {
    return title;
}

const QString& toDo::getDescription() const {
    return description;
}

const QString& toDo::getDeadline() const {
    return deadline;
}

int toDo::getListId() const {
    return l_id;
}
