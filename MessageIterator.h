/**
 * @file MessageIterator.h
 * @brief Iterator implementation for traversing chat message collections
 * @author Rachel Clifford
 * @date 19/09/2025
 */

#ifndef MESSAGEITERATOR_H
#define MESSAGEITERATOR_H

#include "ChatIterator.h"
#include <vector>
#include <string>

// Forward declarations
class User;

/**
 * @brief Concrete iterator for iterating through chat messages
 * 
 * This class implements the Iterator pattern to traverse
 * a collection of chat message strings. Note: Since messages
 * are strings, current() returns nullptr for User* but provides
 * currentMessage() method.
 */
class MessageIterator : public ChatIterator {
private:
    std::vector<std::string> chatHistory;

public:
    /**
     * @brief Constructor for MessageIterator
     * 
     * Creates an iterator for the given message history. The iterator maintains
     * its own copy of the message list to ensure thread safety and consistency
     * during iteration.
     * 
     * @param messageHistory Reference to the vector of message strings to iterate over
     */
    MessageIterator(const std::vector<std::string>& messageHistory);
    
    /**
     * @brief Destructor
     * 
     * Cleans up the iterator resources. Message strings are copied so no
     * external cleanup is needed.
     */
    ~MessageIterator();
    
    /**
     * @brief Check if there are more messages to iterate over
     * 
     * @return bool True if there are more messages available, false if at the end
     */
    bool hasNext() override;

    /**
     * @brief Move to the next message in the collection
     * 
     * Advances the internal pointer to the next message. Should only be called
     * after checking hasNext() returns true.
     */
    void next() override;

    /**
     * @brief Get the current user (always returns nullptr)
     * 
     * This method is part of the ChatIterator interface but is not applicable
     * for message iteration since messages are strings, not User objects.
     * Use currentMessage() instead to get the actual message content.
     * 
     * @return User* Always returns nullptr for message iteration
     */
    User* current() override; 
    
    /**
     * @brief Get the current message string
     * 
     * Returns the message at the current iterator position. This is the
     * primary method for accessing message content during iteration.
     * 
     * @return std::string The current message, or empty string if at the end
     */    
    std::string currentMessage();
};

#endif 