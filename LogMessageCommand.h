/**
 * @file LogMessageCommand.h
 * @brief Command implementation for logging message activities
 * @author Rachel Clifford
 * @date 20/09/2025
 */

#ifndef LOGMESSAGECOMMAND_H
#define LOGMESSAGECOMMAND_H

#include "Command.h"

/**
 * @brief Command for logging message activities
 * 
 * This command logs message activity to the console for audit and debugging purposes.
 * In a production system, this could be extended to log to files, databases,
 * or external logging services.
 */
class LogMessageCommand : public Command {
public:

    /**
     * @brief Constructor for LogMessageCommand
     * 
     * @param room Pointer to the ChatRoom where the message was sent
     * @param user Pointer to the User who sent the message
     * @param msg The message content to be logged
     */
    LogMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    
    /**
     * @brief Destructor
     * 
     * Base class handles cleanup of common members.
     */
    ~LogMessageCommand();
    
    /**
     * @brief Execute the logging command
     * 
     * Logs message activity to console with timestamp, user name, room name,
     * and message content. Only executes if all required parameters are valid.
     */
    void execute() override;
    
};

#endif 