#include <gtest/gtest.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <../util/file_decoder.h>
#include <../util/file_encoder.h>
#include <decoder.h>
#include <encoder.h>
#include <fstream>

#include <../util/file_decoder.cpp>
#include <../util/file_encoder.cpp>
#include <../util/reader.cpp>
#include <../util/writer.cpp>

TEST(correctness, encode_decode) {
    std::string s = "мама мыла раму";
    std::vector<byte> x;
    x.insert(x.end(), s.begin(), s.end());
    counter c;
    c.update(x);

    encoder e(c);
    decoder d(e.get_map());

    EXPECT_TRUE(d.decode(e.encode(x)) == x);
}

TEST(correctness, size_one) {
    const size_t coef = 2048 * 1024;
    std::vector<byte> x(coef, 255);
    counter c;
    c.update(x);

    encoder e(c);
    decoder d(e.get_map());

    EXPECT_TRUE(e.encode(x).size() == coef);
    EXPECT_TRUE(d.decode(e.encode(x)) == x);
}

TEST(correctness, split_decode) {
    std::string s = "мама мыла раму и меня тоже мыла";
    std::vector<byte> x, y, full;
    full.insert(full.end(), s.begin(), s.end());
    x.insert(x.end(), s.begin(), s.begin() + (s.size() >> 1));
    y.insert(y.end(), s.begin() + (s.size() >> 1), s.end());
    counter c;
    c.update(full);

    encoder e(c);
    decoder d(e.get_map());

    std::vector<byte> res = d.decode(e.encode(x));
    std::vector<byte> next = d.decode(e.encode(y));

    res.insert(res.end(), next.begin(), next.end());

    EXPECT_TRUE(res == full);
}

TEST(correctness, file_encode_decode) {
    std::string file = "../easy_test/my_test";
    std::ofstream out(file + ".in");
    std::string test = "a little test of micro file, really 26316&^&%*!@";
    out << test;
    out.close();
    file_encoder fe(file + ".in");
    fe.encode_file(file + ".huf");
    fe.write_dictionary(file + ".hufdict");

    file_decoder fd(file + ".huf", file + ".hufdict");
    fd.decode_file(file + ".out");

    std::ifstream in(file + ".out");
    std::string res;
    getline(in, res);
    in.close();

    EXPECT_TRUE(res == test && fd.check_dictionary(file + ".out"));
}

TEST(correctness, file_empty) {
    std::string file = "../empty_test/my_test";
    std::ofstream out(file + ".in");
    std::string test = "";
    out.close();
    file_encoder fe(file + ".in");
    fe.encode_file(file + ".huf");
    fe.write_dictionary(file + ".hufdict");

    file_decoder fd(file + ".huf", file + ".hufdict");
    fd.decode_file(file + ".out");

    std::ifstream in(file + ".out");
    std::string res;
    getline(in, res);
    in.close();

    EXPECT_TRUE(res == test);
}

TEST(correctness, wrong_code) {
    const size_t coef = 2048 * 1024;
    std::vector<byte> x(coef, 255);
    counter c;
    c.update(x);

    encoder e(c);
    decoder d(e.get_map());
    std::vector<bool> res = e.encode(x);
    res.insert(res.end(), 1, 1);
    EXPECT_ANY_THROW(d.decode(res));
}
