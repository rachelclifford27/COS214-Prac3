#ifndef NOTIFICATION_SUBJECT_H
#define NOTIFICATION_SUBJECT_H

#include <vector>
#include <string>
#include "NotificationObserver.h"

/**
 * @file NotificationSubject.h
 * @brief Abstract subject interface for the Observer pattern
 * @author Sofia Finlayson
 * @date 09/09/2025
 */

/**
 * @class NotificationSubject
 * @brief Abstract subject interface for managing observers
 * 
 * This interface defines the contract for all subjects in the Observer pattern.
 * Subjects maintain a list of observers and notify them when events occur.
 */
class NotificationSubject {
protected:
    std::vector<NotificationObserver*> observers;

public:
    /**
     * @brief Virtual destructor for proper cleanup
     */
    virtual ~NotificationSubject() = default;
    
    /**
     * @brief Add an observer to the notification list
     * @param observer The observer to add
     * 
     * Registers an observer to receive notifications about events
     */
    virtual void addObserver(NotificationObserver* observer);
    
    /**
     * @brief Remove an observer from the notification list
     * @param observer The observer to remove
     * 
     * Unregisters an observer from receiving notifications
     */
    virtual void removeObserver(NotificationObserver* observer);
    
    /**
     * @brief Notify all registered observers about an event
     * @param event The type of event that occurred
     * @param data Additional data about the event
     * 
     * Calls the update method on all registered observers
     */
    virtual void notifyObservers(const std::string& event, const std::string& data) = 0;
};

#endif