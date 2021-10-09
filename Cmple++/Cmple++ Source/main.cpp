#include <iostream>
#include "FileParser.h"

int main(int argc, char** argv) {
    FileParser file_parser(argc, argv);
    file_parser.parse();

    return 0;
}
