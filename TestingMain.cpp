#include <iostream>
#include <string>

#include "Users.h"

/**
 * @file TestingMain.cpp
 * @brief Basic testing starting with User and ChatRoom instantiation
 * @author Rachel Clifford and Sofia Finlayson
 * @date 10/09/2025
 */

int main() {
    std::cout << "PetSpace Chat System - Basic Testing" << std::endl;
    std::cout << "Starting with User instantiation...\n" << std::endl;

    try {
        std::cout << "User Creation " << std::endl;

        User* alice = new User("Rachel");
        User* bob = new User("Sofia"); 
        User* charlie = new User("Bobby");

        std::cout << "Created user: " << alice->getName() << std::endl;
        std::cout << "Created user: " << bob->getName() << std::endl;
        std::cout << "Created user: " << charlie->getName() << std::endl;

        std::cout << "\nTesting initial user states:" << std::endl;
        std::cout << alice->getName() << " is online: " << alice->getOnlineStatus() << std::endl;
        std::cout << alice->getName() << " chat rooms: " << alice->getChatRooms().size() << std::endl;
        std::cout << alice->getName() << " command queue: " << alice->getCommandQueueSize() << std::endl;

        std::cout << "\nTesting online status changes:" << std::endl;
        alice->setOnlineStatus(true);
        bob->setOnlineStatus(true);
        charlie->setOnlineStatus(true);

        std::cout << alice->getName() << " is now online: " << alice->getOnlineStatus() << std::endl;
        std::cout << bob->getName() << " is now online: " << bob->getOnlineStatus() << std::endl;
        std::cout << charlie->getName() << " is now online: " << charlie->getOnlineStatus() << std::endl;

        std::cout << "Basic user creation test completed!\n" << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error during testing: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
