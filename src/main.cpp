#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "scanner.h"

using namespace std;

int main (int argc, char *argv[]) {
    string input = "";

    // Parse arguments
    vector<string> args;
    args.assign (argv, argv + argc);
    int i = 0;
    for (auto arg : args) {
        if (arg == "-i" || arg == "--input") {
            auto _arg = args[++i];
            input = _arg;
        }
        i++;
    }

    // Check arguments
    if (input == "") {
        cout << "Please specifiy an input source." << endl;
        return 1;
    }

    // Read source file
    ifstream file (input);
    stringstream source;
    source << file.rdbuf ();

    // Scan source
    Scanner scanner;
    scanner.Feed (source.str ());
    auto tokens = scanner.Scan ();

    // Show scanned tokens
    for (auto iter = tokens.begin (); iter != tokens.end (); iter++) {
        auto tk = *(iter);
        printf ("%s -> %s at %d:%d\n",
                TokenTypeName[tk.type].c_str (),
                tk.value.c_str (),
                tk.position->linenum,
                tk.position->linepos);
    }

    // Parse tokens
    // ...

    return 0;
}