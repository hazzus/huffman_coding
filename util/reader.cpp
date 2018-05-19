#include "reader.h"

std::vector<byte> reader::read_byte_data(size_t amount) {
    size_t i = 0;
    char c;
    std::vector<byte> result;
    while (i < amount && in.get(c)) {
        result.push_back(c);
        i++;
    }
    return result;
}

std::vector<bool> reader::read_bool_data(size_t amount) {
    std::vector<byte> chars = read_byte_data(amount);
    std::vector<bool> result;
    for (byte c : chars) {
        for (size_t i = 0; i < 8; i++) result.push_back((c >> (7 - i)) & 1);
    }
    return result;
}
