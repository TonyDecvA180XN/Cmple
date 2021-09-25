#ifndef FILEPARSER_H_INCLUDED
#define FILEPARSER_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

class FileParser {
public:
    FileParser();

    void parse();

private:
    std::set < std::string > classes;

    std::deque < std::string > split_data(std::string data);

    void parse_file(std::string file_name);

    std::deque < std::string > parse_strings_header(std::deque < std::string > split, std::string class_name);
    std::deque < std::string > parse_strings_source(std::deque < std::string > split, std::string class_name);

    void create_include_files();

    void create_classes_implementation_header_files();
    void create_classes_implementation_source_files();
    void create_classes_update_files();
    void create_classes_display_3d_files();
    void create_classes_display_2d_files();
};

#endif // FILEPARSER_H_INCLUDED
