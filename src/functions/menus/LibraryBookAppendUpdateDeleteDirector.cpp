//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

void LibraryBookAppendUpdateDeleteDirector(Library &lib)
{
    std::string bkISBN_input, bkname_input;
    std::vector<int> result_search;

    int mode_flag;
    std::cout << fmt::format("\n{:*^34}\n", "图书信息录入与更新菜单");
    std::cout << "请选择图书信息输入模式\n"
                 "\t1. ISBN\n"
                 "\t2. 书名\n"
                 "\t输入其他任意数字以退出\n"
                 "$?-";
    std::cin >> mode_flag;

    if (!std::cin) {
        std::cout << "请输入数字！\n";
        std::cin.clear();
        std::cin.ignore(500, '\n');						// 清空输入缓冲区
        mode_flag = -1;
    }

    switch (mode_flag)
    {
        case 1:
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            std::cout << "请输入ISBN:";
            std::cin >> bkISBN_input;
            result_search = LibraryBookISBNSearch(lib, bkISBN_input);
            break;

        case 2:
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            std::cout << "请输入书名:";
            std::cin >> bkname_input;
            result_search = LibraryBookNameSearch(lib, bkname_input);
            break;

        default:// 程序出口
//            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            std::cout << "\n退出输入模式\n\n\n";
            return;
    }

    if (result_search.empty()) {
        int append_flag; // 选项，是否添加书
        std::cout << "\n图书馆中无该图书信息\n";
        std::cout << "是否要添加该书？\n"
                     "\t0. 否\n"
                     "\t1. 是\n"
                     "\t输入其他任意字符以退出\n"
                     "$?-";
        std::cin >> append_flag;

        switch (append_flag) {
            case 0:
                std::cin.ignore(500, '\n');						// 清空输入缓冲区
                std::cout << "退出\n";
                break;

            case 1:
                std::cin.ignore(500, '\n');						// 清空输入缓冲区
                if (lib.book_amount_total >= BOOK_MAX_NUM) {
                    std::cout << "图书馆藏书已满\n";
                } else{
                    LibraryBook_Append(lib.book_list[lib.book_amount_total + 1], bkname_input, bkISBN_input);
                    lib.book_amount_total++;
                    lib.book_amount_real++;
                }
                break;
            default:
                std::cin.ignore(500, '\n');						// 清空输入缓冲区
                break;
        }
    } else{
        std::cout << "\n图书馆中有该图书信息\n";
        LibraryBook_Update_Copy_Delete_Director(lib, result_search);
    }
}