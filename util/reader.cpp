#include "reader.h"

std::vector<byte> reader::read_byte_data(size_t amount) {
    std::vector<byte> result(amount);
    in.read(reinterpret_cast<char*>(result.data()), amount);
    result.resize(in.gcount());
    return result;
}

bitstring reader::read_bool_data(size_t amount) {
    std::vector<byte> chars = read_byte_data(amount);
    bitstring result;
    result.reserve(amount >> 3);
    for (byte c : chars) {
        if (left_to_read >= 8) {
            result.push_back(symbol_code(c));
        } else {
            symbol_code last(c);
            last.set_length(left_to_read);
            result.push_back(last);
        }
        left_to_read -= 8;
    }
    return result;
}
