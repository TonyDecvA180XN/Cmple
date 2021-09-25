#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <fstream>
#include <sstream>

#include "Directory.h"
#include "FileParser.h"

FileParser::FileParser() {

}

/**< Detects all files in input directory, reads all class names, calls parsings of all files */
void FileParser::parse() {
    std::vector < std::string > file_list = find_files_in_directory(Directory_Search_Input_Scripts);
    std::cout << "Initializing input files...\n";
    std::cout.flush();
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if(is_cpp(file_name))
                classes.insert(remove_extension(file_name));
        }
    }
    std::cout << "Parsing files...\n";
    std::cout << 0 * 100 / (int)classes.size() << "% completed";
    std::cout.flush();
    int nCompleted = 0;
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if(is_cpp(file_name)){
                parse_file(remove_extension(file_name));
                nCompleted++;
                std::cout << "\r" << nCompleted * 100 / (int)classes.size() << "% completed";
                std::cout.flush();
            }
        }
    }

    std::cout << "\rCreating include files...\n";
    std::cout.flush();

    create_include_files();

    std::cout << "Competed\n";
    std::cout.flush();
}

/**< Splits the code into words and all other symbols */
std::deque < std::string > FileParser::split_data(std::string data) {
    std::deque < std::string > split;
    std::string cur_string;
    for(char cur_char : data) {
        if(is_letter_or_digit(cur_char)) {
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

/**< Reads file, splits it, calls parse_strings and saves output file */
void FileParser::parse_file(std::string file_name) {
    std::ifstream file_input((Directory_Input_Scripts + file_name + ".cpp").c_str());
    std::stringstream file_data_stream;
    file_data_stream << file_input.rdbuf();
    file_input.close();

    std::string file_data = file_data_stream.str();

    std::deque < std::string > split = split_data(file_data);
    std::deque < std::string > split_source = parse_strings_source(split, remove_extension(file_name));
    std::ofstream file_output_source((Directory_Output_Scripts + file_name + ".cpp").c_str());
    for(std::string word : split_source) {
        file_output_source << word;
    }
    file_output_source.close();


    std::deque < std::string > split_header = parse_strings_header(split, remove_extension(file_name));
    std::ofstream file_output_header((Directory_Output_Scripts + file_name + ".h").c_str());
    for(std::string word : split_header) {
        file_output_header << word;
    }
    file_output_header.close();
}

std::deque < std::string > FileParser::parse_strings_header(std::deque < std::string > split, std::string class_name) {
    for (size_t i = 0; i < split.size(); i++) {
        if (split[i] == "\n") {
            split[i] = "\n\t";
        }
        else if (split[i] == "{") {
            while (split[i] != "}" && i < split.size()) {
                split[i++] = "";
            }
            split[i] = "";
        }
        else if (is_letter(split[i][0])) {
            if (split[i+1] == "{")
                split[i] = "void " + split[i] + "();";
            else if (classes.find(split[i]) != classes.end())
                split[i] = split[i] + "_typename";
        }
    }
    std::string to_add_front_1 = "#ifndef " + to_upper(class_name) + "_H_INCLUDED\n";
    std::string to_add_front_2 = "#define " + to_upper(class_name) + "_H_INCLUDED\n\n";
    std::string to_add_front_3 = "#include \"classes_implementation.h\"\n\n";
    std::string to_add_front_4 = "class " + class_name + " {\npublic:\n\n\t";
    std::string to_add_back_1 = "\n};\n\n";
    std::string to_add_back_2 = "#endif // " + to_upper(class_name) + "_H_INCLUDED\n";

    split.push_front(to_add_front_4);
    split.push_front(to_add_front_3);
    split.push_front(to_add_front_2);
    split.push_front(to_add_front_1);
    split.push_back(to_add_back_1);
    split.push_back(to_add_back_2);


    return split;
}

/**< The mainest and scariest function of Parser class, which does all dirty work */
std::deque < std::string > FileParser::parse_strings_source(std::deque < std::string > split, std::string class_name) {
    std::map < std::string, std::string > variables;
    std::stack < std::map < std::string, std::string > > stack_of_variables;
    stack_of_variables.push(std::map < std::string, std::string > ());
    for (size_t i = 0; i < split.size(); i++) {
        if (split[i] == "\n") {
            split[i] = "\n";
        }
        if (split[i] == "{") {
            stack_of_variables.push(std::map < std::string, std::string > ());
        }
        if (split[i] == "}") {
            for(std::pair < std::string, std::string > var : stack_of_variables.top()) {
                variables.erase(var.first);
            }
            stack_of_variables.pop();
        }
        if (Function.find(split[i]) != Function.end()) {
            split[i] = "void " + class_name + "::" + split[i] + "() ";
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
        else if (variables.count(split[i])) {
            if ((size_t)i + 1< split.size() && split[i+1] == "&") {
                split[i+1] = "";
                i++;
            }
            else {
                split[i] = variables[split[i]] + "_container[" + split[i] + "]";
            }
        }
    }

    std::string to_add_front_1 = "#include \"classes_implementation.h\"\n\n";
    std::string to_add_back_1 = "\n";

    split.push_front(to_add_front_1);
    split.push_back(to_add_back_1);

    return split;
}

void FileParser::create_include_files() {
    create_classes_implementation_header_files();
    create_classes_implementation_source_files();
    create_classes_update_files();
    create_classes_display_3d_files();
    create_classes_display_2d_files();
}

void FileParser::create_classes_implementation_header_files() {
    std::ofstream file;
    file.open(Directory_Output_Scripts+"classes_implementation.h");

    file << "#ifndef CLASSES_IMPLEMENTATION_H_INCLUDED\n";
    file << "#define CLASSES_IMPLEMENTATION_H_INCLUDED\n\n";

    file << "#include <map>\n\n";

    for (std::string class_name : classes) {
        file << "class " << class_name << ";\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "extern std::map <int, " << class_name << "> " << class_name <<"_container;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "extern int " << class_name << "_objects_number;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "using " << class_name << "_typename = int;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "int create_object_" << class_name << "();\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "void destroy_object_" << class_name << "(int);\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "#include \"" << class_name << ".h\"\n";
    }
    file << "\n\n";

    file << "#endif // CLASSES_IMPLEMENTATION_H_INCLUDED\n";

    file.close();
}

void FileParser::create_classes_implementation_source_files() {
    std::ofstream file;
    file.open(Directory_Output_Scripts+"classes_implementation.cpp");

    file << "#include \"classes_implementation.h\"\n\n";

    for (std::string class_name : classes) {
        file << "std::map <int, " << class_name << "> " << class_name <<"_container;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "int " << class_name << "_objects_number = 0;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "int create_object_" << class_name << "() {\n"
        << "\t" << class_name << " object;\n"
        << "\t" << class_name << "_container[" << class_name << "_objects_number] = object;\n"
        << "\t" << class_name << "_container[" << class_name << "_objects_number].Create();\n"
        << "\treturn " << class_name << "_objects_number++;\n" << "}\n\n";
    }

    for (std::string class_name : classes) {
        file << "void destroy_object_" << class_name << "(int num) {\n"
        << "\t" << class_name << "_container[num].Destroy();\n"
        << "\t" << class_name << "_container.erase(num);\n" << "}\n\n";
    }

    file.close();
}

void FileParser::create_classes_update_files() {
    std::ofstream file;
    file.open(Directory_Output_Scripts+"classes_display_3d.h");
    for(std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "> i : " << class_name << "_container) {\n"
        << "\t" << "i.second.Draw3D();\n" << "}\n";
    }
    file.close();
}

void FileParser::create_classes_display_3d_files() {
    std::ofstream file;
    file.open(Directory_Output_Scripts+"classes_update.h");
    for(std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "> i : " << class_name << "_container) {\n"
        << "\t" << "i.second.Update();\n" << "}\n";
    }
    file.close();
}

void FileParser::create_classes_display_2d_files() {
    std::ofstream file;
    file.open(Directory_Output_Scripts+"classes_display_2d.h");
    for(std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "> i : " << class_name << "_container) {\n"
        << "\t" << "i.second.Draw2D();\n" << "}\n";
    }
    file.close();
}
