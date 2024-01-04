//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"
using namespace std;
void DataBackupAndRestoreMenu(Library &lib, BorrowerGroup &gp)
{
    int choice;
    do {
        cout << "*****数据备份与恢复菜单*****" << endl;
        cout << "1. 图书数据备份" << endl;
        cout << "2. 图书数据恢复" << endl;
        cout << "3. 用户数据备份" << endl;
        cout << "4. 用户数据恢复" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择功能（输入相应数字）：";
        cin >> choice;

        string fileExtension = ".json";
        string backupFileName;
        string restoreFileName;
        switch (choice) {
            case 1: {
                cout << "请输入备份文件名（包含路径）：";
                cin >> backupFileName;
                lib.writeToJSONFile(backupFileName + fileExtension);
            }
                break;
            case 2: {
                cout << "请输入恢复文件名（包含路径）：";
                cin >> restoreFileName;
                lib.readFromJSONFile(restoreFileName + fileExtension);
            }
                break;
            case 3:{
                cout << "请输入备份文件名（包含路径）：";
                cin >> backupFileName;
                gp.writeToJSONFile(backupFileName + fileExtension);

            }
                break;
            case 4: {
                cout << "请输入恢复文件名（包含路径）：";
                cin >> restoreFileName;
                gp.readFromJSONFile(restoreFileName + fileExtension);
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