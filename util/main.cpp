#include <time.h>
#include <iostream>
#include "file_decoder.h"
#include "file_encoder.h"

using namespace std;

void wait_command() {
    cout << ">>> ";
    cout.flush();
}

void start() {
    cout << "Wellcome to huffman-code shell!\nWrite \"help\" for commands "
            "list\n";
    wait_command();
}

void show_help() {
    cout << "Command list (* stands for optional args):" << endl;
    cout << "   encode <input file> <output file*> <dictionary*> - encodes file"
         << endl;
    cout << "   decode <input file> <dictionary> <output file*>  - decodes file"
         << endl;
    cout << "   exit                                             - exit from "
            "shell"
         << endl;
    // cout << "   cd <dir>    " << endl;
}

void encode_it(vector<string> const& command) {
    try {
        cout << "Encoding..." << endl;
        clock_t start = clock();
        file_encoder fe(command[1]);
        if (command.size() == 2) {
            fe.encode_file(cout);
            fe.write_dictionary();
        } else if (command.size() == 3) {
            fe.encode_file(command[2], cout);
            fe.write_dictionary();
        } else {
            fe.encode_file(command[2], cout);
            fe.write_dictionary(command[3]);
        }
        clock_t end = clock();
        cout << "Done! Time spent: "
             << (double)(end - start) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << endl;
    }
}

void decode_it(vector<string> const& command) {
    try {
        cout << "Decoding..." << endl;
        clock_t start = clock();
        file_decoder fd(command[1], command[2]);
        if (command.size() == 3) {
            fd.decode_file(cout);
        } else {
            fd.decode_file(command[3], cout);
        }
        clock_t end = clock();
        cout << "Done! Time spent: "
             << (double)(end - start) / CLOCKS_PER_SEC * 1000.0 << "ms" << endl;
    } catch (runtime_error e) {
        cout << "Error occured: \n" << e.what() << endl;
    }
}

vector<string> parse_command(string command) {
    vector<string> result;
    size_t prev = 0;
    for (size_t i = 0; i < command.length(); i++) {
        if (command[i] == ' ') {
            if (i > prev) result.push_back(command.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    result.push_back(command.substr(prev));
    return result;
}

int main() {
    start();
    string input;
    while (getline(cin, input)) {
        vector<string> command = parse_command(input);
        if (command[0] == "encode") {
            if (command.size() > 4 || command.size() < 2) {
                cout << "Wrong argument amount" << endl;
            } else {
                encode_it(command);
            }
        } else if (command[0] == "decode") {
            if (command.size() > 4 || command.size() < 3) {
                cout << "Wrong arguments amount" << endl;
            } else {
                decode_it(command);
            }
        } else if (command[0] == "exit") {
            exit(0);
        } else if (command[0] == "help") {
            show_help();
        } else {
            cout << "No such command" << endl;
        }
        wait_command();
    }
}
