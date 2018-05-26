#include <fstream>
#include <iostream>
#include "bitstring.h"
#include "decoder.h"
#include "encoder.h"
#include "file_decoder.cpp"
#include "file_decoder.h"
#include "file_encoder.cpp"
#include "file_encoder.h"
#include "reader.cpp"
#include "writer.cpp"

using namespace std;

int main() {
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

    cout << res;
    cout << endl;
}
