#ifndef CHATITERATOR_H
#define CHATITERATOR_H

// Forward declarations
class User;

/**
 * @brief Abstract base iterator class for the Iterator pattern
 * 
 * This class defines the interface for iterating through collections
 * in the chat system.
 */
class ChatIterator {
protected:
    int currentIndex;

public:
    // Constructor
    ChatIterator();
    
    // Virtual destructor
    virtual ~ChatIterator();
    
    // Pure virtual methods that must be implemented by concrete iterators
    virtual bool hasNext() = 0;
    virtual void next() = 0;
    virtual User* current() = 0;
};

#endif