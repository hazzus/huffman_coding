#include "encoder.h"

bitstring encoder::encode(std::vector<byte> data) {
    bitstring result;
    result.reserve(data.size() >> 3);
    for (byte s : data) {
        symbol_code const& code_of_s = source_tree.get_code(s);
        result.push_back(code_of_s);
    }
    return result;
}
