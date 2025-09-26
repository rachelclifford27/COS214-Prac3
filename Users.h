#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class NotificationObserver;

class ChatRoom;
class Command;

/**
 * @file User.h
 * @brief User class that participates in Mediator, Command, and Observer patterns
 * @author [Your Name]
 * @date [Current Date]
 */

/**
 * @class User
 * @brief Represents a user in the PetSpace chat system
 * 
 * This class participates in multiple design patterns:
 * - Mediator Pattern: Acts as a colleague that communicates through ChatRoom mediator
 * - Command Pattern: Acts as an invoker that creates and executes commands
 * - Observer Pattern: Acts as a concrete observer that receives notifications
 */
class User {
private:
    std::string name;                           
    std::vector<ChatRoom*> chatRooms;          
    std::vector<Command*> commandQueue;        
    bool isOnline;                             

public:
    /**
     * @brief Constructor for User
     * @param userName The name of the user
     */
    User(const std::string& userName);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~User();
    
    // Mediator Pattern Methods
    /**
     * @brief Send a message to a specific chat room
     * @param message The message content
     * @param room The chat room to send the message to
     * 
     * This method creates SendMessageCommand and SaveMessageCommand objects
     * and adds them to the command queue for execution
     */
    virtual void sendMessage(const std::string& message, ChatRoom* room);
    
    /**
     * @brief Receive a message from a chat room
     * @param message The message content
     * @param fromUser The user who sent the message
     * @param room The chat room where the message was sent
     * 
     * This method is called by the ChatRoom mediator when a message is delivered
     */
    virtual void receive(const std::string& message, User* fromUser, ChatRoom* room);
    
    // Command Pattern Methods (User as Invoker)
    /**
     * @brief Add a command to the command queue
     * @param command The command to add
     */
    void addCommand(Command* command);
    
    /**
     * @brief Execute all commands in the queue
     * 
     * Executes commands in FIFO order and clears the queue
     */
    void executeAll();
    
    // Observer Pattern Methods (User as ConcreteObserver)
    /**
     * @brief Update method called when observed events occur
     * @param event The type of event that occurred
     * @param data Additional data about the event
     * @param room The chat room where the event occurred
     * 
     * Implementation of Observer pattern - called by ChatRoom when events occur
     */
    virtual void update(const std::string& event, const std::string& data, ChatRoom* room);
    
    // User Management Methods
    /**
     * @brief Join a chat room
     * @param room The chat room to join
     */
    void joinChatRoom(ChatRoom* room);
    
    /**
     * @brief Leave a chat room
     * @param room The chat room to leave
     */
    void leaveChatRoom(ChatRoom* room);
    
    /**
     * @brief Set the user's online status
     * @param status True for online, false for offline
     */
    void setOnlineStatus(bool status);
    
    // Getters
    /**
     * @brief Get the user's name
     * @return The user's name
     */
    std::string getName() const;
    
    /**
     * @brief Get the user's online status
     * @return True if online, false if offline
     */
    bool getOnlineStatus() const;
    
    /**
     * @brief Get the list of chat rooms the user belongs to
     * @return Vector of ChatRoom pointers
     */
    std::vector<ChatRoom*> getChatRooms() const;
    
    /**
     * @brief Get the current command queue size
     * @return Number of commands in queue
     */
    size_t getCommandQueueSize() const;

protected:
    /**
     * @brief Helper method to check if user is in a specific chat room
     * @param room The chat room to check
     * @return True if user is in the room, false otherwise
     */
    bool isInChatRoom(ChatRoom* room) const;
};

#endif