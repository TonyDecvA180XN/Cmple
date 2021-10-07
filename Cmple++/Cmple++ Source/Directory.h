#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif // __unix__

#include <iostream>
#include <string>
#include <vector>
#include <set>

const std::string Directory_Input_Default = "input";
const std::string Directory_Const_Input_Default = "const_input";
const std::string Directory_To_Compile_Default = "to_compile";
const std::string Directory_Scripts = "scripts";
const std::string Directory_Sprites = "sprites";
const std::string Directory_Models = "models";
const std::string Directory_Sounds = "sounds";
const std::string Directory_Creation_Code = "creation_code";

const std::string Directory_Current = ".";
const std::string Directory_Previous = "..";
const std::set < std::string > Function = { "Create", "Destroy", "Update", "Draw3D", "Draw2D" };

std::vector < std::string > find_files_in_directory(std::string directory);
void copy_directory(std::string from, std::string to);
void clean_directory(std::string path);

std::string remove_first_directory(std::string path);

bool is_letter(char c);
bool is_letter_or_digit(char c);
bool is_space(char c);
bool is_space(std::string str);
bool is_cpp(std::string str);
bool is_image(std::string str);
bool is_model(std::string str);
bool is_sound(std::string str);

std::string to_upper(std::string str);

std::string remove_extension(std::string file_name);
std::string get_extension(std::string file_name);

#endif // DIRECTORY_H_INCLUDED
