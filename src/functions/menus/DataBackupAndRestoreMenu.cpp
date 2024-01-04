//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../../headers/function_definitions.h"
using namespace std;
void DataBackupAndRestoreMenu(Library &lib, BorrowerGroup &gp)
{
    int choice;
    do {
//        SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
        cout << fmt::format("\n{:*^34}\n", "系统数据备份与恢复");
        cout << "1. 图书数据备份" << endl;
        cout << "2. 图书数据导入" << endl;
        cout << "3. 用户数据备份" << endl;
        cout << "4. 用户数据导入" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择功能（输入相应数字）：";

//        SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色

        cin >> choice;

        string fileExtension = ".json";
        string backupFilePath;
        string restoreFilePath;
        switch (choice) {
            case 1: {
                cout << "\n是否要永久删除所有已删除的图书数据：\n"
                        "\t1. 是\n"
                        "\t2. 否\n"
                        "输入其他数字以退出图书数据备份程序\n"
                        "$-";
                cin >> choice;
                std::cin.ignore(500, '\n');						// 清空输入缓冲区

                if (!cin) {
                    cout << "输入非数字！\n"
                            "将退出图书数据备份程序\n";
                    cin.clear();
                    choice = 0;
                }
                switch (choice) {
                    case 1:
                        cout << "请输入备份文件名（包含路径）：";
                        cin >> backupFilePath;
                        lib.writeToJSONFile_DeleteNotExistBooks(backupFilePath + fileExtension);
                        cout << fmt::format("\n图书数据备份成功\n"
                                            "已保存在 {} 路径下\n\n", backupFilePath + fileExtension);
                        break;

                    case 2:
                        cout << "请输入备份文件名（包含路径）：";
                        cin >> backupFilePath;
                        lib.writeToJSONFile_Origin(backupFilePath + fileExtension);
                        cout << fmt::format("\n图书数据备份成功\n"
                                            "已保存在 {} 路径下\n\n", backupFilePath + fileExtension);
                        break;

                    default:
                        cout << "\n退出图书数据备份程序\n";
                        break;
                }
            }
                break;
            case 2: {
                cout << "请输入导入文件名（包含路径）：";
                cin >> restoreFilePath;
                lib.readFromJSONFile(restoreFilePath + fileExtension);
                cout << fmt::format("\n图书数据导入成功\n"
                                    "由 ./{} 路径下导入\n\n", restoreFilePath + fileExtension);
            }
                break;
            case 3:{
                cout << "请输入备份文件名（包含路径）：";
                cin >> backupFilePath;
                gp.writeToJSONFile(backupFilePath + fileExtension);
                cout << fmt::format("\n用户数据备份成功\n"
                                    "已保存在 {} 路径下\n\n", backupFilePath + fileExtension);

            }
                break;
            case 4: {
                cout << "请输入恢复文件名（包含路径）：";
                cin >> restoreFilePath;
                gp.readFromJSONFile(restoreFilePath + fileExtension);
                cout << fmt::format("\n用户数据导入成功\n"
                                    "由 {} ./路径下导入\n\n", restoreFilePath + fileExtension);
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