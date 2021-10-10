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

class FileParser
{
public:
    FileParser(int argc, char ** argv);

    void Parse();

private:
    std::string m_directoryInput;
    std::string m_directoryConstInput;
    std::string m_directoryToCompile;
    bool m_gccCreateBat = false;
    bool m_gccAutoExecute = false;
    std::set<std::string> m_classes;
    std::set<std::string> m_sprites;
    std::map<std::string, std::string> m_spritesExtensions;
    std::set<std::string> m_models;
    std::set<std::string> m_sounds;
    std::map<std::string, std::string> m_soundsExtensions;

    void ProcessArguments(int argc, char ** argv);

    void ReadInputClasses();
    void ReadInputSprites();
    void ReadInputModels();
    void ReadInputSounds();

    static std::deque<std::string> SplitData(std::string data);

    void ParseFile(std::string file_name);
    void ParseCreationCode();

    std::deque<std::string> ParseStringsHeader(std::deque<std::string> split, std::string class_name);
    std::deque<std::string> ParseStringsSource(std::deque<std::string> split, std::string class_name);

    void CreateIncludeFiles();

    void CreateClassesImplementationHeaderFiles();
    void CreateClassesImplementationSourceFiles();
    void CreateClassesUpdateFiles();
    void CreateClassesDisplay3DFiles();
    void CreateClassesDisplay2DFiles();
    void CreateFilesLoad();
    void CreateFilesAudioLoad();
    void CopyConstInput() const;
    static void CreateBatFile();
};

#endif // FILEPARSER_H_INCLUDED
