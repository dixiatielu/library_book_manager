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

#include "headers/macro.h"
#include "headers/function_definitions.h"

using namespace std;

int main() {
    system("chcp 65001"); // 终端UTF-8编码
    system("cls");

    Library library_local(0);
    BorrowerGroup group_local(0);
    while (true) {
        if (ShowMainMenu(library_local, group_local) == 0) {
            break;
        }

        system("pause");
    }

    return 0;
}