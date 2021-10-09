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

FileParser::FileParser(int argc, char** argv) {
    process_arguments(argc, argv);
}

void FileParser::process_arguments(int argc, char** argv) {
    directory_input = Directory_Input_Default;
    directory_const_input = Directory_Const_Input_Default;
    directory_to_compile = Directory_To_Compile_Default;

    for (int i = 1; i < argc; i++) {
        std::string command(argv[i]);

        if (command.size() >= 7 && command.substr(0, 6) == "input=") {
            directory_input = command.substr(6);
        }
        if (command.size() >= 13 && command.substr(0, 12) == "const_input=") {
            directory_input = command.substr(12);
        }
        if (command.size() >= 12 && command.substr(0, 11) == "to_compile=") {
            directory_input = command.substr(11);
        }
        if (command == "gcc_create_batch") {
            gcc_create_bat = true;
        }
        if (command == "gcc_auto_execute") {
            gcc_auto_execute = true;
        }
    }
}

void FileParser::parse() {
    try {
        copy_const_input();

        read_input_classes();
        read_input_sprites();
        read_input_models();
        read_input_sounds();

        std::vector < std::string > file_list = find_files_in_directory(directory_input + "\\" + Directory_Scripts);
        for (std::string class_name : classes) {
            parse_file(class_name);
        }
        parse_creation_code();
        create_include_files();

        if (gcc_create_bat || gcc_auto_execute)
            create_bat_file();

#ifdef __WIN32
        if (gcc_auto_execute) {
            std::string command;
            command = "cd " + directory_to_compile + " & compile.bat";
            std::system(command.c_str());
            command = "cd " + directory_to_compile + " & program.exe";
            std::system(command.c_str());
        }
#endif // __WIN32

        std::cout << "Successful parsing" << std::endl;
    }
    catch (char const* err) {
        std::cerr << err << std::endl;
        std::cout << "Unsuccessful parsing" << std::endl;
    }
}

void FileParser::read_input_classes() {
    std::vector < std::string > file_list = find_files_in_directory(directory_input + "\\" + Directory_Scripts);
    std::cout.flush();
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if (is_cpp(file_name) && remove_extension(file_name) != Directory_Creation_Code)
                classes.insert(remove_extension(file_name));
        }
    }
}

void FileParser::read_input_sprites() {
    std::vector < std::string > file_list = find_files_in_directory(directory_input + "\\" + Directory_Sprites);
    std::cout.flush();
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if (is_image(file_name)) {
                sprites.insert(remove_extension(file_name));
                sprites_extensions[remove_extension(file_name)] = get_extension(file_name);
            }
        }
    }
    copy_directory(directory_input + "\\" + Directory_Sprites, directory_to_compile + "\\" + Directory_Sprites);
}

void FileParser::read_input_models() {
    std::vector < std::string > file_list = find_files_in_directory(directory_input + "\\" + Directory_Models);
    std::cout.flush();
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if (is_model(file_name)) {
                models.insert(remove_extension(file_name));
            }
        }
    }
    copy_directory(directory_input + "\\" + Directory_Models, directory_to_compile + "\\" + Directory_Models);
}

void FileParser::read_input_sounds() {
    std::vector < std::string > file_list = find_files_in_directory(directory_input + "\\" + Directory_Sounds);
    std::cout.flush();
    for (std::string file_name : file_list) {
        if (file_name != Directory_Current && file_name != Directory_Previous) {
            if (is_sound(file_name)) {
                sounds.insert(remove_extension(file_name));
                sounds_extensions[remove_extension(file_name)] = get_extension(file_name);
            }
        }
    }
    copy_directory(directory_input + "\\" + Directory_Sounds, directory_to_compile + "\\" + Directory_Sounds);
}

std::deque < std::string > FileParser::split_data(std::string data) {
    std::deque < std::string > split;
    std::string cur_string;
    for (char cur_char : data) {
        if (is_letter_or_digit(cur_char)) {
            cur_string.push_back(cur_char);
        }
        else {
            if (!cur_string.empty()) {
                split.push_back(cur_string);
                cur_string.clear();
            }
            split.push_back(std::string{ cur_char });
        }
    }
    return split;
}

void FileParser::parse_file(std::string file_name) {
    std::ifstream file_input((directory_input + "\\" + Directory_Scripts + "\\" + file_name + ".cpp").c_str());
    std::stringstream file_data_stream;
    file_data_stream << file_input.rdbuf();
    file_input.close();

    std::string file_data = file_data_stream.str();

    std::deque < std::string > split = split_data(file_data);
    std::deque < std::string > split_source = parse_strings_source(split, remove_extension(file_name));
    std::ofstream file_output_source((directory_to_compile + "\\" + file_name + ".cpp").c_str());
    for (std::string word : split_source) {
        file_output_source << word;
    }
    file_output_source.close();

    std::deque < std::string > split_header = parse_strings_header(split, remove_extension(file_name));
    std::ofstream file_output_header((directory_to_compile + "\\" + file_name + ".h").c_str());
    for (std::string word : split_header) {
        file_output_header << word;
    }
    file_output_header.close();
}

void FileParser::parse_creation_code() {
    std::ifstream file_input((directory_input + "\\" + Directory_Scripts + "\\" + Directory_Creation_Code + ".cpp").c_str());
    std::stringstream file_data_stream;
    file_data_stream << file_input.rdbuf();
    file_input.close();

    std::string file_data = file_data_stream.str();

    std::deque < std::string > split = split_data(file_data);
    std::deque < std::string > split_source = parse_strings_source(split, Directory_Creation_Code);
    std::ofstream file_output_source((directory_to_compile + "\\" + Directory_Creation_Code + ".h").c_str());
    for (std::string word : split_source) {
        file_output_source << word;
    }
    file_output_source.close();
}

std::deque < std::string > FileParser::parse_strings_header(std::deque < std::string > split, std::string class_name) {
    for (size_t i = 0; i < split.size(); i++) {
        if (split[i] == "\n") {
            split[i] = "\n\t";
        }
        else if (split[i] == "{") {
            int level = 1;
            split[i] = "";
            i++;
            while (i < split.size() && level != 0) {
                if (split[i] == "{")
                    level++;
                else if (split[i] == "}")
                    level--;
                split[i] = "";
                i++;
            }
        }
        else if (is_letter(split[i][0])) {
            bool next_brace = false;
            for (size_t j = i + 1; j < split.size(); j++) {
                if (split[j] == "{") {
                    next_brace = true;
                }
                if (!is_space(split[j])) {
                    break;
                }
            }
            if (next_brace)
                split[i] = "void " + split[i] + "();";
            else if (classes.find(split[i]) != classes.end())
                split[i] = split[i] + "_typename";
        }
    }

    std::string to_add_front_1 = "#ifndef " + to_upper(class_name) + "_H_INCLUDED\n";
    std::string to_add_front_2 = "#define " + to_upper(class_name) + "_H_INCLUDED\n\n";
    std::string to_add_front_3 = "#include \"cmple_api.h\"\n";
    std::string to_add_front_4 = "#include \"classes_implementation.h\"\n\n";
    std::string to_add_front_5 = "class " + class_name + " {\npublic:\n\n\t";
    std::string to_add_back_1 = "\n};\n\n";
    std::string to_add_back_2 = "#endif // " + to_upper(class_name) + "_H_INCLUDED\n";

    split.push_front(to_add_front_5);
    split.push_front(to_add_front_4);
    split.push_front(to_add_front_3);
    split.push_front(to_add_front_2);
    split.push_front(to_add_front_1);
    split.push_back(to_add_back_1);
    split.push_back(to_add_back_2);


    return split;
}

std::deque < std::string > FileParser::parse_strings_source(std::deque < std::string > split, std::string class_name) {
    std::map < std::string, std::string > variables;
    std::stack < std::map < std::string, std::string > > stack_of_variables;
    stack_of_variables.push(std::map < std::string, std::string >());
    for (size_t i = 0; i < split.size(); i++) {
        if (split[i] == "\n") {
            split[i] = "\n";
        }
        if (split[i] == "{") {
            stack_of_variables.push(std::map < std::string, std::string >());
        }
        if (split[i] == "}") {
            for (std::pair < std::string, std::string > var : stack_of_variables.top()) {
                variables.erase(var.first);
            }
            stack_of_variables.pop();
        }
        if (Function.find(split[i]) != Function.end()) {
            split[i] = "void " + class_name + "::" + split[i] + "() ";
        }
        if (classes.find(split[i]) != classes.end()) {
            std::string variable_name = split[i];
            split[i] = split[i] + "_typename";
            for (size_t j = i + 1; j < split.size(); j++) {
                if (!is_space(split[j])) {
                    stack_of_variables.top()[split[j]] = variable_name;
                    variables[split[j]] = variable_name;
                    break;
                }
            }
        }
        else if (variables.count(split[i])) {
            int depth = 0;
            int posEnd = i;
            for (size_t j = i + 1; j < split.size(); j++) {
                if (split[j] == "[")
                    depth++;
                if (split[j] == "]")
                    depth--;
                if (split[j] == "&" || (is_space(split[j]) && depth == 0)) {
                    posEnd = j;
                    break;
                }
            }

            if (split[posEnd] == "&") {
                split[i] = variables[split[i]] + "_container[" + split[i];
                split[posEnd] = "]->";
            }
            else {
                i++;
            }
        }
    }

    if (class_name != Directory_Creation_Code) {
        std::string to_add_front_1 = "#include \"classes_implementation.h\"\n\n";
        std::string to_add_back_1 = "\n";

        split.push_front(to_add_front_1);
        split.push_back(to_add_back_1);
    }
    else {
        std::string to_add_back_1 = "\n";

        split.push_back(to_add_back_1);
    }

    return split;
}

void FileParser::create_include_files() {
    create_classes_implementation_header_files();
    create_classes_implementation_source_files();
    create_classes_update_files();
    create_classes_display_3d_files();
    create_classes_display_2d_files();
    create_files_load();
    create_files_audio_load();
}

void FileParser::create_classes_implementation_header_files() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "classes_implementation.h");

    file << "#ifndef CLASSES_IMPLEMENTATION_H_INCLUDED\n";
    file << "#define CLASSES_IMPLEMENTATION_H_INCLUDED\n\n";

    file << "#include <map>\n";
    file << "#include \"cmple_api.h\"\n\n";

    for (std::string class_name : classes) {
        file << "class " << class_name << ";\n";
    }
    file << "\n";

    for (std::string sprite_name : sprites) {
        file << "extern Sprite " << sprite_name << ";\n";
    }
    file << "\n";

    for (std::string model_name : models) {
        file << "extern Model " << model_name << ";\n";
    }
    file << "\n";

    for (std::string sound_name : sounds) {
        file << "extern Sound " << sound_name << ";\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "extern std::map <int, " << class_name << "*> " << class_name << "_container;\n";
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
        file << class_name << "_typename create_object_" << class_name << "();\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "void destroy_object_" << class_name << "(" << class_name << "_typename num);\n";
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
    file.open(directory_to_compile + "\\" + "classes_implementation.cpp");

    file << "#include \"classes_implementation.h\"\n\n";

    for (std::string sprite_name : sprites) {
        file << "Sprite " << sprite_name << ";\n";
    }
    file << "\n";

    for (std::string model_name : models) {
        file << "Model " << model_name << ";\n";
    }
    file << "\n";

    for (std::string sound_name : sounds) {
        file << "Sound " << sound_name << ";\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "std::map <int, " << class_name << "*> " << class_name << "_container;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << "int " << class_name << "_objects_number = 0;\n";
    }
    file << "\n";

    for (std::string class_name : classes) {
        file << class_name << "_typename create_object_" << class_name << "() {\n"
            << "\t" << class_name << " *object = new " << class_name << ";\n"
            << "\t" << class_name << "_container[" << class_name << "_objects_number] = object;\n"
            << "\t" << class_name << "_container[" << class_name << "_objects_number]->Create();\n"
            << "\treturn " << class_name << "_objects_number++;\n" << "}\n\n";
    }

    for (std::string class_name : classes) {
        file << "void destroy_object_" << class_name << "(" << class_name << "_typename num) {\n"
            << "\t" << class_name << "_container[num]->Destroy();\n"
            << "\t" << class_name << "_container.erase(num);\n" << "}\n\n";
    }

    file.close();
}

void FileParser::create_classes_update_files() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "classes_display_3d.h");
    for (std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "*> i : " << class_name << "_container) {\n"
            << "\t" << "i.second->Draw3D();\n" << "}\n";
    }
    file.close();
}

void FileParser::create_classes_display_3d_files() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "classes_update.h");
    for (std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "*> i : " << class_name << "_container) {\n"
            << "\t" << "i.second->Update();\n" << "}\n";
    }
    file.close();
}

void FileParser::create_classes_display_2d_files() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "classes_display_2d.h");
    for (std::string class_name : classes) {
        file << "for(std::pair <int, " << class_name << "*> i : " << class_name << "_container) {\n"
            << "\t" << "i.second->Draw2D();\n" << "}\n";
    }
    file.close();
}

void FileParser::create_files_load() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "files_load.h");

    for (std::string sprite_name : sprites) {
        file << sprite_name << ".Load(\"" << Directory_Sprites + "\\" + "\\" + sprite_name + sprites_extensions[sprite_name] << "\");\n";
    }
    file << "\n";

    for (std::string model_name : models) {
        file << model_name << ".Load(\"" << Directory_Models + "\\" + "\\" + model_name + ".obj" << "\");\n";
    }
    file << "\n";

    file.close();
}

void FileParser::create_files_audio_load() {
    std::ofstream file;
    file.open(directory_to_compile + "\\" + "files_audio_load.h");

    for (std::string sound_name : sounds) {
        file << sound_name << ".Load(\"" << Directory_Sounds + "\\" + "\\" + sound_name + sounds_extensions[sound_name] << "\");\n";
    }
    file << "\n";

    file.close();
}

void FileParser::copy_const_input() {
    clean_directory(directory_to_compile);
    copy_directory(directory_const_input, directory_to_compile);
}

void FileParser::create_bat_file() {
#ifdef __WIN32
    std::ofstream file_out("to_compile\\compile.bat");
    file_out << "gcc glad.c -c\n";
    file_out << "g++ camera.cpp -c\n";
    file_out << "g++ classes_implementation.cpp -c\n";
    file_out << "g++ cmple_api.cpp -c\n";
    file_out << "g++ cmple_engine.cpp -c\n";
    file_out << "g++ font.cpp -c\n";
    file_out << "g++ main.cpp -c\n";
    file_out << "g++ model.cpp -c\n";
    file_out << "g++ shader.cpp -c\n";
    file_out << "g++ sound.cpp -c\n";
    file_out << "g++ sprite.cpp -c\n";
    file_out << "g++ stb_image.cpp -c\n";

    for (std::string class_name : classes) {
        file_out << "g++ " + class_name + ".cpp -c\n";
    }

    file_out << "g++ glad.o ";
    file_out << "camera.o ";
    file_out << "classes_implementation.o ";
    file_out << "cmple_api.o ";
    file_out << "cmple_engine.o ";
    file_out << "font.o ";
    file_out << "main.o ";
    file_out << "model.o ";
    file_out << "shader.o ";
    file_out << "sound.o ";
    file_out << "sprite.o ";
    file_out << "stb_image.o ";

    for (std::string class_name : classes) {
        file_out << class_name << ".o ";
    }

    file_out << "-lopengl32 ";
    file_out << "-L./GL -lglfw3dll ";
    file_out << "-L./audiere -laudiere ";

    file_out << "-o program.exe";

    file_out.close();
#endif // __WIN32
#ifdef __unix__

#endif // __unix__
}
