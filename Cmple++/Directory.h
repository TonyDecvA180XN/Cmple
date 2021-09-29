#ifndef DIRECTORY_H_INCLUDED
#define DIRECTORY_H_INCLUDED

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif // __unix__

const std::string Directory_Input_Scripts     = "input\\scripts\\";
const std::string Directory_Output_Scripts    = "to_compile\\";
const std::string Directory_Const_Scripts     = "const_input\\scripts\\";
const std::string Directory_Input_Sprites     = "input\\sprites\\";
const std::string Directory_Output_Sprites    = "to_compile\\sprites\\";
const std::string Directory_Execution_Sprites = "sprites\\\\";
const std::string Directory_Input_Models      = "input\\models\\";
const std::string Directory_Output_Models     = "to_compile\\models\\";
const std::string Directory_Execution_Models  = "models\\\\";
const std::string Directory_Input_Sounds      = "input\\sounds\\";
const std::string Directory_Output_Sounds     = "to_compile\\sounds\\";
const std::string Directory_Execution_Sounds  = "sounds\\\\";
const std::string Directory_Initial_Object    = "input\\init.txt";
const std::string Directory_Creation_Code               = "creation_code";

const std::string Directory_Search_Input_Scripts  = "input\\scripts\\*";
const std::string Directory_Search_Output_Scripts = "to_compile\\*";
const std::string Directory_Search_Const_Scripts  = "const_input\\scripts\\*";
const std::string Directory_Search_Input_Sprites  = "input\\sprites\\*";
const std::string Directory_Search_Output_Sprites = "to_compile\\sprites\\*";
const std::string Directory_Search_Input_Models   = "input\\models\\*";
const std::string Directory_Search_Output_Models  = "to_compile\\models\\*";
const std::string Directory_Search_Input_Sounds   = "input\\sounds\\*";
const std::string Directory_Search_Output_Sounds  = "to_compile\\sounds\\*";

const std::string Directory_Current  = ".";
const std::string Directory_Previous = "..";
const std::set < std::string > Function = {"Create", "Destroy", "Update", "Draw3D", "Draw2D"};

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
        while((ent = readdir(dir)) != NULL) {
            file_list.push_back(ent -> d_name);
        }
    }
    else {
        std::cerr << "Error: could not open directory: " << directory << std::endl;
    }
    return file_list;
#endif // __unix__
}

void find_files_in_subdirectories(std::vector < std::string > &path, std::vector < std::string > &files) {
    std::string path_string;
    for(std::string directory : path) {
        path_string += directory + "\\";
    }
    std::vector < std::string > file_list = find_files_in_directory(path_string + "*");
    for(std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            std::ifstream file(path_string + file_name);
            if(file.is_open()) {
                files.push_back(path_string + file_name);
            }
            else {
                path.push_back(file_name);
                find_files_in_subdirectories(path, files);
                path.pop_back();
            }
        }
    }
}

std::string remove_first_directory(std::string path) {
    for(int i = 0; i <= (int)path.size(); i++) {
        if(path[i] == '\\') {
            return path.substr(i);
        }
    }
    return path;
}

bool is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool is_letter_or_digit(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');
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

bool is_image(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size()-4) == ".bmp" ||
                                str.substr(str.size()-4) == ".png" ||
                                str.substr(str.size()-4) == ".jpg"));
}

bool is_model(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size()-4) == ".obj" ||
                                str.substr(str.size()-4) == ".mtl" ||
                                str.substr(str.size()-4) == ".bmp" ||
                                str.substr(str.size()-4) == ".png" ||
                                str.substr(str.size()-4) == ".jpg"));
}

bool is_sound(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size()-4) == ".wav" ||
                                str.substr(str.size()-4) == ".mp3" ||
                                str.substr(str.size()-4) == ".ogg"));
}

std::string to_upper(std::string str){
    for(char &c : str) {
        if(c >= 'a' && c <= 'z') {
            c += 'A' - 'a';
        }
    }
    return str;
}

std::string remove_extension(std::string file_name) {
    if(file_name.empty())
        return file_name;
    for(size_t i = 0; i < file_name.size(); i++) {
        if(file_name[i] == '.') {
            return file_name.substr(0, i);
        }
    }
    return file_name;
}

std::string get_extension(std::string file_name) {
    if(file_name.empty())
        return file_name;
    for(size_t i = file_name.size() - 1; i >= 0; i--) {
        if(file_name[i] == '.') {
            return file_name.substr(i);
        }
    }
    return "";
}

#endif // DIRECTORY_H_INCLUDED
