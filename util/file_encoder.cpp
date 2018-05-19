#include "file_encoder.h"

counter file_encoder::count_file() {
    reader input(filename);
    counter counter;
    while (!input.eof()) {
        counter.update(input.read_byte_data(MAX_READ));
    }
    return counter;
}

void file_encoder::encode_file(std::string to) {
    reader in(filename);
    writer out(to);
    while (!in.eof()) {
        out.write_bool_data(enc.encode(in.read_byte_data(MAX_READ)));
    }
}

void file_encoder::encode_file(std::string to, std::ostream& p_out) {
    reader in(filename);
    writer out(to);
    ullong done = 0;
    double prev = 0;
    p_out
        << "Progress: 0%                                                  100%"
        << std::endl;
    p_out << "            ";
    while (!in.eof()) {
        ullong cur = (++done * 50) / cnt.get_times();
        for (; prev < cur; prev++) {
            p_out << "|";
        }
        p_out.flush();
        out.write_bool_data(enc.encode(in.read_byte_data(MAX_READ)));
    }
    p_out << std::endl;
}

void file_encoder::encode_file() { encode_file(filename + ".huf"); }
void file_encoder::encode_file(std::ostream& p_out) {
    encode_file(filename + ".huf", p_out);
}

void file_encoder::write_dictionary(std::string to) {
    std::ofstream out_dict(to);
    auto d = cnt.get_freq();
    for (size_t i = 0; i < MAX_DATA + 1; i++) {
        if (d.find(reinterpret_cast<const unsigned char&>(i)) != d.end()) {
            out_dict << d.at(i) << " ";
        } else {
            out_dict << 0 << " ";
        }
    }
    out_dict.close();
}

void file_encoder::write_dictionary() {
    write_dictionary(filename + ".hufdict");
}
