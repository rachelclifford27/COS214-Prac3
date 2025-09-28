#include "ChatRoom.h"
#include "ChatAggregate.h"
#include "Users.h"
#include "NotificationObserver.h"
#include "Command.h"
#include "ChatIterator.h"      
#include "UserIterator.h"  
#include "MessageIterator.h"

ChatRoom::ChatRoom() : chatHistory(), roomName("DefaultRoom") {
}

ChatRoom::~ChatRoom() {
    for (auto* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
    
    users.clear();
    //observers.clear();
}

void ChatRoom::registerUser(User* user) {
    if (user != nullptr) {
        for (const auto& existingUser : users) {
            if (existingUser == user) {
                return;
            }
        }
        users.push_back(user);
        
        notifyObservers("USER_JOINED", "User joined the chat room");
    }
}

void ChatRoom::removeUser(User* user) {
    if (user != nullptr) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (*it == user) {
                users.erase(it);
                
                notifyObservers("USER_LEFT", "User left the chat room");
                break;
            }
        }
    }
}

User* ChatRoom::getUser(const std::string& name) {
    for (User* user : users) {
        if (user != nullptr && user->getName() == name) {
            return user;
        }
    }
    return nullptr;
}

void ChatRoom::sendMessage(const std::string& message, User* fromUser) {
    if (fromUser != nullptr && !message.empty()) {
        saveMessage(message, fromUser);
        
       for (auto* user : users) {
            if (user != fromUser) {
                user->receiveMessage(message, fromUser);
            }
        }
        
        notifyObservers("MESSAGE_SENT", message);
    }
}

void ChatRoom::receiveMessage(const std::string& message, User* fromUser) {
    sendMessage(message, fromUser);
}

void ChatRoom::saveMessage(const std::string& message, User* fromUser) {
    if (fromUser != nullptr && !message.empty()) {
        std::string formattedMessage = "[" + fromUser->getName() + "]: " + message + "\n";
        chatHistory.push_back(formattedMessage);
    }
}

UserIterator* ChatRoom::createUserIterator() {
    return new UserIterator(users);
}

MessageIterator* ChatRoom::createMessageIterator() {
    return new MessageIterator(chatHistory);
}

void ChatRoom::notifyObservers(const std::string& event, const std::string& data) {
    for (auto* observer : observers) {
        if (observer != nullptr) {
            observer->update(event, data, this);
        }
    }
}

void ChatRoom::addCommand(Command* command) {
    if (command != nullptr) {
        commandQueue.push_back(command);
    }
}

void ChatRoom::executeAll() {
    for (auto* command : commandQueue) {
        if (command != nullptr) {
            command->execute();
        }
    }
    
    for (auto* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
}

bool ChatRoom::hasUser(User* user) const {
    if (user == nullptr) {
        return false;
    }
    
    for (const User* u : users) {
        if (u == user) {
            return true;
        }
    }
    return false;
}

int ChatRoom::getUserCount() const {
    return static_cast<int>(users.size());
}

const std::vector<NotificationObserver*>& ChatRoom::getObservers() const {
    return observers;
}

const std::vector<User*>& ChatRoom::getUsers() const {
    return users;
}

const std::vector<std::string>& ChatRoom::getChatHistory() const {
    return chatHistory;
}

std::string ChatRoom::getName() const {
    return roomName;
}

void ChatRoom::clearChatHistory() {
    chatHistory.clear();
    std::cout << "[" << roomName << "] Chat history cleared" << std::endl;
}