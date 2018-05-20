#include "writer.h"

void writer::write_bool_data(bitstring data) {
    if (data.size() == 0) return;
    for (size_t i = 0; i < data.size() - 1; i++) {
        remain.push_back(symbol_code(data.get_real(i), 64));
    }
    remain.push_back(
        symbol_code(data.get_real(data.size() - 1), data.get_last()));

    for (size_t i = 0; i < remain.size() - 1; i++) {
        uint64_t x = remain.get_real(i);
        for (size_t j = 8; j <= 64; j += 8) {
            out << (byte)((x >> (64 - j)) & 255);
        }
    }
    if (remain.get_last() != 0) {
        uint64_t x = remain.get_real(remain.size() - 1);
        size_t i = 8;
        if (remain.get_last() > 8) {
            for (; i < remain.get_last(); i += 8) {
                out << (byte)((x >> (64 - i)) & 255);
            }

            bitstring new_remain;
            if (i == remain.get_last()) {
                out << (byte)((x >> (64 - i)) & 255);
                remain.clear();
            } else if (i > remain.get_last()) {
                new_remain.push_back(symbol_code(
                    x << (i - 8), static_cast<byte>(remain.get_last() % 8)));
                remain = new_remain;
            }
        } else {
            bitstring new_remain;
            new_remain.push_back(
                symbol_code(x & (255ull << 56), remain.get_last()));
            remain = new_remain;
        }
    }
}

void writer::write_byte_data(std::vector<byte> data) {
    for (byte x : data) {
        out << x;
    }
}

writer::~writer() {
    if (remain.size() > 0) {
        out << (byte)((remain.get_real(0) >> (56)) & 255);
    }
    out.close();
}
