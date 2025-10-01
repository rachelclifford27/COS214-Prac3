#ifndef DOGORITHM_H
#define DOGORITHM_H

#include "ChatRoom.h"

/**
 * @file Dogorithm.h
 * @brief Dogorithm concrete mediator class - a dog-themed chat room
 * @author Sofia Finlayson
 * @date 10/09/2025
 */

/**
 * @class Dogorithm
 * @brief Concrete mediator for dog-themed discussions
 * 
 * Dogorithm is a concrete implementation of the ChatRoom mediator.
 * It handles all communication between users interested in dogs and
 * algorithm/programming topics.
 */
class Dogorithm : public ChatRoom {
private:
    static const std::string ROOM_NAME; ///< Static room name

public:
    /**
     * @brief Constructor for Dogorithm chat room
     */
    Dogorithm();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Dogorithm();
    
    /**
     * @brief Register a user with the Dogorithm chat room
     * @param user The user to register
     * 
     * Adds the user to the room and notifies other users
     */
    void registerUser(User* user);
    
    /**
     * @brief Remove a user from the Dogorithm chat room
     * @param user The user to remove
     * 
     * Removes the user from the room and notifies other users
     */
    void removeUser(User* user);
    
    /**
     * @brief Get the name of this chat room
     * @return The room name "Dogorithm"
     */
    std::string getName() const;
};

#endif