#include "writer.h"

void writer::write_bool_data(bitstring data) {
    if (data.size() == 0) return;
    for (size_t i = 0; i < data.size() - 1; i++) {
        remain.push_back(data.get_real(i));
    }
    remain.push_back(
        symbol_code(data.get_real(data.size() - 1), data.get_last()));
    std::string result;
    result.reserve(data.size() << 3);
    for (size_t i = 0; i < remain.size() - 1; i++) {
        uint64_t x = remain.get_real(i);
        for (size_t j = 8; j <= 64; j += 8) {
            result.push_back(static_cast<byte>((x >> (64 - j)) & 255));
        }
    }
    if (remain.get_last() != 0) {
        uint64_t x = remain.get_real(remain.size() - 1);
        size_t i = 8;
        if (remain.get_last() > 8) {
            for (; i < remain.get_last(); i += 8) {
                result.push_back(static_cast<byte>((x >> (64 - i)) & 255));
            }

            bitstring new_remain;
            if (i == remain.get_last()) {
                result.push_back(static_cast<byte>((x >> (64 - i)) & 255));
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
    } else {
        remain.clear();
    }
    written += result.size() * 8;
    out << result;
}

void writer::write_byte_data(std::vector<byte> data) {
    std::string result;
    result.reserve(data.size());
    for (byte x : data) {
        result.push_back(x);
    }
    out << result;
}

ullong writer::get_written_amount() { return written + remain.get_last(); }

writer::~writer() {
    std::string res;
    if (remain.size() > 0) {
        res.push_back(static_cast<byte>((remain.get_real(0) >> (56)) & 255));
    }
    out << res;
    out.close();
}
