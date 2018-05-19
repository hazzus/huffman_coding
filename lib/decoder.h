#ifndef DECODER_H
#define DECODER_H

#include "constants.h"
#include "tree.h"

// Simple decoder class
class decoder {
   public:
    /* constructors from diffrent structures of data, creates encoding tree
     basing on the structure */
    decoder(code_tree decoding_tree) : source_tree(decoding_tree) {}

    decoder(std::vector<std::pair<byte, ullong>> alphabet)
        : source_tree(alphabet), remain() {}

    decoder(std::map<byte, std::vector<bool>> codes)
        : source_tree(codes), remain() {}

    decoder(std::map<byte, ullong> counts) : source_tree(counts), remain() {}

    // Decode func, gets chars from bools(stored as bits)
    std::vector<byte> decode(std::vector<bool> data);

    // before destructing must be checked that remain only contains zeroes!?
    bool check();

   private:
    code_tree source_tree;
    std::vector<bool> remain;
};

#endif  // DECODER_H
