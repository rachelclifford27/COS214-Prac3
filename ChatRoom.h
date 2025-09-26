#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>
#include <string>
#include <map>
#include <list>
#include <iostream>

// Forward declarations
class User;
class NotificationObserver;
class UserIterator;
class MessageIterator;

class ChatRoom {
    private:
        std::vector<User*> users;
        std::vector<std::string> chatHistory;
        std::vector<NotificationObserver*> observers;
    public:
        // Constructor and Destructor
        ChatRoom();
        virtual ~ChatRoom();
        
        // User management methods
        void registerUser(User* user);
        void removeUser(User* user);

        //add to UML
        User* getUser(const std::string& name);
        
        // Message handling methods
        void sendMessage(const std::string& message, User* fromUser);
        void saveMessage(const std::string& message, User* fromUser);
        
        // Iterator creation methods
        UserIterator* createUserIterator();
        MessageIterator* createMessageIterator();
        
        // Observer pattern methods
        void addObserver(NotificationObserver* observer);
        void removeObserver(NotificationObserver* observer);
        void notifyObservers(const std::string& event, const std::string& data);
        
        //Add to UML
        // Getter methods
        const std::vector<User*>& getUsers() const;
        const std::vector<std::string>& getChatHistory() const;
        const std::vector<NotificationObserver*>& getObservers() const;
        
        // Utility methods
        int getUserCount() const;
        bool hasUser(User* user) const;
        void clearChatHistory();
};

#endif 