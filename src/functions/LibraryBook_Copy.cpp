//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

int LibraryBook_Copy(Book &bk, Book bk_sample)
{
    bk = std::move(bk_sample);
    return 0;
}