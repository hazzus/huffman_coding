#include "reader.h"

std::vector<byte> reader::read_byte_data(size_t amount) {
    std::vector<byte> result;
    char* c = new char[amount];
    in.read(c, amount);
    result.insert(result.end(), c, c + in.gcount());
    return result;
}

bitstring reader::read_bool_data(size_t amount) {
    std::vector<byte> chars = read_byte_data(amount);
    bitstring result;
    for (byte c : chars) {
        result.push_back(symbol_code(c));
    }
    return result;
}
