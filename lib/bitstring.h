#ifndef CODE_H
#define CODE_H

#include "constants.h"

class symbol_code {
   public:
    symbol_code() : code(0), length(0) {}
    symbol_code(uint64_t x, byte l) : code(x), length(l) {}
    symbol_code(byte x) : code((uint64_t)x << 56), length(8) {}
    bool empty();

    void push_back(bool x);
    void pop_back();

    byte size();

    uint64_t get_code();

   private:
    uint64_t code;
    byte length;
};

class bitstring {
   public:
    bitstring() : value(), last_size(0) {}

    bool empty();

    size_t size();

    void push_back(symbol_code x);
    void push_back(uint64_t x);

    bool operator[](size_t index);

    byte get_last() { return last_size; }

    uint64_t const& get_real(size_t index);

    void clear();

    void reserve(size_t n);

   private:
    std::vector<uint64_t> value;
    byte last_size;
};

#endif  // CODE_H
