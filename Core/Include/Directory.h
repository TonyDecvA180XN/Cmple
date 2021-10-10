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

inline const std::string DIRECTORY_INPUT_DEFAULT = "input";
inline const std::string DIRECTORY_CONST_INPUT_DEFAULT = "const_input";
inline const std::string DIRECTORY_TO_COMPILE_DEFAULT = "to_compile";
inline const std::string DIRECTORY_SCRIPTS = "scripts";
inline const std::string DIRECTORY_SPRITES = "sprites";
inline const std::string DIRECTORY_MODELS = "models";
inline const std::string DIRECTORY_SOUNDS = "sounds";
inline const std::string DIRECTORY_CREATION_CODE = "creation_code";

inline const std::string DIRECTORY_CURRENT = ".";
inline const std::string DIRECTORY_PREVIOUS = "..";
inline const std::set<std::string> FUNCTION = {"Create", "Destroy", "Update", "Draw3D", "Draw2D"};

std::vector<std::string> FindFilesInDirectory(std::string directory);
void CopyDirectory(std::string from, std::string to);
void CleanDirectory(std::string path);

std::string RemoveFirstDirectory(std::string & path);

bool IsLetter(char c);
bool IsLetterOrDigit(char c);
bool IsSpace(char c);
bool IsSpace(const std::string & str);
bool IsCpp(const std::string & str);
bool IsImage(const std::string & str);
bool IsModel(const std::string & str);
bool IsSound(const std::string & str);

std::string ToUpper(std::string str);

std::string RemoveExtension(std::string & file_name);
std::string GetExtension(std::string & file_name);

#endif // DIRECTORY_H_INCLUDED
