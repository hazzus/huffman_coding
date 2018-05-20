#ifndef DECODER_H
#define DECODER_H

#include "code.h"
#include "constants.h"
#include "tree.h"

// Simple decoder class
class decoder {
   public:
    /* constructors from diffrent structures of data, creates encoding tree
     basing on the structure */
    decoder(code_tree decoding_tree) : source_tree(decoding_tree), current(source_tree.root), remain() {}

    decoder(std::vector<std::pair<byte, ullong>> alphabet)
        : source_tree(alphabet), current(source_tree.root), remain() {}

    decoder(std::map<byte, symbol_code> codes) : source_tree(codes), current(source_tree.root), remain() {}

    decoder(std::map<byte, ullong> counts) : source_tree(counts), current(source_tree.root), remain() {}

    // Decode func, gets chars from bools(stored as bits)
    std::vector<byte> decode(bitstring data);

    // before destructing must be checked that remain only contains zeroes!?
    bool check();

   private:
    code_tree source_tree;
    code_tree::node* current;
    std::vector<bool> remain;
};

#endif  // DECODER_H
