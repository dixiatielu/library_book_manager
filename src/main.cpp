/**
 * @file main.cpp
 * @authors
 * Chengpu
 * dixiatielu
 * @brief 程序入口
 * @version 1.0
 * @date 2024.1
 *
 * @copyright Copyright (c) 2024
 *
**/

#include "./headers/function_definitions.h"

using namespace std;

int main() {
    system("chcp 65001"); // 设置Windows下终端为UTF-8编码
    system("cls");        // 设置Windows下终端清屏

    Library library_local(0);       // 初始化图书馆：
                                                    // 设置当前图书馆藏书量   book_amount_real、
                                                    //              藏书总量 book_amount_total为 0
                                                    // 初始化图书馆书单数组，按宏 BOOK_MAX_NUM 申请内存空间
    BorrowerGroup group_local(0); // 初始化借书者群：
                                                    // 设置当前借书者总量为 0
                                                    // 初始化借书者名单 vector
    while (true) { // 持续运行程序
        if (ShowMainMenu(library_local, group_local) == 0) {
            break;
        }

        system("pause"); // 暂停，直到用户按任意键
    }

    return 0;
}