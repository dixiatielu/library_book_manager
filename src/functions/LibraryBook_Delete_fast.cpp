//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

void LibraryBook_Delete_fast(Library &lib, int bk_position)
{
    lib.book_list[bk_position].lend_state_flag = -3;
    lib.book_amount--;
}