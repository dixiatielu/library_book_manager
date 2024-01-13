//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

using namespace std;
int ShowMainMenu(Library &lib, BorrowerGroup &gp)
{
    system("cls");

    int choice;
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
    cout << fmt::format("\n{:*^34}", "主菜单") << endl;
    cout << "1. 图书信息录入与更新" << endl;
    cout << "2. 图书信息检索" << endl;
    cout << "3. 图书借阅与归还" << endl;
    cout << "4. 用户信息管理" << endl;
    cout << "5. 系统数据备份与恢复" << endl;
    cout << "6. 图书馆信息速览" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请选择功能（输入相应数字）：";
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色

//    std::cin.ignore(500, '\n');						// 清空输入缓冲区
    cin >> choice;
    std::cin.ignore(500, '\n');						// 清空输入缓冲区

    if (!cin) {
        cout << "输入非数字！\n"
                "将退出系统\n\n\n";
        cin.clear();
        std::cin.ignore(500, '\n');						// 清空输入缓冲区
        choice = 0;
    }
    switch (choice)
    {
        case 1:
        {
            // 调用图书信息录入与更新的函数
            while(true) {
                LibraryBookAppendUpdateDeleteDirector(lib);
                cout << "\n是否继续录入和更新图书信息？（1：是，0：否）：";
                int continue_flag;
                cin >> continue_flag;
                cin.ignore(500, '\n');						// 清空输入缓冲区

                if ((!continue_flag)||(!cin)) {
                    cin.clear();
                    cout << "\n退出图书信息录入与更新功能\n";
                    break;
                }
            }
            break;
        }

        case 2:
            // 调用图书检索的函数
            LibrarySearchMenu(lib);
            break;

        case 3:
            // 调用借阅与归还管理的函数
            UserBorrowAndGiveBackMenu(lib, gp);
            break;

        case 4:
            // 调用用户权限管理的函数
            UserManagement(gp);
            break;

        case 5:
            // 调用系统数据备份与恢复的函数
            DataBackupAndRestoreMenu(lib, gp);
            break;

        case 6:
            Library_User_InfoMenu(lib, gp);
            break;

        case 0:
            cout << "感谢使用，再见！" << endl;
            break;

        default:
            cout << "无效的选项，请重新选择。" << endl;
            break;
    }
    return choice;
}