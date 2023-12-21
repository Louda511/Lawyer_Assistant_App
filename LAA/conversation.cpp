#include "conversation.h"
#include "qdebug.h"
#include "qsqlerror.h"
#include "qsqlquery.h"

// Constructor
Conversation::Conversation(const QString& id, const QString& lawerId, const int& qtThreadId, const QSqlDatabase dbChatConnection)
    : id(id), lawerId(lawerId), qtThreadId(qtThreadId) {
    // Save the object to the database upon creation
    if (!saveToDatabase()) {
        qDebug() << "Failed to save conv to database";
        // Handle the error as needed
    }
}
Conversation::Conversation(const int& qtThreadId){
    if (!loadFromDatabase(qtThreadId)) {
        qDebug() << "Failed to load chat from database for id: " << qtThreadId;
        // Handle the error as needed
    }

}
// Getter for id
const QString& Conversation::getId() const {
    return id;
}

// Setter for id
void Conversation::setId(const QString& newId) {
    id = newId;
}

// Getter for lawerId
const QString& Conversation::getLawerId() const {
    return lawerId;
}

// Setter for lawerId
void Conversation::setLawerId(const QString& newLawerId) {
    lawerId = newLawerId;
}

// Getter for qtThreadId
const int& Conversation::getQtThreadId() const {
    return qtThreadId;
}

// Setter for qtThreadId
void Conversation::setQtThreadId(const int& newQtThreadId) {
    qtThreadId = newQtThreadId;
}
bool Conversation::saveToDatabase() {
    QSqlQuery query(dbChatConnection);
    query.prepare("INSERT INTO Thread (id, Lawyer_id, Qt_thread_id) VALUES (:id, :lawyerId, :conversationId)");
    query.bindValue(":id", id);
    query.bindValue(":lawyerId", lawerId);
    query.bindValue(":conversationId", qtThreadId);

    if (query.exec()) {
        qDebug() << "Chat saved to database!";
        return true;
    } else {
        qDebug() << "Error saving chat to database:" << query.lastError().text();
        return false;
    }
}

bool Conversation::loadFromDatabase(const int& threadId) {
    QSqlQuery query(dbChatConnection);
    query.prepare("SELECT * FROM Thread WHERE Qt_thread_id = :conversationId");
    query.bindValue(":conversationId", threadId);

    if (query.exec() && query.next()) {
        id = query.value("id").toString();
        lawerId = query.value("lawyerId").toString();
        qtThreadId = query.value("Qt_thread_id").toInt();
        QSqlDatabase::database().commit();
        qDebug() << "Chat loaded from database!";
        return true;
    } else {
        qDebug() << "Error loading chat from database:" << query.lastError().text();
        return false;
    }
}
