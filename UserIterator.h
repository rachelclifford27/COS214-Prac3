/**
 * @file UserIterator.h
 * @brief Iterator implementation for traversing User collections
 * @author Rachel Clifford
 * @date 19/09/2025
 */

#ifndef USERITERATOR_H
#define USERITERATOR_H

#include "ChatIterator.h"
#include <vector>

// Forward declarations
class User;

/**
 * @brief Concrete iterator for iterating through users
 * 
 * This class implements the Iterator pattern to traverse
 * a collection of User objects.
 */
class UserIterator : public ChatIterator {
private:
    std::vector<User*> users;

public:
     /**
     * @brief Constructor for UserIterator
     * 
     * Creates an iterator for the given user list. The iterator maintains
     * its own copy of the user list to ensure thread safety and consistency
     * during iteration.
     * 
     * @param userList Reference to the vector of User pointers to iterate over
     */
    UserIterator(const std::vector<User*>& userList);
    
    /**
     * @brief Destructor
     * 
     * Cleans up the iterator. Note that User objects are not deleted
     * as they are managed by the ChatRoom.
     */
    ~UserIterator();
    
    /**
     * @brief Check if there are more users to iterate over
     * 
     * @return bool True if there are more users available, false if at the end
     */
    bool hasNext() override;

    /**
     * @brief Move to the next user in the collection
     * 
     * Advances the internal pointer to the next user. Should only be called
     * after checking hasNext() returns true.
     */
    void next() override;

    /**
     * @brief Get the current user
     * 
     * Returns a pointer to the user at the current iterator position.
     * 
     * @return User* Pointer to the current user, or nullptr if at the end
     */
    User* current() override;
};

#endif 