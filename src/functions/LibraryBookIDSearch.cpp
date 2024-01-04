//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"
std::vector<int> LibraryBookIDSearch(Library lib, const std::string& bk_ID)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount_total; i++)
    {
        if ((lib.book_list[i].identification == bk_ID) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    return bk_position;
}