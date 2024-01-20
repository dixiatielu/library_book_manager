//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

using namespace std;

int ShowMainMenu(Library &lib, BorrowerGroup &gp) {
    system("cls");  // 设置Windows下终端清屏

    int choice;
    cout << fmt::format("\n{:*^34}", "主菜单") << endl;
    cout << "1. 图书信息录入与更新" << endl;
    cout << "2. 图书信息检索" << endl;
    cout << "3. 图书借阅与归还" << endl;
    cout << "4. 用户信息管理" << endl;
    cout << "5. 系统数据备份与恢复" << endl;
    cout << "6. 图书馆信息速览" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请选择功能（输入相应数字）：";

    cin >> choice;
    std::cin.ignore(500, '\n');                        // 清空输入缓冲区

    if (!cin) { // 当用户输入非数字时
        cout << "输入非数字！\n"
                "将退出系统\n\n\n";
        cin.clear();
        std::cin.ignore(500, '\n');                        // 清空输入缓冲区
        choice = 0;
    }
    switch (choice) {
        case 1: {
            // 调用图书信息录入与更新的函数
            while (true) {
                LibraryBookAppendUpdateDeleteDirector(lib);
                cout << "\n是否继续录入和更新图书信息？（1：是，0：否）：";
                int continue_flag;
                cin >> continue_flag;
                cin.ignore(500, '\n');                        // 清空输入缓冲区

                if ((!continue_flag) || (!cin)) {
                    cin.clear();
                    cout << "\n退出图书信息录入与更新功能\n";
                    break;
                }
            }
            break;
        }

        case 2:
            // 调用图书信息检索的函数
            LibrarySearchMenu(lib);
            break;

        case 3:
            // 调用图书借阅与归还管理的函数
            UserBorrowAndGiveBackMenu(lib, gp);
            break;

        case 4:
            // 调用用户信息管理的函数
            UserManagement(gp);
            break;

        case 5:
            // 调用系统数据备份与恢复的函数
            DataBackupAndRestoreMenu(lib, gp);
            break;

        case 6:
            // 调用图书馆信息速览的函数
            Library_User_InfoMenu(lib, gp);
            break;

        case 0: // 用户输入 0 或其他非数字字符时
            // 退出系统
            cout << "\n感谢使用，再见！" << endl;
            break;

        default: // 发生未知输入错误时
            cout << "\n发生未知输入错误！" << endl;
            exit(1);
    }
    return choice;
}