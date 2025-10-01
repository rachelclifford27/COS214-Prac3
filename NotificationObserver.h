#ifndef NOTIFICATION_OBSERVER_H
#define NOTIFICATION_OBSERVER_H

#include <string>

class ChatRoom;

/**
 * @file NotificationObserver.h
 * @brief Abstract observer interface for the Observer pattern
 * @author Sofia Finlayson
 * @date 09/09/2025
 */

/**
 * @class NotificationObserver
 * @brief Abstract observer interface for receiving notifications
 * 
 * This interface defines the contract for all observers in the PetSpace system.
 * Concrete observers must implement the update method to receive notifications
 * about events occurring in chat rooms.
 */
class NotificationObserver {
public:
    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~NotificationObserver() = default;
    
    /**
     * @brief Pure virtual update method called when observed events occur
     * @param event The type of event that occurred
     * @param data Additional data about the event
     * @param room The chat room where the event occurred
     * 
     * This method must be implemented by all concrete observers to handle
     * notifications from subjects they are observing.
     */
    virtual void update(const std::string& event, const std::string& data, ChatRoom* room) = 0;
};

#endif