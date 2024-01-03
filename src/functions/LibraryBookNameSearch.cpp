//
// Created by 地铁DXTL on 2024/1/3.
//
#include "../headers/function_definitions.h"

std::vector<int> LibraryBookNameSearch(Library lib, const std::string& bk_name)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].name == bk_name) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    return bk_position;
}