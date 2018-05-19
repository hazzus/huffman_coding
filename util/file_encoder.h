#ifndef FILE_ENCODER_H
#define FILE_ENCODER_H

#include <string>

#include "encoder.h"
#include "reader.h"
#include "writer.h"

// Class for encoding files
class file_encoder {
   public:
    // Constructor from filename
    file_encoder() = delete;
    explicit file_encoder(std::string filename)
        : filename(filename), cnt(count_file()), enc(cnt) {}

    // Encodes file to "to"
    void encode_file(std::string to);
    void encode_file(std::string to, std::ostream& p_out);  // with progress bar
    void encode_file();  // or to automatically made filename
    void encode_file(std::ostream& p_out);

    // Writes dictionary (simple one) to "to"
    void write_dictionary(std::string to);
    void write_dictionary();  // same as higher

    // This can return other dict(not frequency) if needed
    std::map<byte, std::vector<bool>> get_dict() { return enc.get_map(); }

   private:
    std::string filename;
    counter cnt;
    encoder enc;

    counter count_file();
};

#endif  // FILE_ENCODER_H
