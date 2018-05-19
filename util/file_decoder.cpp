#include "file_decoder.h"
#include "reader.h"
#include "writer.h"

void file_decoder::decode_file(std::string to) {
    reader in(filename);
    writer out(to);
    while (!in.eof()) {
        out.write_byte_data(dec.decode(in.read_bool_data(MAX_READ)));
    }
}

void file_decoder::decode_file(std::string to, std::ostream& p_out) {
    reader in(filename);
    writer out(to);
    ullong done = 0;
    double prev = 0;
    p_out
        << "Progress: 0%                                                  100%"
        << std::endl;
    p_out << "            ";
    while (!in.eof()) {
        ullong cur = (++done * 50) / times;
        for (; prev < cur; prev++) {
            p_out << "|";
        }
        p_out.flush();
        out.write_byte_data(dec.decode(in.read_bool_data(MAX_READ)));
    }
    p_out << std::endl;
}

void file_decoder::decode_file() { decode_file(filename + "_decoded.out"); }
void file_decoder::decode_file(std::ostream& p_out) {
    decode_file(filename + "_decoded.out", p_out);
}

bool file_decoder::check_dictionary(std::string decoded) {
    counter c;
    reader input(decoded);
    while (!input.eof()) {
        c.update(input.read_byte_data(MAX_READ));
    }
    if (f != c.get_freq()) {
        return false;
    } else {
        return true;
    }
}

void file_decoder::change_dictionary(std::string dictname) {
    new (&dec) decoder(pull_freq(dictname));
}

std::map<byte, ullong> file_decoder::pull_freq(std::string dictname) {
    times = 0;
    std::ifstream in_dict(dictname);
    if (in_dict.fail()) {
        throw std::runtime_error("No such file" + dictname);
    }
    std::map<byte, ullong> frequency;
    ullong x;
    uint z = 0;
    ullong symbol_counter = 0;
    while (in_dict >> x) {
        if (x != 0) {
            frequency.insert({z, x});
            symbol_counter += x;
        }
        if (symbol_counter > MAX_READ) {
            times += symbol_counter / MAX_READ;
            symbol_counter %= MAX_READ;
        }
        z++;
        if (z == 257)
            throw std::runtime_error(
                "Wrong dictionary format, too many numbers found");  // too many
                                                                     // dict
    }
    if (z != 256)
        throw std::runtime_error(
            "Wrong dictionary format, too few numbers found");
    if (symbol_counter != 0) {
        times++;
    }
    in_dict.close();
    return frequency;
}
