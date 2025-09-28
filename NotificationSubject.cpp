#include "NotificationSubject.h"
#include <algorithm>
#include <iostream>

/**
 * @file NotificationSubject.cpp
 * @brief Implementation of NotificationSubject abstract class
 * @author Sofia Finlayson
 * @date 09/09/2025
 */

/**
 * @brief Add an observer to the notification list
 * @param observer The observer to add
 * 
 * Registers an observer to receive notifications about events
 */
void NotificationSubject::addObserver(NotificationObserver* observer) {
    if (observer == nullptr) {
        std::cerr << "Error: Cannot add null observer" << std::endl;
        return;
    }
    
    // Check if observer is already registered
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        std::cerr << "Warning: Observer already registered" << std::endl;
        return;
    }
    
    observers.push_back(observer);
}

/**
 * @brief Remove an observer from the notification list
 * @param observer The observer to remove
 * 
 * Unregisters an observer from receiving notifications
 */
void NotificationSubject::removeObserver(NotificationObserver* observer) {
    if (observer == nullptr) {
        std::cerr << "Error: Cannot remove null observer" << std::endl;
        return;
    }
    
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    } else {
        std::cerr << "Warning: Observer not found for removal" << std::endl;
    }
}