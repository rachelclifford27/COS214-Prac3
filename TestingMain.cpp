#include <iostream>
#include <string>

#include "Users.h"
#include "ChatRoom.h"
#include "CtrlCat.h"
#include "Dogorithm.h"

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

        User* sofia = new User("Rachel");
        User* rachel = new User("Sofia"); 
        User* bobby = new User("Bobby");

        std::cout << "Created user: " << sofia->getName() << std::endl;
        std::cout << "Created user: " << rachel->getName() << std::endl;
        std::cout << "Created user: " << bobby->getName() << std::endl;

        std::cout << "\nTesting initial user states:" << std::endl;
        std::cout << sofia->getName() << " is online: " << sofia->getOnlineStatus() << std::endl;
        std::cout << sofia->getName() << " chat rooms: " << sofia->getChatRooms().size() << std::endl;
        std::cout << sofia->getName() << " command queue: " << sofia->getCommandQueueSize() << std::endl;

        std::cout << "\nTesting online status changes:" << std::endl;
        sofia->setOnlineStatus(true);
        rachel->setOnlineStatus(true);
        bobby->setOnlineStatus(true);

        std::cout << sofia->getName() << " is now online: " << sofia->getOnlineStatus() << std::endl;
        std::cout << rachel->getName() << " is now online: " << rachel->getOnlineStatus() << std::endl;
        std::cout << bobby->getName() << " is now online: " << bobby->getOnlineStatus() << std::endl;

        std::cout << "Basic user creation test completed!\n" << std::endl;

        //mediator
        std::cout << "\nMediator Pattern" << std::endl;

        std::cout << "\nCreating chat rooms" << std::endl;

        CtrlCat* ctrlCat = new CtrlCat();
        Dogorithm* dogorithm = new Dogorithm();
        std::cout << "Chat rooms created: " << ctrlCat->getName() << " and " << dogorithm->getName() << std::endl;

        std::cout << "\nUser Registration with Chat Rooms" << std::endl;
        std::cout << "\nSofia (Name1) joining CtrlCat" << std::endl;
        sofia->joinChatRoom(ctrlCat);

        std::cout << "\nSofia (Name1) joining Dogorithm..." << std::endl;
        sofia->joinChatRoom(dogorithm);
        
        std::cout << "\nRachel (Name2) joining CtrlCat..." << std::endl;
        rachel->joinChatRoom(ctrlCat);
        
        std::cout << "\nBobby (Name3) joining Dogorithm..." << std::endl;
        bobby->joinChatRoom(dogorithm);

        std::cout << "\nVerifying Chat Room Memberships" << std::endl;
        std::cout << "CtrlCat has " << ctrlCat->getUserCount() << " users" << std::endl;
        std::cout << "Dogorithm has " << dogorithm->getUserCount() << " users" << std::endl;
        
        std::cout << "\nSofia is in " << sofia->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Rachel is in " << rachel->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Bobby is in " << bobby->getChatRooms().size() << " chat room(s)" << std::endl;

        std::cout << "\nTesting hasUser() method" << std::endl;
        std::cout << "CtrlCat has Sofia: " << ctrlCat->hasUser(sofia) << std::endl;
        std::cout << "CtrlCat has Rachel: " << ctrlCat->hasUser(rachel) << std::endl;
        std::cout << "CtrlCat has Bobby: " << ctrlCat->hasUser(bobby) << std::endl;
        
        std::cout << "\nDogorithm has Sofia: " << dogorithm->hasUser(sofia) << std::endl;
        std::cout << "Dogorithm has Rachel: " << dogorithm->hasUser(rachel) << std::endl;
        std::cout << "Dogorithm has Bobby: " << dogorithm->hasUser(bobby) << std::endl;
        
        std::cout << "\nTesting User Removal" << std::endl;
        std::cout << "Charlie leaving Dogorithm..." << std::endl;
        bobby->leaveChatRoom(dogorithm);
        
        std::cout << "Dogorithm now has " << dogorithm->getUserCount() << " users" << std::endl;
        std::cout << "Bobby is now in " << bobby->getChatRooms().size() << " chat room(s)" << std::endl;
        std::cout << "Dogorithm has Bobby: " << dogorithm->hasUser(bobby) << std::endl;
        
        std::cout << "\nDemonstrating Mediator" << std::endl;
        std::cout << "Sofia is in multiple rooms but users don't communicate directly" << std::endl;
        std::cout << "All communication goes through the ChatRoom mediator" << std::endl;
        std::cout << "Sofia's rooms:" << std::endl;
        for (size_t i = 0; i < sofia->getChatRooms().size(); i++) {
            std::cout << "  - " << sofia->getChatRooms()[i]->getName() << std::endl;
        }
        
        std::cout << "\nMediator pattern test completed!\n" << std::endl;

        //observer
        

    } catch (const std::exception& e) {
        std::cout << "Error during testing: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
