#include "LogMessageCommand.h"
#include "ChatRoom.h"
#include "Users.h"
#include <iostream>

// LogMessageCommand implementation
LogMessageCommand::LogMessageCommand(ChatRoom* room, User* user, const std::string& msg)
    : Command(room, user, msg) {
}

LogMessageCommand::~LogMessageCommand() {
    // Destructor - base class handles cleanup
}

void LogMessageCommand::execute() {
    if (room != nullptr && fromUser != nullptr && !message.empty()) {
        // Log the message activity to console for audit/debugging purposes
        // In a real system, this could log to a file, database, or external logging service
        std::cout << "[LOG] Timestamp: NOW" 
                  << " | User: " << fromUser->getName() 
                  << " | Room: ChatRoom"
                  << " | Message: \"" << message << "\"" << std::endl;
        
        
                  
    }
}