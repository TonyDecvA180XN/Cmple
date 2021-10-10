#include "Directory.h"

std::vector<std::string> FindFilesInDirectory(std::string directory)
{
    directory += "\\*";
#ifdef _WIN32
    std::vector<std::string> fileList;
    WIN32_FIND_DATA file;
    if (const HANDLE hl = FindFirstFile(directory.c_str(), &file); hl != INVALID_HANDLE_VALUE)
    {
        do
        {
            fileList.push_back(file.cFileName);
        }
        while (FindNextFile(hl, &file) != 0);
        FindClose(hl);
    }
    else
    {
        throw "Error: could not open directory " + directory;
    }
    return fileList;
#endif // _WIN32
#ifdef __unix__
    std::vector < std::string > file_list;
    DIR* dir = opendir(directory.c_str());
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

void CopyDirectory([[maybe_unused]] std::string from, [[maybe_unused]] std::string to)
{
#ifdef __WIN32
    std::string comand;
    comand = "xcopy " + from + " " + to + "/E /H /C /R /Q /Y >NUL";
    system(comand.c_str());
#endif // __WIN32
#ifdef __unix__

#endif // __unix__
}

void CleanDirectory([[maybe_unused]] std::string path)
{
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

std::string RemoveFirstDirectory(std::string path)
{
    for (int i = 0; i <= static_cast<int>(path.size()); i++)
    {
        if (path[i] == '\\')
        {
            return path.substr(i);
        }
    }
    return path;
}

bool IsLetter(const char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

bool IsLetterOrDigit(const char c)
{
    return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '_';
}

bool IsSpace(const char c)
{
    return c == ' ' || c == '\t' || c == '\n';
}

bool IsSpace(const std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!IsSpace(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool IsCpp(const std::string str)
{
    return str.size() >= 4 && str.substr(str.size() - 4) == ".cpp";
}

bool IsImage(const std::string str)
{
    return str.size() >= 4 && (str.substr(str.size() - 4) == ".bmp" ||
        str.substr(str.size() - 4) == ".png" ||
        str.substr(str.size() - 4) == ".jpg");
}

bool IsModel(const std::string str)
{
    return str.size() >= 4 && (str.substr(str.size() - 4) == ".obj" ||
        str.substr(str.size() - 4) == ".mtl" ||
        str.substr(str.size() - 4) == ".bmp" ||
        str.substr(str.size() - 4) == ".png" ||
        str.substr(str.size() - 4) == ".jpg");
}

bool IsSound(const std::string str)
{
    return str.size() >= 4 && (str.substr(str.size() - 4) == ".wav" ||
        str.substr(str.size() - 4) == ".mp3" ||
        str.substr(str.size() - 4) == ".ogg");
}

std::string ToUpper(std::string str)
{
    for (char & c : str)
    {
        if (c >= 'a' && c <= 'z')
        {
            c += 'A' - 'a';
        }
    }
    return str;
}

std::string RemoveExtension(std::string file_name)
{
    if (file_name.empty())
        return file_name;
    for (size_t i = 0; i < file_name.size(); i++)
    {
        if (file_name[i] == '.')
        {
            return file_name.substr(0, i);
        }
    }
    return file_name;
}

std::string GetExtension(std::string file_name)
{
    if (file_name.empty())
        return file_name;
    for (int i = file_name.size() - 1; i >= 0; i--)
    {
        if (file_name[i] == '.')
        {
            return file_name.substr(i);
        }
    }
    return "";
}
