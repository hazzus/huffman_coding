#include "decoder.h"

std::vector<byte> decoder::decode(std::vector<bool> data) {
    size_t i = 0;
    data.insert(data.begin(), remain.begin(), remain.end());
    remain.clear();
    std::vector<byte> result;
    while (i < data.size()) {
        code_tree::node* current = source_tree.root;
        size_t last = data.size() - i;
        while (current != nullptr && !current->end && i < data.size()) {
            if (data[i++] == false) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (current == nullptr)
            throw std::runtime_error(
                "No such code in the tree (It actually then contains only 1 "
                "code)");
        if (i == data.size() && !current->end) {
            remain.insert(remain.end(), data.end() - last, data.end());
        } else
            result.push_back(current->symbol);
    }
    return result;
}
