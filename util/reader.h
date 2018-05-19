#ifndef READER_H
#define READER_H

#include <fstream>
#include <iostream>
#include <vector>

#include "constants.h"

class reader {
   public:
    reader() = delete;
    reader(std::string filename) : in(filename, std::ios::binary) {
        if (in.fail()) {
            in.close();
            throw std::runtime_error("No such file " + filename);
        }
    }

    std::vector<byte> read_byte_data(size_t amount);

    std::vector<bool> read_bool_data(size_t amount);

    ~reader() { in.close(); }

    bool eof() { return in.eof(); }

   private:
    std::ifstream in;
};

#endif  // READER_H
