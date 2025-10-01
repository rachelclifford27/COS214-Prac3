#include "ChatIterator.h"

/**
 * @file ChatIterator.cpp
 * @brief Implementation of the base ChatIterator class
 */

/**
 * @brief Constructor for ChatIterator base class
 */
ChatIterator::ChatIterator() : currentIndex(0) {
    // Initialize current index to 0
}

/**
 * @brief Virtual destructor for ChatIterator base class
 */
ChatIterator::~ChatIterator() {
    // Base destructor - no cleanup needed
}