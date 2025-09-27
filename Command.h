#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class ChatRoom;
class User;

/**
 * @brief Abstract base Command class for the Command pattern
 * 
 * This class encapsulates a request as an object, allowing for
 * parameterization of clients with different requests, queuing
 * of requests, and logging of requests.
 */

class Command {
    protected:
        ChatRoom* room;
        User* fromUser;
        std::string message;

    public:

        /**
         * @brief Constructor for Command
         * @param room Pointer to the ChatRoom where the command will be executed
         * @param user Pointer to the User who initiated the command
         * @param msg The message content
         */

        Command(ChatRoom* room, User* user, const std::string& msg);
        
        /**
         * @brief Virtual destructor for proper inheritance
         */

        virtual ~Command();
        
        /**
         * @brief Pure virtual execute method
         * 
         * This method must be implemented by all concrete command classes
         * to define the specific action to be performed.
         */
        virtual void execute() = 0;
};

#endif 