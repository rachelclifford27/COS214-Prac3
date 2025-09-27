#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class ChatRoom;
class User;

class Command {
    protected:
        ChatRoom* room;
        User* fromUser;
        std::string message;

    public:
        // Constructor
        Command(ChatRoom* room, User* user, const std::string& msg);
        
        // Virtual destructor
        virtual ~Command();
        
        // Pure virtual execute method
        virtual void execute() = 0;
};

#endif 