#include "SendMessageCommand.h"
#include "ChatRoom.h"
#include "Users.h"

// SendMessageCommand implementation
SendMessageCommand::SendMessageCommand(ChatRoom* room, User* user, const std::string& msg)
    : Command(room, user, msg) {
}

SendMessageCommand::~SendMessageCommand() {
    // Destructor - base class handles cleanup
}

void SendMessageCommand::execute() {
    if (room != nullptr && fromUser != nullptr && !message.empty()) {
        // Use ChatRoom's sendMessage method to deliver message to all users
        // This will distribute the message to all users in the chat room
        room->sendMessage(message, fromUser);
    }
}