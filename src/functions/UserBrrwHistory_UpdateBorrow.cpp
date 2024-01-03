//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../include/function_definitions.h"
int UserBrrwHistory_UpdateBorrow(BorrowHistory &brrw_history, std::string bk_ID)
{
    BookNode  brrw_bk_node = {
            .book_ID           = std::move(bk_ID),
            .borrow_date       = GetCurrentTime(),
            .giveback_date     = {},
            .borrow_state_flag = -1
    };

    brrw_history.borrowed_books_cur++;
    brrw_history.borrowed_books_acc++;
    brrw_history.book_list.emplace_back(brrw_bk_node);
    return 0;
}