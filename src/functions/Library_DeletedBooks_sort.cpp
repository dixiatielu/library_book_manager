//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

int Library_DeletedBooks_sort(Library &lib) {
    std::queue<int> books_deleted_position;
    for (int i = 1; i <= BOOK_MAX_NUM; i++) {
        if (lib.book_list[i].lend_state_flag == -3) {
            books_deleted_position.push(i);
            continue;
        } else if (books_deleted_position.empty()) {
            continue;
        } else {
            LibraryBook_Copy(lib.book_list[books_deleted_position.front()], lib.book_list[i]);
            lib.book_list[i].lend_state_flag = -3;
            books_deleted_position.push(i);
            books_deleted_position.pop();
        }
    }
    return 0;
}