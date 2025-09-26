#include "SendMessageCommand.h"
#include "ChatRoom.h"
#include "User.h"

// SendMessageCommand implementation
SendMessageCommand::SendMessageCommand(ChatRoom* room, User* user, const std::string& msg)
    : Command(room, user, msg) {
}

SendMessageCommand::~SendMessageCommand() {
    // Destructor - base class handles cleanup
}

void SendMessageCommand::execute() {
    if (chatRoom != nullptr && fromUser != nullptr && !message.empty()) {
        // Use ChatRoom's sendMessage method to deliver message to all users
        // This will distribute the message to all users in the chat room
        chatRoom->sendMessage(message, fromUser);
    }
}