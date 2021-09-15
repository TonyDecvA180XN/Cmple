#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif // __unix__

const std::string Directory_Input_Scripts  = "input\\scripts\\";
const std::string Directory_Output_Scripts = "to_compile\\scripts\\";
const std::string Directory_Const_Scripts  = "const_input\\scripts\\";
const std::string Directory_Search_Input_Scripts  = "input\\scripts\\*";
const std::string Directory_Search_Output_Scripts = "to_compile\\scripts\\*";
const std::string Directory_Search_Const_Scripts  = "const_input\\scripts\\*";
const std::string Directory_Current  = ".";
const std::string Directory_Previous = "..";
const std::set < std::string > Function = {"Create", "Destroy", "Update", "Draw"};

std::vector < std::string > find_files_in_directory(std::string directory) {
#ifdef _WIN32
    std::vector < std::string > file_list;
    WIN32_FIND_DATA file;
    HANDLE hl;
    hl = FindFirstFile(directory.c_str(), &file);
    if (hl != INVALID_HANDLE_VALUE) {
        do {
            file_list.push_back(file.cFileName);
        }
        while (FindNextFile(hl, &file) != 0);
        FindClose(hl);
    }
    else {
        std::cerr << "Error: could not open directory: " << directory << std::endl;
    }
    return file_list;
#endif // _WIN32
#ifdef __unix__
    std::vector < std::string > file_list;
    DIR *dir = opendir(directiry.c_str());
    if(dir) {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL){
            file_list.push_back(ent -> d_name);
        }
    }
    else {
        std::cerr << "Error: could not open directory: " << directory << std::endl;
    }
    return file_list;
#endif // __unix__
}

bool is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

bool is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

bool is_space(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {
        if(!is_space(str[i])){
            return false;
        }
    }
    return true;
}

bool is_cpp(std::string str) {
    return (str.size() >= 4 && str.substr(str.size()-4) == ".cpp");
}

std::string remove_extension(std::string file_name) {
    if(file_name.empty())
        return file_name;
    for(size_t i = 0; i < file_name.size(); i++){
        if(file_name[i] == '.') {
            return file_name.substr(0, i);
        }
    }
    return file_name;
}

#endif // DIRECTORY_H_INCLUDED
