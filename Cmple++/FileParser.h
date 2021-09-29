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
    std::set < std::string > sprites;
    std::map < std::string, std::string > sprites_extensions;
    std::set < std::string > models;
    std::set < std::string > sounds;
    std::map < std::string, std::string > sounds_extensions;

    void read_input_classes();
    void read_input_sprites();
    void read_input_models();
    void read_input_sounds();

    std::deque < std::string > split_data(std::string data);

    void parse_file(std::string file_name);
    void parse_creation_code();

    std::deque < std::string > parse_strings_header(std::deque < std::string > split, std::string class_name);
    std::deque < std::string > parse_strings_source(std::deque < std::string > split, std::string class_name);

    void create_include_files();

    void create_classes_implementation_header_files();
    void create_classes_implementation_source_files();
    void create_classes_update_files();
    void create_classes_display_3d_files();
    void create_classes_display_2d_files();
    void create_files_load_files();
    void copy_const_input();
    void create_bat_file();
};

#endif // FILEPARSER_H_INCLUDED
