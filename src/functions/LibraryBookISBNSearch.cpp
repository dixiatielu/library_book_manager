//
// Created by 地铁DXTL on 2024/1/3.
//
#include "../include/function_definitions.h"

std::vector<int> LibraryBookISBNSearch(Library lib, const std::string& bk_ISBN)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].publish_info.ISBN == bk_ISBN) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    return bk_position;
}