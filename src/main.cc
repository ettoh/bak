#include <iostream>
#include <string>

#include "backup.h"

int main(int argc, char *argv[]) {
    using std::string;
    if (argc < 2) {
        std::cout << "Usage: bak file1 [file2 ...]" << std::endl;
        return 1;
    }

    if (string(argv[1]).compare("--version") == 0) {
        std::cout << "bak version 1.0" << std::endl;
        return 0;
    }

    // backup all given files
    for (int i = 1; i < argc; ++i) {
        Backup::backup(argv[i]);
    }

    return 0;
}
