#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#ifdef __unix__
#include <sys/types.h>
#include <dirent.h>
#endif // __unix__

const std::string Directory_Input_Scripts  =  "input\\scripts\\";
const std::string Directory_Output_Scripts = "output\\scripts\\";
const std::string Directory_Search_Input_Scripts  =  "input\\scripts\\*";
const std::string Directory_Search_Output_Scripts = "output\\scripts\\*";
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
    return file_list
#endif // __unix__
}

bool is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_');
}

bool is_space(char c) {
    return (c == ' ' || c == '\t' || c == '\n');
}

bool is_space(std::string str) {
    for (size_t i = 0; i < str.size(); i++) {\
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
    for(int i = (int)file_name.size() - 1; i >= 0; i--){
        if(file_name[i] == '.') {
            return file_name.substr(0, i);
        }
    }
    return file_name;
}

class FileParser {
public:
    FileParser() {

    }

    void parse() {
        std::vector < std::string > file_list = find_files_in_directory(Directory_Search_Input_Scripts);
        for (std::string file_name : file_list) {
            if (file_name != Directory_Current && file_name != Directory_Previous) {
                if(is_cpp(file_name))
                    classes.insert(file_name.substr(0, file_name.size()-4));
            }
        }
        for (std::string file_name : file_list) {
            if (file_name != Directory_Current && file_name != Directory_Previous) {
                if(is_cpp(file_name))
                    parse_file(file_name);
            }
        }
    }

private:
    std::set < std::string > classes;

    std::vector < std::string > split_data(std::string data) {
        std::vector < std::string > split;
        std::string cur_string;
        for(char cur_char : data) {
            if(is_letter(cur_char)) {
                cur_string.push_back(cur_char);
            }
            else{
                if(!cur_string.empty()) {
                    split.push_back(cur_string);
                    cur_string.clear();
                }
                split.push_back(std::string{cur_char});
            }
        }
        return split;
    }

    void parse_file(std::string file_name) {
        std::ifstream file_input((Directory_Input_Scripts + file_name).c_str());
        std::stringstream file_data_stream;
        file_data_stream << file_input.rdbuf();
        file_input.close();

        std::string file_data = file_data_stream.str();

        std::vector < std::string > split = split_data(file_data);
        parse_strings(split, remove_extension(file_name));

        std::ofstream file_output((Directory_Output_Scripts + file_name).c_str());
        for(std::string word : split) {
            file_output << word;
        }
        file_output.close();
    }

    void parse_strings(std::vector < std::string > &split, std::string class_name) {
        std::map < std::string, std::string > variables;
        std::stack < std::map < std::string, std::string > > stack_of_variables;
        stack_of_variables.push(std::map < std::string, std::string > ());
        split[0] = "class " + class_name + " {\npublic:\n\t" + split[0];
        for(size_t i = 0; i < split.size(); i++) {
            if(split[i] == "\n") {
                split[i] = "\n\t";
            }
            if(split[i] == "{") {
                stack_of_variables.push(std::map < std::string, std::string > ());
            }
            if(split[i] == "}") {
                for(std::pair < std::string, std::string > var : stack_of_variables.top()) {
                    variables.erase(var.first);
                }
                stack_of_variables.pop();
            }
            if(Function.find(split[i]) != Function.end()) {
                split[i] = "void " + split[i] + "() ";
            }
            if (classes.find(split[i]) != classes.end()){
                std::string variable_name = split[i];
                split[i] = split[i] + "_typename";
                for (size_t j = i + 1; j < split.size(); j++) {
                    if (!is_space(split[j])) {
                        stack_of_variables.top()[split[j]] = variable_name;
                        variables[split[j]] = variable_name;
                        i = j;
                        break;
                    }
                }
            }
            else if(variables.count(split[i])) {
                split[i] = variables[split[i]] + "_container[" + split[i] + "]";
            }
        }
        split.push_back("\n}\n");
    }
};

int main(int argc,char **argv) {
    FileParser file_parser;
    file_parser.parse();

    return 0;
}
