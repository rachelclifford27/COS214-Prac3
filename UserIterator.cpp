#include "UserIterator.h"
#include "Users.h"

/**
 * @file UserIterator.cpp
 * @brief Implementation of the UserIterator class
 */

/**
 * @brief Constructor for UserIterator
 * @param userList Reference to vector of User pointers to iterate over
 */
UserIterator::UserIterator(const std::vector<User*>& userList) : ChatIterator() {
    users = userList;
    currentIndex = 0;
}

/**
 * @brief Destructor for UserIterator
 */
UserIterator::~UserIterator() {
    // Clear the vector but don't delete User objects (they're managed elsewhere)
    users.clear();
}

/**
 * @brief Check if there are more users to iterate over
 * @return True if there are more users, false otherwise
 */
bool UserIterator::hasNext() {
    return currentIndex < static_cast<int>(users.size());
}

/**
 * @brief Move to the next user in the collection
 */
void UserIterator::next() {
    if (hasNext()) {
        currentIndex++;
    }
}

/**
 * @brief Get the current user in the iteration
 * @return Pointer to the current User, or nullptr if at end
 */
User* UserIterator::current() {
    if (currentIndex >= 0 && currentIndex < static_cast<int>(users.size())) {
        return users[currentIndex];
    }
    return nullptr;
}