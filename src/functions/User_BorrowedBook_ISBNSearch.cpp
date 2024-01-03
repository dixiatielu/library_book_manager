//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../include/function_definitions.h"
std::vector<int> User_BorrowedBook_ISBNSearch(Library lib, BorrowHistory brrw_history, const std::string& bk_ISBN)
{
    std::string tmp_bkID;
    std::vector<int> tmp_bk_position;
    std::vector<int> rt_bk_position;
    for (int i = 0; i <= brrw_history.book_list.size() - 1; i++) {
        if ((brrw_history.book_list[i].borrow_state_flag == -1)
            ||(brrw_history.book_list[i].borrow_state_flag == -2)) {

            tmp_bkID = brrw_history.book_list[i].book_ID;
            tmp_bk_position = LibraryBookIDSearch(lib, tmp_bkID);

            if (lib.book_list[tmp_bk_position.front()].publish_info.ISBN == bk_ISBN) {

                rt_bk_position.emplace_back(i);
                return rt_bk_position; // 函数出口，因为已限制用户相同图书只能借一本

            } else{
                continue;
            }

        } else{
            continue;
        }
    }
    return rt_bk_position;
}