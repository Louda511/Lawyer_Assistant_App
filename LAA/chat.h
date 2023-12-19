#ifndef CHAT_H
#define CHAT_H

#include "qsqldatabase.h"
#include <QString>
class Chat {
private:
    QString id;
    QString request;
    QString response;
    QString conversationId;
    QSqlDatabase dbChatConnection;
public:
    // Constructor
    Chat(const QString& request, const QString& response, const QString& conversationId,const QSqlDatabase dbChatConnection);
    Chat(const QString& id);
    // Getters
    const QString& getId() const;
    const QString& getRequest() const;
    const QString& getResponse() const;
    const QString& getConversationId() const;

    // Setters
    void setId(const QString& newId);
    void setRequest(const QString& newRequest);
    void setResponse(const QString& newResponse);

    bool saveToDatabase();
    bool loadFromDatabase(const QString& chatId);
};

#endif // CHAT_H
