#include "counter.h"

counter::counter() {
    for (size_t i = 0; i < MAX_DATA + 1; i++) {
        count[i] = 0;
    }
    times = 0;
    // memset?
}

ullong counter::get(size_t index) { return count[index]; }

void counter::update(std::vector<byte> const& data) {
    times++;
    for (byte sym : data) {
        count[sym]++;
    }
}

std::map<byte, ullong> counter::get_freq() {
    std::map<byte, ullong> dict;
    for (size_t i = 0; i < MAX_DATA + 1; i++) {
        if (get(i) != 0) {
            dict.insert({i, get(i)});
        }
    }
    return dict;
}

ullong counter::get_times() { return times; }
