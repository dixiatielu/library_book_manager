//
// Created by 地铁DXTL on 2024/1/4.
//

#include "../../headers/function_definitions.h"
void UserBorrowAndGiveBackMenu(Library &lib, BorrowerGroup &gp)
{
    int mode_flag;
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
    std::cout << fmt::format("\n{:*^34}\n", "图书借阅与归还菜单");
    std::cout << "请选择借阅/归还图书图书\n"
                 "\t1. 借阅图书\n"
                 "\t2. 归还图书\n"
                 "输入其他任意数字以退出\n"
                 "$-";
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色
    std::cin >> mode_flag;
    std::cin.ignore(500, '\n');						// 清空输入缓冲区

    if (!std::cin) {
        std::cout << "请输入数字！\n";
        std::cin.clear();
        mode_flag = -1;
    }

    switch (mode_flag) {
        case 1:
            UserBookBorrow(gp, lib);
//            std::cout << "\n借书成功！\n";
            break;

        case 2:
            UserBookGiveback(gp, lib);
//            std::cout << "\n还书成功\n";
            break;

        default:
            break;
    }
    std::cout << "\n退出借阅与归还程序\n\n\n";
}