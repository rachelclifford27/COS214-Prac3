#ifndef SENDMESSAGECOMMAND_H
#define SENDMESSAGECOMMAND_H

#include "Command.h"

class SendMessageCommand : public Command {
public:
    // Constructor
    SendMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    
    // Destructor
    ~SendMessageCommand();
    
    // Override execute method
    void execute() override;
};

#endif