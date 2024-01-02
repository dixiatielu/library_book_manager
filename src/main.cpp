/**
 * @file main.cpp
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief 测试
 * @version 0.2
 * @date 2023-12-26
 *
 * @copyright Copyright (c) 2023
 *
**/
#include ".\include\main.h"

int main(void)
{
    system("chcp 936");
    Book books[BOOK_MAX_NUM + 1];
    Library library_local = {
        .book_amount = 0,
        .book_list = books
    };

    // Time a = TimeGetCurrent();
    // std::cout << fmt::format("YY{}MM{}DD{}", a.YY, a.MM, a.DD);

    // Book a;
    // std::cout << a;


    LibraryBook_Append_Update_Delete_Director(library_local);
    std::cout << library_local.book_list[1];

    return 0;
}