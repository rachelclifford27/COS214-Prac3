#ifndef LOGMESSAGECOMMAND_H
#define LOGMESSAGECOMMAND_H

#include "Command.h"

// LogMessageCommand - logs message activity for audit/debugging purposes
class LogMessageCommand : public Command {
public:
    // Constructor
    LogMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    
    // Destructor
    ~LogMessageCommand();
    
    // Override execute method
    void execute() override;
};

#endif // LOGMESSAGECOMMAND_H