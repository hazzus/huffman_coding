#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <string>
#include <vector>
#include "bitstring.h"
#include "constants.h"

class writer {
   public:
    writer() = delete;
    writer(std::string filename)
        : filename(filename),
          out(this->filename, std::ios::binary),

          written(0),
          remain() {}
    // Check permission and while working too!

    void write_bool_data(bitstring data);

    void write_byte_data(std::vector<byte> data);

    ullong get_written_amount();

    ~writer();

   private:
    std::string filename;
    std::ofstream out;
    ullong written;

    bitstring remain;
};

#endif  // WRITER_H
