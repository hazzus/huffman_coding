#ifndef ENCODING_TREE_H
#define ENCODING_TREE_H

#include <algorithm>
#include <array>
#include "bitstring.h"
#include "constants.h"
#include "counter.h"

/*
This class implements basic coding tree of huffman algoritm
*/
class code_tree {
   public:
    /*
    Structure of tree node, it holds the origin symbol, amount counted in
    instream or file and code representation.
    */
    struct node {
        byte symbol;
        size_t amount;
        bool end;

        node* left;
        node* right;

        node()
            : symbol(0), amount(0), end(false), left(nullptr), right(nullptr) {}
        node(byte symbol, size_t amount)
            : symbol(symbol),
              amount(amount),
              end(true),
              left(nullptr),
              right(nullptr) {}
    };

    // Constructor from counter of symbols in file(for encoding)
    code_tree(counter cnt) : code_tree(cnt.get_freq()) {}

    // Constructor from dictionary(vector of pairs) (for decoding)
    code_tree(std::vector<std::pair<byte, ullong>> alphabet);

    // Constructor from dictionary(map) (for decoding)
    code_tree(std::map<byte, ullong> alphabet);

    // Constructor from map clear byte - huffcode, (for even faster work?)
    code_tree(std::map<byte, symbol_code> codes);

    // Returns huffman code of specific byte
    symbol_code const& get_code(byte s);

    // Returns map <clear byte - huffman code>
    std::map<byte, symbol_code> get_code_map() {
        std::map<byte, symbol_code> result;
        for (unsigned i = 0; i != 256; ++i)
            if (!code[i].empty()) result.insert({i, code[i]});
        return result;
    }

    // this must be private but is really hard to retreave
    node* root;

    ~code_tree();

   private:
    std::array<symbol_code, 256> code;
    std::map<byte, ullong> freq;

    // Implementation of tree build
    void build_tree(std::vector<node*> dict);

    void dfs_assign(node* vertex, symbol_code code);

    void specific_build(std::pair<byte, symbol_code> p);

    void del(node*& cur);
};

#endif  // ENCODING_TREE_H
