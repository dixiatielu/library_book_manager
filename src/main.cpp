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

#include "headers/macro.h"
#include "headers/function_definitions.h"

using namespace std;

int main() {
    system("chcp 65001"); // 终端UTF-8编码
    system("cls");

    Library library_local(0);
    BorrowerGroup group_local(0);
    while (true) {
        if(ShowMainMenu(library_local,group_local) == 0) {
            break;
        }

        system("pause");
    }
//    library_local.writeToJSONFile_Origin("firstTestLib.json");

    return 0;
}