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
    // Constructor
    MessageIterator(const std::vector<std::string>& messageHistory);
    
    // Destructor
    ~MessageIterator();
    
    // Override virtual methods from ChatIterator
    bool hasNext() override;
    void next() override;
    User* current() override; // Returns nullptr (messages aren't Users)
    
    // Additional method specific to message iteration
    std::string currentMessage();
};

#endif 