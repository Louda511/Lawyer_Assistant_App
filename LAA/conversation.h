#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QSqlDatabase>
#include <QString>

class Conversation {
private:
    QString id;
    QString lawerId;
    int qtThreadId;
    QSqlDatabase dbChatConnection;
public:
    // Constructor
    Conversation(const QString& id, const QString& lawerId, const int& qtThreadId,const QSqlDatabase dbChatConnection);
    Conversation(const int& qtThreadId);
    // Getter for id
    const QString& getId() const;

    // Setter for id
    void setId(const QString& newId);

    // Getter for lawerId
    const QString& getLawerId() const;

    // Setter for lawerId
    void setLawerId(const QString& newLawerId);

    // Getter for qtThreadId
    const int& getQtThreadId() const;

    // Setter for qtThreadId
    void setQtThreadId(const int& newQtThreadId);
    bool saveToDatabase();

    bool loadFromDatabase(const int& threadId) ;
};

#endif // CONVERSATION_H
