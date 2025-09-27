#include "MessageIterator.h"

/**
 * @file MessageIterator.cpp
 * @brief Implementation of the MessageIterator class
 */

/**
 * @brief Constructor for MessageIterator
 * @param messageHistory Reference to vector of message strings to iterate over
 */
MessageIterator::MessageIterator(const std::vector<std::string>& messageHistory) : ChatIterator() {
    chatHistory = messageHistory;
    currentIndex = 0;
}

/**
 * @brief Destructor for MessageIterator
 */
MessageIterator::~MessageIterator() {
    // Clear the vector
    chatHistory.clear();
}

/**
 * @brief Check if there are more messages to iterate over
 * @return True if there are more messages, false otherwise
 */
bool MessageIterator::hasNext() {
    return currentIndex < static_cast<int>(chatHistory.size());
}

/**
 * @brief Move to the next message in the collection
 */
void MessageIterator::next() {
    if (hasNext()) {
        currentIndex++;
    }
}

/**
 * @brief Get current User pointer (always returns nullptr for message iterator)
 * @return nullptr since messages are not User objects
 * 
 * Note: This method is required by the ChatIterator interface but doesn't
 * make sense for message iteration. Use currentMessage() instead.
 */
User* MessageIterator::current() {
    return nullptr; // Messages are not User objects
}

/**
 * @brief Get the current message string in the iteration
 * @return Current message string, or empty string if at end
 */
std::string MessageIterator::currentMessage() {
    if (currentIndex >= 0 && currentIndex < static_cast<int>(chatHistory.size())) {
        return chatHistory[currentIndex];
    }
    return ""; // Return empty string if out of bounds
}