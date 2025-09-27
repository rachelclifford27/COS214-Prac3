#include "CtrlCat.h"
#include "Users.h"
#include <iostream>
#include <algorithm>

/**
 * @file CtrlCat.cpp
 * @brief Implementation of CtrlCat concrete mediator
 * @author [Your Name]
 * @date [Current Date]
 */

// Static member definition
const std::string CtrlCat::ROOM_NAME = "CtrlCat";

/**
 * @brief Constructor for CtrlCat chat room
 */
CtrlCat::CtrlCat() : ChatRoom() {
    std::cout << "CtrlCat room created - Welcome to the feline programming paradise!" << std::endl;
}

/**
 * @brief Virtual destructor
 */
CtrlCat::~CtrlCat() {
    std::cout << "CtrlCat room destroyed - The cats have logged off!" << std::endl;
}

/**
 * @brief Register a user with the CtrlCat chat room
 * @param user The user to register
 * 
 * Adds the user to the room and notifies other users
 */
void CtrlCat::registerUser(User* user) {
    if (user == nullptr) {
        std::cerr << "Error: Cannot register null user in CtrlCat" << std::endl;
        return;
    }
    
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        std::cerr << "User " << user->getName() << " is already registered in CtrlCat" << std::endl;
        return;
    }
    
    users.push_back(user);
    
    std::cout << "🐱 " << user->getName() << " has pounced into CtrlCat! " 
              << "Ready to discuss cats and code! 🐱" << std::endl;
    
    notifyObservers("USER_JOINED", user->getName());
    
    std::cout << "CtrlCat now has " << users.size() << " coding cats online." << std::endl;
}

/**
 * @brief Remove a user from the CtrlCat chat room
 * @param user The user to remove
 * 
 * Removes the user from the room and notifies other users
 */
void CtrlCat::removeUser(User* user) {
    if (user == nullptr) {
        std::cerr << "Error: Cannot remove null user from CtrlCat" << std::endl;
        return;
    }
    
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        users.erase(it);
        
        std::cout << "🐱 " << user->getName() << " has left CtrlCat. " 
                  << "The cat has wandered off to chase other code! 🐱" << std::endl;
        
        notifyObservers("USER_LEFT", user->getName());
        
        std::cout << "CtrlCat now has " << users.size() << " coding cats online." << std::endl;
    } else {
        std::cerr << "User " << user->getName() << " is not in CtrlCat room" << std::endl;
    }
}

/**
 * @brief Get the name of this chat room
 * @return The room name "CtrlCat"
 */
std::string CtrlCat::getName() const {
    return ROOM_NAME;
}