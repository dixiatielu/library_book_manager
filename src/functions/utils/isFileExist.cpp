//
// Created by Cp on 2024/01/18.
//
#include "../../headers/function_definitions.h"

bool isFileExist(const std::string& filePath)
{
    bool file_state_flag;
    std::ifstream f_in(filePath);
    file_state_flag = f_in.good();
    f_in.close();

    return file_state_flag;
}