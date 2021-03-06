#ifndef FILE_ENCODER_H
#define FILE_ENCODER_H

#include <string>

#include "bitstring.h"
#include "encoder.h"
#include "reader.h"
#include "writer.h"

// Class for encoding files
class file_encoder {
   public:
    // Constructor from filename
    file_encoder() = delete;
    explicit file_encoder(std::string filename)
        : filename(filename), cnt(count_file()), enc(cnt), message_size(0) {}

    // Encodes file to "to"
    void encode_file(std::string to);
    void encode_file(std::string to, std::ostream& p_out);  // with progress bar
    void encode_file();  // or to automatically made filename
    void encode_file(std::ostream& p_out);

    // Writes dictionary (simple one) to "to"
    void write_dictionary(std::string to);
    void write_dictionary();  // same as higher

    // This can return other dict(not frequency) if needed
    std::map<byte, symbol_code> get_dict() { return enc.get_map(); }

   private:
    std::string filename;
    counter cnt;
    encoder enc;
    ullong message_size;

    counter count_file();
};

#endif  // FILE_ENCODER_H
