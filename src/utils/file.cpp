#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>

std::string ExePath()
{
    TCHAR buffer[MAX_PATH] = {0};
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string result = std::string(buffer);
    std::string::size_type pos = result.find_last_of("\\/");
    return result.substr(0, pos);
}