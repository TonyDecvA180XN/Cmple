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

FileParser::FileParser(const int argc, char ** argv)
{
    ProcessArguments(argc, argv);
}

void FileParser::ProcessArguments(const int argc, char ** argv)
{
    m_directoryInput = DIRECTORY_INPUT_DEFAULT;
    m_directoryConstInput = DIRECTORY_CONST_INPUT_DEFAULT;
    m_directoryToCompile = DIRECTORY_TO_COMPILE_DEFAULT;

    for (int i = 1; i < argc; i++)
    {
        std::string command(argv[i]);

        if (command.size() >= 7 && command.substr(0, 6) == "input=")
        {
            m_directoryInput = command.substr(6);
        }
        if (command.size() >= 13 && command.substr(0, 12) == "const_input=")
        {
            m_directoryConstInput = command.substr(12);
        }
        if (command.size() >= 12 && command.substr(0, 11) == "to_compile=")
        {
            m_directoryToCompile = command.substr(11);
        }
        if (command == "gcc_create_batch")
        {
            m_gccCreateBat = true;
        }
        if (command == "gcc_auto_execute")
        {
            m_gccAutoExecute = true;
        }
    }
}

void FileParser::Parse()
{
    try
    {
        CopyConstInput();

        ReadInputClasses();
        ReadInputSprites();
        ReadInputModels();
        ReadInputSounds();

        for (const std::string & className : m_classes)
        {
            ParseFile(className);
        }
        ParseCreationCode();
        CreateIncludeFiles();

        if (m_gccCreateBat || m_gccAutoExecute)
            CreateBatFile();

#ifdef __WIN32
        if (m_gccAutoExecute) {
            std::string command;
            command = "cd " + m_directoryToCompile + " & compile.bat";
            std::system(command.c_str());
            command = "cd " + m_directoryToCompile + " & program.exe";
            std::system(command.c_str());
        }
#endif // __WIN32

        std::cout << "Successful parsing" << std::endl;
    }
    catch (const char * err)
    {
        std::cerr << err << std::endl;
        std::cout << "Unsuccessful parsing" << std::endl;
    }
}

void FileParser::ReadInputClasses()
{
    const std::vector<std::string> fileList = FindFilesInDirectory(m_directoryInput + "\\" + DIRECTORY_SCRIPTS);
    for (std::string fileName : fileList)
    {
        if (fileName != DIRECTORY_CURRENT && fileName != DIRECTORY_PREVIOUS)
        {
            if (IsCpp(fileName) && RemoveExtension(fileName) != DIRECTORY_CREATION_CODE)
                m_classes.emplace(RemoveExtension(fileName));
        }
    }
}

void FileParser::ReadInputSprites()
{
    const std::vector<std::string> fileList = FindFilesInDirectory(m_directoryInput + "\\" + DIRECTORY_SPRITES);
    for (std::string fileName : fileList)
    {
        if (fileName != DIRECTORY_CURRENT && fileName != DIRECTORY_PREVIOUS)
        {
            if (IsImage(fileName))
            {
                m_sprites.emplace(RemoveExtension(fileName));
                m_spritesExtensions[RemoveExtension(fileName)] = GetExtension(fileName);
            }
        }
    }
    CopyDirectory(m_directoryInput + "\\" + DIRECTORY_SPRITES, m_directoryToCompile + "\\" + DIRECTORY_SPRITES);
}

void FileParser::ReadInputModels()
{
    const std::vector<std::string> fileList = FindFilesInDirectory(m_directoryInput + "\\" + DIRECTORY_MODELS);
    for (std::string fileName : fileList)
    {
        if (fileName != DIRECTORY_CURRENT && fileName != DIRECTORY_PREVIOUS)
        {
            if (IsModel(fileName))
            {
                m_models.emplace(RemoveExtension(fileName));
            }
        }
    }
    CopyDirectory(m_directoryInput + "\\" + DIRECTORY_MODELS, m_directoryToCompile + "\\" + DIRECTORY_MODELS);
}

void FileParser::ReadInputSounds()
{
    const std::vector<std::string> fileList = FindFilesInDirectory(m_directoryInput + "\\" + DIRECTORY_SOUNDS);
    for (std::string fileName : fileList)
    {
        if (fileName != DIRECTORY_CURRENT && fileName != DIRECTORY_PREVIOUS)
        {
            if (IsSound(fileName))
            {
                m_sounds.emplace(RemoveExtension(fileName));
                m_soundsExtensions[RemoveExtension(fileName)] = GetExtension(fileName);
            }
        }
    }
    CopyDirectory(m_directoryInput + "\\" + DIRECTORY_SOUNDS, m_directoryToCompile + "\\" + DIRECTORY_SOUNDS);
}

std::vector<std::string> FileParser::SplitData(const std::string & data)
{
    std::vector<std::string> split;
    std::string curString;
    for (const char curChar : data)
    {
        if (IsLetterOrDigit(curChar))
        {
            curString.push_back(curChar);
        }
        else
        {
            if (!curString.empty())
            {
                split.push_back(curString);
                curString.clear();
            }
            split.emplace_back(std::string{curChar});
        }
    }
    return split;
}

void FileParser::ParseFile(std::string file_name)
{
    std::ifstream fileInput((m_directoryInput + "\\" + DIRECTORY_SCRIPTS + "\\" + file_name + ".cpp").c_str());
    std::stringstream fileDataStream;
    fileDataStream << fileInput.rdbuf();
    fileInput.close();

    std::string fileData = fileDataStream.str();

    std::vector<std::string> split = SplitData(fileData);
    std::vector<std::string> splitSource = ParseStringsSource(split, RemoveExtension(file_name));
    std::ofstream fileOutputSource((m_directoryToCompile + "\\" + file_name + ".cpp").c_str());
    for (std::string word : splitSource)
    {
        fileOutputSource << word;
    }
    fileOutputSource.close();

    std::vector<std::string> splitHeader = ParseStringsHeader(split, RemoveExtension(file_name));
    std::ofstream fileOutputHeader((m_directoryToCompile + "\\" + file_name + ".h").c_str());
    for (std::string word : splitHeader)
    {
        fileOutputHeader << word;
    }
    fileOutputHeader.close();
}

void FileParser::ParseCreationCode()
{
    std::ifstream fileInput((m_directoryInput + "\\" + DIRECTORY_SCRIPTS + "\\" + DIRECTORY_CREATION_CODE + ".cpp").c_str());
    std::stringstream fileDataStream;
    fileDataStream << fileInput.rdbuf();
    fileInput.close();

    const std::string fileData = fileDataStream.str();

    std::vector<std::string> split = SplitData(fileData);
    std::vector<std::string> splitSource = ParseStringsSource(split, DIRECTORY_CREATION_CODE);
    std::ofstream fileOutputSource((m_directoryToCompile + "\\" + DIRECTORY_CREATION_CODE + ".h").c_str());
    for (std::string word : splitSource)
    {
        fileOutputSource << word;
    }
    fileOutputSource.close();
}

std::vector<std::string> FileParser::ParseStringsHeader(std::vector<std::string> split, const std::string & class_name)
{
    for (size_t i = 0; i < split.size(); i++)
    {
        if (split[i] == "\n")
        {
            split[i] = "\n\t";
        }
        else if (split[i] == "{")
        {
            int level = 1;
            split[i].clear();
            i++;
            while (i < split.size() && level != 0)
            {
                if (split[i] == "{")
                    level++;
                else if (split[i] == "}")
                    level--;
                split[i].clear();
                i++;
            }
        }
        else if (IsLetter(split[i][0]))
        {
            bool nextBrace = false;
            for (size_t j = i + 1; j < split.size(); j++)
            {
                if (split[j] == "{")
                {
                    nextBrace = true;
                }
                if (!IsSpace(split[j]))
                {
                    break;
                }
            }
            if (nextBrace)
                split[i] = "void " + split[i] + "();";
            else if (m_classes.find(split[i]) != m_classes.end())
                split[i] = split[i] + "_typename";
        }
    }

    const std::string toAddFront1 = "#ifndef " + ToUpper(class_name) + "_H_INCLUDED\n";
    const std::string toAddFront2 = "#define " + ToUpper(class_name) + "_H_INCLUDED\n\n";
    const std::string toAddFront3 = "#include \"cmple_api.h\"\n";
    const std::string toAddFront4 = "#include \"classes_implementation.h\"\n\n";
    const std::string toAddFront5 = "class " + class_name + " {\npublic:\n\n\t";
    const std::string toAddBack1 = "\n};\n\n";
    const std::string toAddBack2 = "#endif // " + ToUpper(class_name) + "_H_INCLUDED\n";

    split.insert(split.begin(), toAddFront5);
    split.insert(split.begin(), toAddFront4);
    split.insert(split.begin(), toAddFront3);
    split.insert(split.begin(), toAddFront2);
    split.insert(split.begin(), toAddFront1);
    split.push_back(toAddBack1);
    split.push_back(toAddBack2);


    return split;
}

std::vector<std::string> FileParser::ParseStringsSource(std::vector<std::string> split, const std::string & class_name)
{
    std::map<std::string, std::string> variables;
    std::stack<std::map<std::string, std::string>> stackOfVariables;
    stackOfVariables.push(std::map<std::string, std::string>());
    for (size_t i = 0; i < split.size(); i++)
    {
        if (split[i] == "\n")
        {
            split[i] = "\n";
        }
        if (split[i] == "{")
        {
            stackOfVariables.push(std::map<std::string, std::string>());
        }
        if (split[i] == "}")
        {
            for (std::pair<std::string, std::string> var : stackOfVariables.top())
            {
                variables.erase(var.first);
            }
            stackOfVariables.pop();
        }
        if (FUNCTION.find(split[i]) != FUNCTION.end())
        {
            split[i] = "void " + class_name + "::" + split[i] + "() ";
        }
        if (m_classes.find(split[i]) != m_classes.end())
        {
            const std::string variableName = split[i];
            split[i] = split[i] + "_typename";
            for (size_t j = i + 1; j < split.size(); j++)
            {
                if (!IsSpace(split[j]))
                {
                    stackOfVariables.top()[split[j]] = variableName;
                    variables[split[j]] = variableName;
                    break;
                }
            }
        }
        else if (variables.count(split[i]))
        {
            int64_t depth = 0;
            size_t posEnd = i;
            for (size_t j = i + 1; j < split.size(); j++)
            {
                if (split[j] == "[")
                    depth++;
                if (split[j] == "]")
                    depth--;
                if (split[j] == "&" || (IsSpace(split[j]) && depth == 0))
                {
                    posEnd = j;
                    break;
                }
            }

            if (split[posEnd] == "&")
            {
                split[i] = variables[split[i]] + "_container[" + split[i];
                split[posEnd] = "]->";
            }
            else
            {
                i++;
            }
        }
    }

    if (class_name != DIRECTORY_CREATION_CODE)
    {
        const std::string toAddFront1 = "#include \"classes_implementation.h\"\n\n";
        const std::string toAddBack1 = "\n";

        split.insert(split.begin(), toAddFront1);
        split.push_back(toAddBack1);
    }
    else
    {
        const std::string toAddBack1 = "\n";

        split.push_back(toAddBack1);
    }

    return split;
}

void FileParser::CreateIncludeFiles()
{
    CreateClassesImplementationHeaderFiles();
    CreateClassesImplementationSourceFiles();
    CreateClassesUpdateFiles();
    CreateClassesDisplay3DFiles();
    CreateClassesDisplay2DFiles();
    CreateFilesLoad();
    CreateFilesAudioLoad();
}

void FileParser::CreateClassesImplementationHeaderFiles()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "classes_implementation.h");

    file << "#ifndef CLASSES_IMPLEMENTATION_H_INCLUDED\n";
    file << "#define CLASSES_IMPLEMENTATION_H_INCLUDED\n\n";

    file << "#include <map>\n";
    file << "#include \"cmple_api.h\"\n\n";

    for (std::string className : m_classes)
    {
        file << "class " << className << ";\n";
    }
    file << "\n";

    for (std::string spriteName : m_sprites)
    {
        file << "extern Sprite " << spriteName << ";\n";
    }
    file << "\n";

    for (std::string modelName : m_models)
    {
        file << "extern Model " << modelName << ";\n";
    }
    file << "\n";

    for (std::string soundName : m_sounds)
    {
        file << "extern Sound " << soundName << ";\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "extern std::map <int, " << className << "*> " << className << "_container;\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "extern int " << className << "_objects_number;\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "using " << className << "_typename = int;\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << className << "_typename create_object_" << className << "();\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "void destroy_object_" << className << "(" << className << "_typename id);\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "#include \"" << className << ".h\"\n";
    }
    file << "\n\n";

    file << "#endif // CLASSES_IMPLEMENTATION_H_INCLUDED\n";

    file.close();
}

void FileParser::CreateClassesImplementationSourceFiles()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "classes_implementation.cpp");

    file << "#include \"classes_implementation.h\"\n\n";

    for (std::string spriteName : m_sprites)
    {
        file << "Sprite " << spriteName << ";\n";
    }
    file << "\n";

    for (std::string modelName : m_models)
    {
        file << "Model " << modelName << ";\n";
    }
    file << "\n";

    for (std::string soundName : m_sounds)
    {
        file << "Sound " << soundName << ";\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "std::map <int, " << className << "*> " << className << "_container;\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << "int " << className << "_objects_number = 0;\n";
    }
    file << "\n";

    for (std::string className : m_classes)
    {
        file << className << "_typename create_object_" << className << "() {\n"
            << "\t" << className << " *object = new " << className << ";\n"
            << "\t" << className << "_container[" << className << "_objects_number] = object;\n"
            << "\t" << className << "_container[" << className << "_objects_number]->Create();\n"
            << "\treturn " << className << "_objects_number++;\n" << "}\n\n";
    }

    for (std::string className : m_classes)
    {
        file << "void destroy_object_" << className << "(" << className << "_typename id) {\n"
            << "\t" << className << "_container[id]->Destroy();\n"
            << "\t" << className << "_container.erase(id);\n" << "}\n\n";
    }

    file.close();
}

void FileParser::CreateClassesUpdateFiles()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "classes_display_3d.h");
    for (std::string className : m_classes)
    {
        file << "for(std::pair <int, " << className << "*> i : " << className << "_container) {\n"
            << "\t" << "i.second->Draw3D();\n" << "}\n";
    }
    file.close();
}

void FileParser::CreateClassesDisplay3DFiles()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "classes_update.h");
    for (std::string className : m_classes)
    {
        file << "for(std::pair <int, " << className << "*> i : " << className << "_container) {\n"
            << "\t" << "i.second->Update();\n" << "}\n";
    }
    file.close();
}

void FileParser::CreateClassesDisplay2DFiles()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "classes_display_2d.h");
    for (std::string className : m_classes)
    {
        file << "for(std::pair <int, " << className << "*> i : " << className << "_container) {\n"
            << "\t" << "i.second->Draw2D();\n" << "}\n";
    }
    file.close();
}

void FileParser::CreateFilesLoad()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "files_load.h");

    for (std::string spriteName : m_sprites)
    {
        file << spriteName << ".Load(\"" << DIRECTORY_SPRITES + "\\" + "\\" + spriteName + m_spritesExtensions[spriteName] << "\");\n";
    }
    file << "\n";

    for (std::string modelName : m_models)
    {
        file << modelName << ".Load(\"" << DIRECTORY_MODELS + "\\" + "\\" + modelName + ".obj" << "\");\n";
    }
    file << "\n";

    file.close();
}

void FileParser::CreateFilesAudioLoad()
{
    std::ofstream file;
    file.open(m_directoryToCompile + "\\" + "files_audio_load.h");

    for (std::string soundName : m_sounds)
    {
        file << soundName << ".Load(\"" << DIRECTORY_SOUNDS + "\\" + "\\" + soundName + m_soundsExtensions[soundName] << "\");\n";
    }
    file << "\n";

    file.close();
}

void FileParser::CopyConstInput() const noexcept
{
    CleanDirectory(m_directoryToCompile);
    CopyDirectory(m_directoryConstInput, m_directoryToCompile);
}

void FileParser::CreateBatFile() noexcept
{
#ifdef __WIN32
    std::ofstream file_out(m_directoryToCompile + "\\compile.bat");
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

    for (std::string class_name : m_classes) {
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

    for (std::string class_name : m_classes) {
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
