#include "code.h"

bool bitstring::empty() { return value.empty(); }

size_t bitstring::size() { return value.size(); }

void bitstring::push_back(symbol_code x) {
    if (value.size() > 0) {
        value[value.size() - 1] |= (x.get_code() >> (last_size));
        if (x.size() + last_size >= 64) {
            if (last_size != 0) {
                value.push_back(x.get_code() << (64 - last_size));
            } else {
                value.push_back(0);
            }
            last_size = x.size() + last_size - 64;
        } else {
            last_size += x.size();
        }
    } else {
        value.push_back(x.get_code());
        if (x.size() == 64) {
            value.push_back(0);
        }
        last_size = x.size() % 64;
    }
}

bool symbol_code::empty() { return length == 0; }

void symbol_code::push_back(bool x) {
    if (x) {
        code |= ((uint64_t)1 << (63 - length));
    }
    length++;
}

void symbol_code::pop_back() { length--; }

byte symbol_code::size() { return length; }

uint64_t symbol_code::get_code() { return code; }

uint64_t bitstring::operator[](size_t index) {
    uint64_t x = value[index / 64];
    uint shift = (63 - (index % 64));
    return ((x >> shift) & 1);
}

uint64_t bitstring::get_real(size_t index) { return value[index]; }

void bitstring::clear() {
    value.clear();
    last_size = 0;
}
