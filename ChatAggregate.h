#ifndef CHATAGGREGATE_H
#define CHATAGGREGATE_H

// Forward declarations
class UserIterator;
class MessageIterator;

/**
 * @brief Abstract aggregate interface for the Iterator pattern
 * 
 * This class defines the interface that concrete aggregates must implement
 * to provide iterator creation methods. It represents the Aggregate role
 * in the Iterator design pattern.
 */
class ChatAggregate {
public:
    /**
     * @brief Virtual destructor for proper inheritance
     */
    virtual ~ChatAggregate() = default;
    
    /**
     * @brief Create an iterator for users
     * @return Pointer to UserIterator for traversing users
     */
    virtual UserIterator* createUserIterator() = 0;
    
    /**
     * @brief Create an iterator for messages
     * @return Pointer to MessageIterator for traversing messages
     */
    virtual MessageIterator* createMessageIterator() = 0;
};

#endif