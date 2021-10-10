#include "FileParser.h"

int main(const int argc, char ** argv)
{
    FileParser fileParser(argc, argv);
    fileParser.Parse();

    return 0;
}
