#include "Dogorithm.h"
#include "Users.h"
#include <iostream>
#include <algorithm>

/**
 * @file Dogorithm.cpp
 * @brief Implementation of Dogorithm concrete mediator
 * @author Sofia Finlayson
 * @date 10/09/2025
 */

// Static member definition
const std::string Dogorithm::ROOM_NAME = "Dogorithm";

/**
 * @brief Constructor for Dogorithm chat room
 */
Dogorithm::Dogorithm() : ChatRoom() {
    std::cout << "Dogorithm room created - Where algorithms meet adorable dogs!" << std::endl;
}

/**
 * @brief Virtual destructor
 */
Dogorithm::~Dogorithm() {
    std::cout << "Dogorithm room destroyed - The pack has disbanded!" << std::endl;
}

/**
 * @brief Register a user with the Dogorithm chat room
 * @param user The user to register
 * 
 * Adds the user to the room and notifies other users
 */
void Dogorithm::registerUser(User* user) {
    if (user == nullptr) {
        std::cerr << "Error: Cannot register null user in Dogorithm" << std::endl;
        return;
    }
    
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        std::cerr << "User " << user->getName() << " is already registered in Dogorithm" << std::endl;
        return;
    }
    
    users.push_back(user);
    
    std::cout << user->getName() << " has joined the pack in Dogorithm! " 
              << "Ready to fetch some algorithms and discuss good dogs!" << std::endl;
    
    notifyObservers("USER_JOINED", user->getName());
    
    std::cout << "Dogorithm pack now has " << users.size() << " coding companions." << std::endl;
}

/**
 * @brief Remove a user from the Dogorithm chat room
 * @param user The user to remove
 * 
 * Removes the user from the room and notifies other users
 */
void Dogorithm::removeUser(User* user) {
    if (user == nullptr) {
        std::cerr << "Error: Cannot remove null user from Dogorithm" << std::endl;
        return;
    }
    
    auto it = std::find(users.begin(), users.end(), user);
    if (it != users.end()) {
        // Remove user from the room
        users.erase(it);
        
        // Farewell message specific to Dogorithm
        std::cout << user->getName() << " has left the Dogorithm pack. " 
                  << "Gone to chase new coding adventures!" << std::endl;
        
        // Notify remaining users about the departure
        notifyObservers("USER_LEFT", user->getName());
        
        std::cout << "Dogorithm pack now has " << users.size() << " coding companions." << std::endl;
    } else {
        std::cerr << "User " << user->getName() << " is not in Dogorithm room" << std::endl;
    }
}

/**
 * @brief Get the name of this chat room
 * @return The room name "Dogorithm"
 */
std::string Dogorithm::getName() const {
    return ROOM_NAME;
}