#ifndef FILE_DECODER_H
#define FILE_DECODER_H

#include <string>
#include "decoder.h"

// Special class for decoding files
class file_decoder {
   public:
    // Constructor from name of encoded file and dict
    file_decoder() = delete;
    file_decoder(std::string filename, std::string dictname)
        : filename(filename), f(pull_freq(dictname)), dec(f) {}

    // Change the dictionary of decoding
    void change_dictionary(std::string dictname);

    // Decodes file into "to"
    void decode_file(std::string to);
    void decode_file();  // or to automaticaly done filename
    void decode_file(std::string to, std::ostream& p_out);  // for progress bar
    void decode_file(std::ostream& p_out);

    // Checks if was right after decoding (there may be some collision)
    bool check_dictionary(std::string decoded);

   private:
    std::string filename;
    std::map<byte, ullong> f;
    decoder dec;
    ullong message_length;

    ullong times;

    std::map<byte, ullong> pull_freq(std::string dictname);
};

#endif  // FILE_DECODER_H
