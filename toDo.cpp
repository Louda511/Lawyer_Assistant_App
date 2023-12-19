#include "todo.h"

// Constructors
toDo::toDo() {
    // Initialize member variables if needed
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
