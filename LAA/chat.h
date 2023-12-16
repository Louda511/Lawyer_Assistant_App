#ifndef CHAT_H
#define CHAT_H

#include <QString>

class Chat {
private:
    QString id;
    QString request;
    QString response;
    QString conversationId;

public:
    // Constructor
    Chat(const QString& id, const QString& request, const QString& response, const QString& conversationId);

    // Getters
    const QString& getId() const;
    const QString& getRequest() const;
    const QString& getResponse() const;
    const QString& getConversationId() const;

    // Setters
    void setId(const QString& newId);
    void setRequest(const QString& newRequest);
    void setResponse(const QString& newResponse);
    void setConversationId(const QString& newConversationId);
};

#endif // CHAT_H
