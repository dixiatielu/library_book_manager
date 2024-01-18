//
// Created by Cp on 2024/01/18.
//
#include "../../headers/function_definitions.h"

bool isFileExist(const std::string& file_name)
{
    bool file_state_flag;
    std::ifstream f_in(file_name);
    file_state_flag = f_in.good();
    f_in.close();

    return file_state_flag;
}