//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../include/function_definitions.h"
int BookLendState_UpdateGiveback(Library &lib, const std::string& giveback_bkID)
{
    std::vector<int> result_position = LibraryBookIDSearch(lib, giveback_bkID);
    lib.book_list[result_position.front()].lend_state_flag = 0; // TODO: 若要考虑运输时间，可赋值为1
    return 0;
}