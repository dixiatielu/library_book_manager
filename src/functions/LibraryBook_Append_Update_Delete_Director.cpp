//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

void LibraryBook_Append_Update_Delete_Director(Library &lib)
{
    std::string bkISBN_input, bkname_input;
    std::vector<int> result_search;

    int mode_flag;
    std::cout << "请选择输入模式\n"
                 "\t1. ISBN\n"
                 "\t2. 书名\n"
                 "\t输入其他任意字符以退出\n"
                 "$?-";
    std::cin >> mode_flag;

    switch (mode_flag)
    {
        case 1:
            std::cout << "请输入ISBN:";
            std::cin >> bkISBN_input;
            result_search = LibraryBookISBNSearch(lib, bkISBN_input);
            break;

        case 2:
            std::cout << "请输入书名";
            std::cin >> bkname_input;
            result_search = LibraryBookNameSearch(lib, bkname_input);
            break;

        default:// 程序出口
            return;
    }

    if (result_search.empty()) {
        int append_flag; // 选项，是否添加书
        std::cout << "图书馆中无相同书\n";
        std::cout << "是否要添加该书？\n"
                     "\t0. 否\n"
                     "\t1. 是\n"
                     "$?-";
        std::cin >> append_flag;

        if (append_flag == 0){
            std::cout << "退出\n";
        } else if (lib.book_amount >= BOOK_MAX_NUM) {
            std::cout << "图书馆藏书已满\n";
        } else{
            lib.book_amount++;
            LibraryBook_Append(lib.book_list[lib.book_amount], bkname_input, bkISBN_input);
        }
    } else{
        std::cout << "图书馆中有相同书\n";
        LibraryBook_Update_Copy_Delete_Director(lib, result_search);
    }
}