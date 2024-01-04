//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"

using namespace std;
int ShowMainMenu(Library &lib)
{
    cout << "*****主菜单*****" << endl;
    cout << "1. 图书信息录入与更新" << endl;
    cout << "2. 图书检索与查询" << endl;
    cout << "3. 借阅与归还管理" << endl;
    cout << "4. 用户权限管理" << endl;
    cout << "5. 系统数据备份与恢复" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请选择功能（输入相应数字）：";
    int choice;
    cin >> choice;
    switch (choice)
    {
        case 1:
        {
            // 调用图书信息录入与更新的函数
            while(true) {
                LibraryBookAppendUpdateDeleteDirector(lib);
                cout << "是否继续键入图书？（0：否，1：是）" << endl;
                int continue_flag;
                cin >> continue_flag;
                if (!continue_flag) {
                    break;
                }
            }
            break;
        }
        case 2: {
            // 调用图书检索与查询的函数
            LibrarySearchMenu(lib);
            break;
        }
        case 3: {
            // 调用借阅与归还管理的函数
            BorrowAndGiveBackMenu(lib);
            break;
        }
        case 4: {
            // 调用用户权限管理的函数
            // UserManagement();
            break;
        }
        case 5:{
            // 调用系统数据备份与恢复的函数
            DataBackupAndRestoreMenu(lib);
            break;
        }
        case 0:
            cout << "感谢使用，再见！" << endl;
            break;
        default:
            cout << "无效的选项，请重新选择。" << endl;
    }
    return choice;
}