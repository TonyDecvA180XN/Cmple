#pragma once

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

    static std::vector<std::string> SplitData(const std::string & data);

    void ParseFile(std::string file_name);
    void ParseCreationCode();

    std::vector<std::string> ParseStringsHeader(std::vector<std::string> split, const std::string & class_name);
    std::vector<std::string> ParseStringsSource(std::vector<std::string> split, const std::string & class_name);

    void CreateIncludeFiles();

    void CreateClassesImplementationHeaderFiles();
    void CreateClassesImplementationSourceFiles();
    void CreateClassesUpdateFiles();
    void CreateClassesDisplay3DFiles();
    void CreateClassesDisplay2DFiles();
    void CreateFilesLoad();
    void CreateFilesAudioLoad();
    void CopyConstInput() const noexcept;
    void CreateBatFile() noexcept;
};
