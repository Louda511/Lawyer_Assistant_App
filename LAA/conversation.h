#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QString>

class Conversation {
private:
    QString id;

public:
    // Constructor
    Conversation(const QString& id);

    // Getter for id
    const QString& getId() const;

    // Setter for id
    void setId(const QString& newId);
};

#endif // CONVERSATION_H
