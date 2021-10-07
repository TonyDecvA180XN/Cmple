#include <iostream>
#include "FileParser.h"

int main(int argc, char** argv) {
    FileParser file_parser(argc, argv);
    if (file_parser.parse())
        std::cout << "Successful parsing" << std::endl;
    else
        std::cout << "Unsuccessful parsing" << std::endl;

    return 0;
}
