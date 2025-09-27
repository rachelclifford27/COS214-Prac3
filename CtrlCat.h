#ifndef CTRLCAT_H
#define CTRLCAT_H

#include "ChatRoom.h"

/**
 * @file CtrlCat.h
 * @brief CtrlCat concrete mediator class - a cat-themed chat room
 * @author [Your Name]
 * @date [Current Date]
 */

/**
 * @class CtrlCat
 * @brief Concrete mediator for cat-themed discussions
 * 
 * CtrlCat is a concrete implementation of the ChatRoom mediator.
 * It handles all communication between users interested in cats and
 * programming topics.
 */
class CtrlCat : public ChatRoom {
private:
    static const std::string ROOM_NAME;

public:
    /**
     * @brief Constructor for CtrlCat chat room
     */
    CtrlCat();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~CtrlCat();
    
    /**
     * @brief Register a user with the CtrlCat chat room
     * @param user The user to register
     * 
     * Adds the user to the room and notifies other users
     */
    void registerUser(User* user);
    
    /**
     * @brief Remove a user from the CtrlCat chat room
     * @param user The user to remove
     * 
     * Removes the user from the room and notifies other users
     */
    void removeUser(User* user);
    
    /**
     * @brief Get the name of this chat room
     * @return The room name "CtrlCat"
     */
    std::string getName() const;
};

#endif