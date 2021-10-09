#include "Directory.h"

std::vector < std::string > find_files_in_directory(std::string directory) {
    directory += "\\*";
#ifdef _WIN32
    std::vector < std::string > file_list;
    WIN32_FIND_DATA file;
    HANDLE hl;
    hl = FindFirstFile(directory.c_str(), &file);
    if (hl != INVALID_HANDLE_VALUE) {
        do {
            file_list.push_back(file.cFileName);
        } while (FindNextFile(hl, &file) != 0);
        FindClose(hl);
    }
    else {
        throw "Error: could not open directory " + directory;
    }
    return file_list;
#endif // _WIN32
#ifdef __unix__
    std::vector < std::string > file_list;
    DIR* dir = opendir(directiry.c_str());
    if (dir) {
        struct dirent* ent;
        while ((ent = readdir(dir)) != NULL) {
            file_list.push_back(ent->d_name);
        }
    }
    else {
        throw "Error: could not open directory " + directory;
    }
    return file_list;
#endif // __unix__
}

void copy_directory(std::string from, std::string to) {
#ifdef __WIN32
    std::string comand;
    comand = "xcopy " + from + " " + to + "/E /H /C /R /Q /Y >NUL";
    system(comand.c_str());
#endif // __WIN32
#ifdef __unix__

#endif // __unix__
}

void clean_directory(std::string path) {
#ifdef __WIN32
    std::string comand;
    comand = "del " + path + " /S /Q >NUL";
    system(comand.c_str());
    comand = "rmdir " + path + " /S /Q >NUL";
    system(comand.c_str());
    comand = "mkdir " + path + " >NUL";
    system(comand.c_str());
#endif // __WIN32
#ifdef __unix__

#endif // __unix__
}

std::string remove_first_directory(std::string path) {
    for (int i = 0; i <= (int)path.size(); i++) {
        if (path[i] == '\\') {
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
        if (!is_space(str[i])) {
            return false;
        }
    }
    return true;
}

bool is_cpp(std::string str) {
    return (str.size() >= 4 && str.substr(str.size() - 4) == ".cpp");
}

bool is_image(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size() - 4) == ".bmp" ||
        str.substr(str.size() - 4) == ".png" ||
        str.substr(str.size() - 4) == ".jpg"));
}

bool is_model(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size() - 4) == ".obj" ||
        str.substr(str.size() - 4) == ".mtl" ||
        str.substr(str.size() - 4) == ".bmp" ||
        str.substr(str.size() - 4) == ".png" ||
        str.substr(str.size() - 4) == ".jpg"));
}

bool is_sound(std::string str) {
    return (str.size() >= 4 && (str.substr(str.size() - 4) == ".wav" ||
        str.substr(str.size() - 4) == ".mp3" ||
        str.substr(str.size() - 4) == ".ogg"));
}

std::string to_upper(std::string str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') {
            c += 'A' - 'a';
        }
    }
    return str;
}

std::string remove_extension(std::string file_name) {
    if (file_name.empty())
        return file_name;
    for (size_t i = 0; i < file_name.size(); i++) {
        if (file_name[i] == '.') {
            return file_name.substr(0, i);
        }
    }
    return file_name;
}

std::string get_extension(std::string file_name) {
    if (file_name.empty())
        return file_name;
    for (size_t i = file_name.size() - 1; i >= 0; i--) {
        if (file_name[i] == '.') {
            return file_name.substr(i);
        }
    }
    return "";
}
