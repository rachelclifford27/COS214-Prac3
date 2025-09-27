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
    // Constructor
    UserIterator(const std::vector<User*>& userList);
    
    // Destructor
    ~UserIterator();
    
    // Override virtual methods from ChatIterator
    bool hasNext() override;
    void next() override;
    User* current() override;
};

#endif 