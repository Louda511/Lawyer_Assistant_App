#include "chat.h"

// Constructor
Chat::Chat(const QString& id, const QString& request, const QString& response, const QString& conversationId)
    : id(id), request(request), response(response), conversationId(conversationId) {}

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

void Chat::setConversationId(const QString& newConversationId) {
    conversationId = newConversationId;
}
