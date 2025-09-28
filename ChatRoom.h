/**
 * @file ChatRoom.h
 * @brief Header file for ChatRoom class implementing chat room functionality
 * @author Rachel Clifford
 * @date 10/09/2025
 */


#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>
#include <string>
#include <map>
#include <list>
#include <iostream>
#include "ChatAggregate.h"
#include "NotificationSubject.h"

// Forward declarations
class User;
class NotificationObserver;
class UserIterator;
class MessageIterator;
class Command;

/**
 * @brief ChatRoom class implementing chat room functionality with multiple design patterns
 * 
 * This class serves as the main chat room implementation that supports:
 * - Observer pattern for notifications
 * - Command pattern for message handling
 * - Iterator pattern for traversing users and messages
 * - Aggregate pattern for managing collections
 * 
 * The ChatRoom manages users, message history, observers, and command queues
 * to provide a complete chat room experience.
 */

class ChatRoom : public ChatAggregate, public NotificationSubject {
  protected:
        std::vector<User*> users;
        std::vector<std::string> chatHistory;
        //std::vector<NotificationObserver*> observers;
        std::vector<Command*> commandQueue;
        std::string roomName;
    public:
        /**
         * @brief Default constructor
         * 
         * Initializes an empty chat room with default name "DefaultRoom"
         */
        // Constructor and Destructor
        ChatRoom();

        /**
         * @brief Virtual destructor
         * 
         * Cleans up command queue and clears collections.
         * Note: Users and observers are not deleted as they may be managed elsewhere.
         */
        virtual ~ChatRoom();
        
        // User management methods

        /**
         * @brief Register a user to the chat room
         * 
         * Adds a user to the chat room if not already registered.
         * Notifies all observers when a user joins.
         * 
         * @param user Pointer to the user to register (must not be nullptr)
         */

        void registerUser(User* user);

        /**
         * @brief Remove a user from the chat room
         * 
         * Removes the specified user from the chat room and notifies observers.
         * 
         * @param user Pointer to the user to remove (must not be nullptr)
         */

        void removeUser(User* user);

        /**
        * @brief Get the name of the chat room (pure virtual implementation)
        * 
        * @return std::string The name of the chat room
        */

        virtual std::string getName() const = 0;

        //add to UML
        /**
         * @brief Get a user by name
         * 
         * @param name The name of the user to find
         * @return User* Pointer to the user if found, nullptr otherwise
         */
        
        User* getUser(const std::string& name);
        
        // Message handling methods

        /**
         * @brief Send a message to all users in the chat room
         * 
         * Distributes the message to all users except the sender,
         * saves it to chat history, and notifies observers.
         * 
         * @param message The message content to send (must not be empty)
         * @param fromUser Pointer to the user sending the message (must not be nullptr)
         */

        void sendMessage(const std::string& message, User* fromUser);

        /**
         * @brief Save a message to the chat history
         * 
         * Formats and stores the message in the chat history with username.
         * Format: [Username]: Message\n
         * 
         * @param message The message content to save (must not be empty)
         * @param fromUser Pointer to the user who sent the message (must not be nullptr)
         */

        void saveMessage(const std::string& message, User* fromUser);

        /**
         * @brief Receive an incoming message
         * 
         * Handles incoming messages by delegating to sendMessage.
         * 
         * @param message The received message content
         * @param fromUser Pointer to the user who sent the message
         */

        void receiveMessage(const std::string& message, User* fromUser);

        /**
         * @brief Create an iterator for users
         * 
         * Creates and returns a UserIterator for traversing the user collection.
         * Caller is responsible for deleting the returned iterator.
         * 
         * @return UserIterator* Pointer to a new UserIterator instance
         */
        UserIterator* createUserIterator();

        /**
         * @brief Create an iterator for messages
         * 
         * Creates and returns a MessageIterator for traversing the chat history.
         * Caller is responsible for deleting the returned iterator.
         * 
         * @return MessageIterator* Pointer to a new MessageIterator instance
         */
        MessageIterator* createMessageIterator();
        
        /**
         * @brief Notify all observers about an event
         * 
         * Sends notification to all registered observers with event details.
         * 
         * @param event The type of event that occurred
         * @param data Additional data about the event
         */
        void notifyObservers(const std::string& event, const std::string& data);
        
        /**
         * @brief Add a command to the execution queue
         * 
         * Queues a command for later execution. The command will be executed
         * when executeAll() is called.
         * 
         * @param command Pointer to the command to queue (must not be nullptr)
         */
        void addCommand(Command* command);
        
        /**
         * @brief Execute all queued commands
         * 
         * Executes all commands in the queue in FIFO order, then clears
         * the queue and deletes the command objects.
         */
        void executeAll();

        //Add to UML
        // Getter methods
        /**
         * @brief Get the list of users in the chat room
         * 
         * @return const std::vector<User*>& Reference to the users vector
         */
        const std::vector<User*>& getUsers() const;

        /**
         * @brief Get the chat history
         * 
         * @return const std::vector<std::string>& Reference to the chat history vector
         */
        const std::vector<std::string>& getChatHistory() const;

        /**
         * @brief Get the list of observers
         * 
         * @return const std::vector<NotificationObserver*>& Reference to the observers vector
         */
        const std::vector<NotificationObserver*>& getObservers() const;
        

        /**
         * @brief Get the name of the chat room
         * 
         * @return std::string The name of the chat room
         */
        std::string getName() const;

        // Utility methods

        /**
         * @brief Get the number of users in the chat room
         * 
         * @return int The count of registered users
         */
        int getUserCount() const;

        /**
         * @brief Check if a user is in the chat room
         * 
         * @param user Pointer to the user to check for
         * @return bool True if the user is in the room, false otherwise
         */
        bool hasUser(User* user) const;

        /**
         * @brief Clear all chat history
         * 
         * Removes all messages from the chat history.
         */
        void clearChatHistory();
};

#endif 