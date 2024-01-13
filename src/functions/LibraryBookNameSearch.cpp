//
// Created by 地铁DXTL on 2024/1/3.
//
#include "../headers/function_definitions.h"
#include "utils/KMP/kmp_algorithms_definition.h"

std::vector<int> LibraryBookNameSearch(const Library& lib, const std::string& bk_name)
{
    std::vector<int> bk_position;

    int* nextval = new int[bk_name.length() + 1];
    int* next = new int[bk_name.length() + 1];
    index_construct(next, bk_name);
    nextval_construct(nextval, next, bk_name);

    for (int i = 1; i <= lib.book_amount_total; i++)
    {
        if ((lib.book_list[i].lend_state_flag != -3) && (seek(lib.book_list[i].name, bk_name, nextval, 1, 1))) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    delete [] next;
    delete [] nextval;
    return bk_position;
}