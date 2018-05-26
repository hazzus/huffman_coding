#ifndef READER_H
#define READER_H

#include <fstream>
#include <iostream>
#include <vector>

#include "bitstring.h"
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

    reader(std::string filename, ullong length)
        : in(filename, std::ios::binary), left_to_read(length) {
        if (in.fail()) {
            in.close();
            throw std::runtime_error("No such file " + filename);
        }
    }

    std::vector<byte> read_byte_data(size_t amount);

    bitstring read_bool_data(size_t amount);

    ~reader() { in.close(); }

    bool eof() { return in.eof(); }

   private:
    std::ifstream in;

    ullong left_to_read;
};

#endif  // READER_H
