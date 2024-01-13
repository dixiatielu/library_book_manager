//
// Created by 地铁DXTL on 2024/1/4.
//

#include "../../headers/function_definitions.h"

void LibrarySearchMenu(const Library &lib) {
    std::string bkISBN_input, bkname_input, bkID_input;
    std::vector<int> result_search;

    int mode_flag;

//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
    std::cout << fmt::format("\n{:*^34}\n", "图书检索搜索模式菜单");
    std::cout << "请选择图书根信息搜索模式\n"
                 "\t1. ISBN\n"
                 "\t2. 书名\n"
                 "\t3. ID（图书唯一识别码）\n"
                 "\t输入其他任意数字以退出\n"
                 "$?-";
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色

    std::cin >> mode_flag;
    std::cin.ignore(500, '\n');                        // 清空输入缓冲区

    if (!std::cin) {
        std::cout << "输入非数字！\n"
                     "将退出图书信息录入与更新程序\n";
        std::cin.clear();
        std::cin.ignore(500, '\n');                        // 清空输入缓冲区
        mode_flag = -1;
    }

    switch (mode_flag) {
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
            std::cout << "\n退出图书检索程序\n\n\n";
            return;
    }

    if (!result_search.empty()) {

        std::cout << fmt::format("\n找到了{:-^5}本符合搜索要求的书\n", result_search.size());
        for (int i = 0; i <= result_search.size() - 1; i++)
            std::cout << lib.book_list[result_search[i]] << std::endl << "--------------------------\n";

        std::vector<int> bk_overdue, bk_lent, bk_available, bk_transit;
        for (int i = 0; i <= result_search.size() - 1; i++) {
            switch (lib.book_list[result_search[i]].lend_state_flag) {
                case -2:
                    bk_overdue.emplace_back(result_search[i]);
                    break;

                case -1:
                    bk_lent.emplace_back(result_search[i]);
                    break;

                case 0:
                    bk_available.emplace_back(result_search[i]);
                    break;

                case 1:
                    bk_transit.emplace_back(result_search[i]);
                    break;

                default:
                    std::cerr << "Error occurred in book search...";
                    exit(1);
                    break;
            }
        }

        std::cout << "\n图书出借状态：\n";
        // Important: (vector).size() 返回 unsigned 类型
        // 也可以使用 < 比较实现
        std::cout << fmt::format("\t{:-^12}：{:^3}本\n", "逾期状态", bk_overdue.size());
        for (int i = 0; i <= (signed) bk_overdue.size() - 1; i++) {
            std::cout << fmt::format("\t\t{}: {}\n", i + 1, lib.book_list[bk_overdue[i]].identification);
        }

        std::cout << fmt::format("\t{:-^12}：{:^3}本\n", "借出状态", bk_lent.size());
        for (int i = 0; i <= (signed) bk_lent.size() - 1; i++) {
            std::cout << fmt::format("\t\t{}: {}\n", i + 1, lib.book_list[bk_lent[i]].identification);
        }

        std::cout << fmt::format("\t{:-^12}：{:^3}本\n", "在馆状态", bk_available.size());
        for (int i = 0; i <= (signed) bk_available.size() - 1; i++) {
            std::cout << fmt::format("\t\t{}: {}\n", i + 1, lib.book_list[bk_available[i]].identification);
        }

        std::cout << fmt::format("\t{:-^12}：{:^3}本\n", "在途状态", bk_transit.size());
        for (int i = 0; i <= (signed) bk_transit.size() - 1; i++) {
            std::cout << fmt::format("\t\t{}: {}\n", i + 1, lib.book_list[bk_transit[i]].identification);
        }

    } else {
        std::cout << "\n未找到符合搜索要求的书\n";
    }

    std::cout << "\n退出图书检索程序\n\n\n";
}
