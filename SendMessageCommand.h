/**
 * @file SendMessageCommand.h
 * @brief Command implementation for sending messages to chat room users
 * @author Rachel Clifford
 * @date 20/09/2025
 */

#ifndef SENDMESSAGECOMMAND_H
#define SENDMESSAGECOMMAND_H

#include "Command.h"

/**
 * @brief Command for sending messages in a chat room
 * 
 * This command encapsulates the action of sending a message to all users
 * in a chat room. It delegates to the ChatRoom's sendMessage method to
 * distribute the message to all participants.
 */

class SendMessageCommand : public Command {
public:

    /**
     * @brief Constructor for SendMessageCommand
     * 
     * @param room Pointer to the ChatRoom where the message will be sent
     * @param user Pointer to the User who is sending the message
     * @param msg The message content to be sent to all users
     */
    SendMessageCommand(ChatRoom* room, User* user, const std::string& msg);
    
    /**
     * @brief Destructor
     * 
     * Base class handles cleanup of common members.
     */
    ~SendMessageCommand();
    
    /**
     * @brief Execute the send message command
     * 
     * Sends the message to all users in the chat room using the ChatRoom's
     * sendMessage method. Only executes if all required parameters are valid.
     */
    void execute() override;
};

#endif