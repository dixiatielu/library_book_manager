//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

void LibraryBookAppendUpdateDeleteDirector(Library &lib)
{
    std::string bkISBN_input, bkname_input, bkID_input;
    std::vector<int> result_search;

    int mode_flag;

//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
    std::cout << fmt::format("\n{:*^34}\n", "图书信息录入与更新输入模式菜单");
    std::cout << "请选择图书根信息输入模式\n"
                 "\t1. ISBN\n"
                 "\t2. 书名\n"
                 "\t3. ID（图书唯一识别码）\n"
                 "\t输入其他任意数字以退出\n"
                 "$?-";
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色

    std::cin >> mode_flag;
    std::cin.ignore(500, '\n');						// 清空输入缓冲区

    if (!std::cin) {
        std::cout << "输入非数字！\n"
                     "将退出图书信息录入与更新程序\n";
        std::cin.clear();
        std::cin.ignore(500, '\n');						// 清空输入缓冲区
        mode_flag = -1;
    }

    switch (mode_flag)
    {
        case 1:
            std::cout << "请输入ISBN:";
            std::cin >> bkISBN_input;
            result_search = LibraryBookISBNSearch(lib, bkISBN_input);
            break;

        case 2:
            std::cout << "请输入书名:";
            std::cin >> bkname_input;
            result_search = LibraryBookNameSearch(lib, bkname_input);
            break;

        case 3:
            std::cout << "请输入ID:";
            std::cin >> bkID_input;
            result_search = LibraryBookIDSearch(lib, bkID_input);
            break;

        default:// 程序出口
            std::cout << "退出图书信息录入与更新程序" << std::endl;
            return;
    }

    if (result_search.empty()&&(mode_flag != 3)) {
        int append_flag; // 选项，是否添加书
        std::cout << "\n图书馆中无该图书信息\n";
        std::cout << "是否要添加该书？\n"
                     "\t0. 否\n"
                     "\t1. 是\n"
                     "\t输入其他任意数字以退出\n"
                     "$?-";
        std::cin >> append_flag;
        std::cin.ignore(500, '\n');                        // 清空输入缓冲区

        if (!std::cin) {
            std::cout << "输入非数字！\n"
                         "将退出图书信息录入与更新程序\n";
            std::cin.clear();
            mode_flag = -1;
        }

        switch (append_flag) {
            case 0:
                std::cout << "未添加\n";
                break;

            case 1:
                if (lib.book_amount_total >= BOOK_MAX_NUM) {
                    std::cout << "图书馆藏书已满\n";;
                } else {
                    LibraryBook_Append(lib.book_list[lib.book_amount_total + 1], bkname_input, bkISBN_input);
                    lib.book_amount_total++;
                    lib.book_amount_real++;;
                }
                break;

            default:;
                break;
        }

    } else if (result_search.empty()&&(mode_flag == 3)) {
        std::cout << "不能直接以ID（图书唯一识别码）保存图书信息";

    } else{
        std::cout << "\n图书馆中有该图书信息\n";
        LibraryBook_Update_Copy_Delete_Director(lib, result_search);
    }

    std::cout << "\n退出图书信息录入与更新程序\n\n\n";
    return;
}