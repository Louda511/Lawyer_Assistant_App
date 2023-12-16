#include "conversation.h"

// Constructor
Conversation::Conversation(const QString& id) : id(id) {}

// Getter for id
const QString& Conversation::getId() const {
    return id;
}

// Setter for id
void Conversation::setId(const QString& newId) {
    id = newId;
}
