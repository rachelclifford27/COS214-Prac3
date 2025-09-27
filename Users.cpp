
#include "Users.h"
#include "ChatRoom.h"
#include "Command.h"
#include "SendMessageCommand.h"
#include "LogMessageCommand.h"
#include <iostream>

/**
 * @file User.cpp
 * @brief Implementation of the User class
 * @author [Your Name]
 * @date [Current Date]
 */

/**
 * @brief Constructor for User
 * @param userName The name of the user
 */
User::User(const std::string& userName) : name(userName), isOnline(false) {
    chatRooms.clear();
    commandQueue.clear();
}

/**
 * @brief Virtual destructor
 * 
 * Cleans up command queue and removes user from all chat rooms
 */
User::~User() {
    for (Command* command : commandQueue) {
        delete command;
    }
    commandQueue.clear();
    
    for (ChatRoom* room : chatRooms) {
        if (room != nullptr) {
            room->removeUser(this);
        }
    }
    chatRooms.clear();
}

/**
 * @brief Send a message to a specific chat room
 * @param message The message content
 * @param room The chat room to send the message to
 * 
 * This method implements the Command pattern by creating command objects
 * and adding them to the queue for execution
 */
void User::sendMessage(const std::string& message, ChatRoom* room) {
    if (room == nullptr) {
        std::cerr << "Error: Cannot send message to null chat room" << std::endl;
        return;
    }
    
    if (!isInChatRoom(room)) {
        std::cerr << "Error: User " << name << " is not in the specified chat room" << std::endl;
        return;
    }
    
    if (!isOnline) {
        std::cerr << "Error: User " << name << " is offline and cannot send messages" << std::endl;
        return;
    }
    
    Command* sendCommand = new SendMessageCommand(room, this, message);
    Command* logCommand = new LogMessageCommand(room, this, message);
    
    addCommand(sendCommand);
    addCommand(logCommand);
    
    executeAll();
}

/**
 * @brief Receive a message from a chat room
 * @param message The message content
 * @param fromUser The user who sent the message
 * @param room The chat room where the message was sent
 * 
 * This method is called by the ChatRoom mediator when a message is delivered
 */
void User::receive(const std::string& message, User* fromUser, ChatRoom* room) {
    if (fromUser == nullptr || room == nullptr) {
        std::cerr << "Error: Invalid parameters for receive message" << std::endl;
        return;
    }
    
    if (fromUser == this) {
        return;
    }
    
    if (isOnline && isInChatRoom(room)) {
        std::cout << "[" << name << "] Received in " << room->getName() 
                  << " from " << fromUser->getName() << ": " << message << std::endl;
    }
}

/**
 * @brief Receive a message (simplified version called by ChatRoom)
 * @param message The message content
 * @param fromUser The user who sent the message
 * 
 * This method is called by ChatRoom::sendMessage()
 */
void User::receiveMessage(const std::string& message, User* fromUser) {
    if (fromUser == nullptr) {
        std::cerr << "Error: Invalid sender for receive message" << std::endl;
        return;
    }
    
    if (fromUser == this) {
        return; // Don't receive own messages
    }
    
    if (isOnline) {
        std::cout << "[" << name << "] Received from " << fromUser->getName() 
                  << ": " << message << std::endl;
    }
}

/**
 * @brief Add a command to the command queue
 * @param command The command to add
 */
void User::addCommand(Command* command) {
    if (command != nullptr) {
        commandQueue.push_back(command);
    }
}

/**
 * @brief Execute all commands in the queue
 * 
 * Executes commands in FIFO order and clears the queue
 */
void User::executeAll() {
    for (Command* command : commandQueue) {
        if (command != nullptr) {
            command->execute();
            delete command;
        }
    }

    commandQueue.clear();
}

/**
 * @brief Update method called when observed events occur
 * @param event The type of event that occurred
 * @param data Additional data about the event
 * @param room The chat room where the event occurred
 * 
 * Implementation of NotificationObserver interface for Observer pattern
 */
void User::update(const std::string& event, const std::string& data, ChatRoom* room) {
    if (room == nullptr || !isOnline) {
        return;
    }
    
    if (event == "USER_JOINED") {
        if (data != name) { // Don't notify about own join
            std::cout << "[NOTIFICATION] " << name << ": " << data 
                      << " joined " << room->getName() << std::endl;
        }
    }
    else if (event == "USER_LEFT") {
        if (data != name) {
            std::cout << "[NOTIFICATION] " << name << ": " << data 
                      << " left " << room->getName() << std::endl;
        }
    }
    else if (event == "MESSAGE_SENT") {
    }
    else if (event == "USER_ONLINE") {
        if (data != name) {
            std::cout << "[NOTIFICATION] " << name << ": " << data 
                      << " is now online" << std::endl;
        }
    }
    else if (event == "USER_OFFLINE") {
        if (data != name) {
            std::cout << "[NOTIFICATION] " << name << ": " << data 
                      << " is now offline" << std::endl;
        }
    }
}

/**
 * @brief Join a chat room
 * @param room The chat room to join
 */
void User::joinChatRoom(ChatRoom* room) {
    if (room == nullptr) {
        std::cerr << "Error: Cannot join null chat room" << std::endl;
        return;
    }
    
    if (isInChatRoom(room)) {
        std::cerr << "User " << name << " is already in chat room " << room->getName() << std::endl;
        return;
    }
    
    chatRooms.push_back(room);
    
    room->registerUser(this);
    
    room->addObserver(this);
    
    std::cout << name << " joined chat room: " << room->getName() << std::endl;
}

/**
 * @brief Leave a chat room
 * @param room The chat room to leave
 */
void User::leaveChatRoom(ChatRoom* room) {
    if (room == nullptr) {
        std::cerr << "Error: Cannot leave null chat room" << std::endl;
        return;
    }

    for (auto it = chatRooms.begin(); it != chatRooms.end(); ++it) {
        if (*it == room) {
            chatRooms.erase(it);

            room->removeUser(this);

            room->removeObserver(this);

            std::cout << name << " left chat room: " << room->getName() << std::endl;
            return;
        }
    }

    std::cerr << "User " << name << " is not in chat room " << room->getName() << std::endl;

}

/**
 * @brief Set the user's online status
 * @param status True for online, false for offline
 */
void User::setOnlineStatus(bool status) {
    if (isOnline != status) {
        isOnline = status;
        
        std::string event = isOnline ? "USER_ONLINE" : "USER_OFFLINE";
        for (ChatRoom* room : chatRooms) {
            if (room != nullptr) {
                room->notifyObservers(event, name);
            }
        }
        
        std::cout << name << " is now " << (isOnline ? "online" : "offline") << std::endl;
    }
}

/**
 * @brief Get the user's name
 * @return The user's name
 */
std::string User::getName() const {
    return name;
}

/**
 * @brief Get the user's online status
 * @return True if online, false if offline
 */
bool User::getOnlineStatus() const {
    return isOnline;
}

/**
 * @brief Get the list of chat rooms the user belongs to
 * @return Vector of ChatRoom pointers
 */
std::vector<ChatRoom*> User::getChatRooms() const {
    return chatRooms;
}

/**
 * @brief Get the current command queue size
 * @return Number of commands in queue
 */
size_t User::getCommandQueueSize() const {
    return commandQueue.size();
}

/**
 * @brief Helper method to check if user is in a specific chat room
 * @param room The chat room to check
 * @return True if user is in the room, false otherwise
 */
bool User::isInChatRoom(ChatRoom* room) const {
    for (ChatRoom* r : chatRooms) {
        if (r == room) {
            return true;
        }
    }
    return false;
}
