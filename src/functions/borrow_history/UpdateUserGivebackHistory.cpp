//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

int UpdateUserGivebackHistory(BorrowHistory &brrw_history, int giveback_brrwedbook_numero) {
    brrw_history.borrowed_books_cur--;
    brrw_history.book_list[giveback_brrwedbook_numero].borrow_state_flag = 0; // TODO: 若要考虑罚款问题，可赋值为1
    brrw_history.book_list[giveback_brrwedbook_numero].giveback_date = Get_CurrentTime();
    return 0;
}
