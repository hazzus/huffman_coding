#include "decoder.h"

std::vector<byte> decoder::decode(bitstring data) {
    std::vector<byte> result;
    if (data.size() == 0) return result;
    size_t i = 0;
    size_t total_size = (data.size() - 1) * 64 + data.get_last();
    while (i < total_size) {
        while (current != nullptr && !current->end && i < total_size) {
            if (!data[i++]) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (current == nullptr) {
            throw std::runtime_error("No such code in tree");
        }
        if (current->end) {
            result.push_back(current->symbol);
            current = source_tree.root;
        }
    }
    return result;
}
