#ifndef COUNTER_H
#define COUNTER_H

#include "constants.h"

// Structure for counting frequency of bytes in file
// Similary accumulates symbols, no file binding
class counter {
   public:
    counter();

    // adds data for counting
    void update(std::vector<byte> const& data);

    // return amount of symbols
    ullong get(size_t index);

    // constructs map symbol - frequency for constructing tree or writing
    // dictionary(like frequencies)
    std::map<byte, ullong> get_freq();

    ullong get_times();

   private:
    ullong count[MAX_DATA + 1];
    ullong times;
};

#endif  // COUNTER_H
