#include "chat.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

// Constructors

Chat::Chat(const QString& request, const QString& response, const QString& conversationId,const QSqlDatabase dbChatConnection)
    : request(request), response(response), conversationId(conversationId),dbChatConnection(dbChatConnection) {
    // Save the object to the database upon creation
    if (!saveToDatabase()) {
        qDebug() << "Failed to save chat to database";
        // Handle the error as needed
    }
}
Chat::Chat(const QString& id) {
    // Call the loadFromDatabase method to populate the Chat object based on the provided id
    if (!id.isEmpty()) {
        if (!loadFromDatabase(id)) {
            qDebug() << "Failed to load chat from database for id: " << id;
            // Handle the error as needed
        }
    }
}
// Getters
const QString& Chat::getId() const {
    return id;
}

const QString& Chat::getRequest() const {
    return request;
}

const QString& Chat::getResponse() const {
    return response;
}

const QString& Chat::getConversationId() const {
    return conversationId;
}

// Setters
void Chat::setId(const QString& newId) {
    id = newId;
}

void Chat::setRequest(const QString& newRequest) {
    request = newRequest;
}

void Chat::setResponse(const QString& newResponse) {
    response = newResponse;
}

// Database access methods

bool Chat::saveToDatabase() {
    QSqlQuery query(dbChatConnection);
    query.prepare("INSERT INTO chats (request, response, Thread_id) VALUES (:request, :response, :conversationId)");
    query.bindValue(":request", request);
    query.bindValue(":response", response);
    query.bindValue(":conversationId", conversationId);

    if (query.exec()) {
        qDebug() << "Chat saved to database!";
        return true;
    } else {
        qDebug() << "Error saving chat to database:" << query.lastError().text();
        return false;
    }
}

bool Chat::loadFromDatabase(const QString& chatId) {
    QSqlQuery query(dbChatConnection);
    query.prepare("SELECT * FROM chats WHERE id = :chatId");
    query.bindValue(":chatId", chatId);

    if (query.exec() && query.next()) {
        id = query.value("id").toString();
        request = query.value("request").toString();
        response = query.value("response").toString();
        conversationId = query.value("Thread_id").toString();
        QSqlDatabase::database().commit();
        qDebug() << "Chat loaded from database!";
        return true;
    } else {
        qDebug() << "Error loading chat from database:" << query.lastError().text();
        return false;
    }
}
