#include "encoder.h"

std::vector<bool> encoder::encode(std::vector<byte> data) {
    std::vector<bool> result;
    for (byte s : data) {
        std::vector<bool> const& code_of_s = source_tree.get_code(s);
        result.insert(result.end(), code_of_s.begin(), code_of_s.end());
    }
    return result;
}
