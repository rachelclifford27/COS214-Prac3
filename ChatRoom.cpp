#include "ChatRoom.h"
#include "ChatAggregate.h"
#include "Users.h"
#include "NotificationObserver.h"
#include "Command.h"
#include "ChatIterator.h"      
#include "UserIterator.h"  
#include "MessageIterator.h"

// Constructor
ChatRoom::ChatRoom() : chatHistory(), roomName("DefaultRoom") {
    // Initialize empty vectors and string
}

// Destructor
ChatRoom::~ChatRoom() {
    // Clean up commands
    for (auto* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
    
    // Clean up - Note: We don't delete users or observers as they may be managed elsewhere
    users.clear();
    observers.clear();
}

// User management methods
void ChatRoom::registerUser(User* user) {
    if (user != nullptr) {
        // Check if user is not already registered
        for (const auto& existingUser : users) {
            if (existingUser == user) {
                return; // User already registered
            }
        }
        users.push_back(user);
        
        // Notify observers about new user
        notifyObservers("USER_JOINED", "User joined the chat room");
    }
}

void ChatRoom::removeUser(User* user) {
    if (user != nullptr) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if (*it == user) {
                users.erase(it);
                
                // Notify observers about user leaving
                notifyObservers("USER_LEFT", "User left the chat room");
                break;
            }
        }
    }
}

// Message handling methods
void ChatRoom::sendMessage(const std::string& message, User* fromUser) {
    if (fromUser != nullptr && !message.empty()) {
        // Save the message to history
        saveMessage(message, fromUser);
        
        // Send message to all other users in the room
       for (auto* user : users) {
            if (user != fromUser) {
                user->receiveMessage(message, fromUser);
            }
        }
        
        // Notify observers about new message
        notifyObservers("MESSAGE_SENT", message);
    }
}

void ChatRoom::receiveMessage(const std::string& message, User* fromUser) {
    // This method handles incoming messages to the chat room
    // In this implementation, it delegates to sendMessage
    sendMessage(message, fromUser);
}

void ChatRoom::saveMessage(const std::string& message, User* fromUser) {
    if (fromUser != nullptr && !message.empty()) {
        // Format: [Username]: Message\n
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

// Observer pattern methods
void ChatRoom::addObserver(NotificationObserver* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void ChatRoom::removeObserver(NotificationObserver* observer) {
    if (observer != nullptr) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }
}

void ChatRoom::notifyObservers(const std::string& event, const std::string& data) {
    for (auto* observer : observers) {
        if (observer != nullptr) {
            observer->update(event, data, this);
        }
    }
}

// Command pattern methods
void ChatRoom::addCommand(Command* command) {
    if (command != nullptr) {
        commandQueue.push_back(command);
    }
}

void ChatRoom::executeAll() {
    // Execute all queued commands in sequence
    for (auto* command : commandQueue) {
        if (command != nullptr) {
            command->execute();
        }
    }
    
    // Clear the command queue after execution
    for (auto* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
}


// Getters
const std::vector<User*>& ChatRoom::getUsers() const {
    return users;
}

const std::vector<std::string>& ChatRoom::getChatHistory() const {
    return chatHistory;
}

std::string ChatRoom::getName() const {
    return roomName;
}