#ifndef ENCODER_H
#define ENCODER_H

#include <vector>
#include "bitstring.h"
#include "constants.h"
#include "counter.h"
#include "tree.h"

// Basic encoder of any data
class encoder {
   public:
    encoder() = delete;
    // Constructs the encoder source tree from symbols counter
    encoder(counter const& cnt) : source_tree(cnt) {}

    // Other constructors may be placed here, but are they nesseccary?

    // Implements encoding basing on the tree
    bitstring encode(std::vector<byte> data);

    // Returns the map <clear byte - huffman code>
    std::map<byte, symbol_code> get_map() { return source_tree.get_code_map(); }

   private:
    code_tree source_tree;
};

#endif  // ENCODER_H
