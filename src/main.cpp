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
#include ".\include\main.h"
using namespace std;
int main()
{
    system("chcp 65001"); // 终端UTF-8编码
    Library library_local(0);

    while(true)
    {
        LibraryBook_Append_Update_Delete_Director(library_local);
        cout << "是否继续键入图书？（0：否，1：是）" << endl;
        int continue_flag;
        cin >> continue_flag;
        if(!continue_flag)
        {
            break;
        }
    }
    library_local.writeToJSONFile("firstTestLib.json");

    return 0;
}