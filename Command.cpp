#include "Command.h"
#include "ChatRoom.h"
#include "Users.h"

// Base Command class implementation
Command::Command(ChatRoom* room, User* user, const std::string& msg)
    : room (room), fromUser(user), message(msg) {
}

Command::~Command() {
    // Base destructor - no cleanup needed for pointers we don't own
}