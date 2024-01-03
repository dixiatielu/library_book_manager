//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"
using namespace std;
void DataBackupAndRestoreMenu(Library& lib)
{
    int choice;
    do {
        cout << "*****数据备份与恢复菜单*****" << endl;
        cout << "1. 数据备份" << endl;
        cout << "2. 数据恢复" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择功能（输入相应数字）：";
        cin >> choice;

        switch (choice) {
            case 1: {
                string backupFileName;
                cout << "请输入备份文件名（包含路径）：";
                cin >> backupFileName;
                lib.writeToJSONFile(backupFileName);
            }
                break;
            case 2: {
                string restoreFileName;
                cout << "请输入恢复文件名（包含路径）：";
                cin >> restoreFileName;
                lib.readFromJSONFile(restoreFileName);
            }
                break;
            case 0:
                cout << "返回主菜单。" << endl;
                break;
            default:
                cout << "无效的选项，请重新选择。" << endl;
        }
    }while(choice != 0);
}