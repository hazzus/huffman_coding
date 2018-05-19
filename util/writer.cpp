#include "writer.h"
#include "constants.h"

void writer::write_bool_data(std::vector<bool> data) {
    data.insert(data.begin(), remain.begin(), remain.end());
    remain.clear();
    size_t i = 0;
    if (data.size() >= 8) {
        for (; i < data.size() - 8; i += 8) {
            char cur = 0;
            for (size_t j = i, s = 7; s < 8 && j < data.size(); j++, s--) {
                cur |= (data[j] << s);
            }
            out << cur;
        }
    }
    if (i + 8 != data.size()) {
        remain.insert(remain.end(), data.begin() + i, data.end());
    } else {
        char cur = 0;
        for (size_t j = i, s = 7; s < 8 && j < data.size(); j++, s--) {
            cur |= (data[j] << s);
        }
        out << cur;
    }
}

void writer::write_byte_data(std::vector<byte> data) {
    for (byte x : data) {
        out << x;
    }
}

writer::~writer() {
    if (remain.size() > 0) {
        remain.insert(remain.end(), 8 - remain.size(), 0);
        char last = 0;
        for (size_t i = 0; i < 8; i++) {
            last |= (remain[i] << (7 - i));
        }
        out << last;
    }
    out.close();
}
