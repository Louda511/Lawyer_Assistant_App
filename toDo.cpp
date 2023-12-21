#include "todo.h"

// Constructors
toDo::toDo() {
    // Initialize member variables if needed
}

toDo::toDo(int newId, const QString& newTitle, const QString& newDescription, const QString& newDeadline, int newLawyerId, bool done, const QString& name)
    : id(newId), title(newTitle), description(newDescription), deadline(newDeadline), l_id(newLawyerId), done(done), toDoAuthorName(name)
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

void toDo::setToDoAuthorName(const QString& newName) {
    toDoAuthorName = newName;
}

void toDo::setToDoAuthorId(int newListId) {
    l_id = newListId;
}
void toDo::setDone(bool newDone) {
    done = newDone;
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
const QString& toDo::getToDoAuthorName() const {
    return toDoAuthorName;
}
int toDo::getToDoAuthorId() const {
    return l_id;
}
bool toDo::isDone() const {
    return done;
}
