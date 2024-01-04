//
// Created by 地铁DXTL on 2024/1/3.
//

#include "../../headers/function_definitions.h"

Time GetTimeInput()
{
    float tmp_YY, tmp_MM, tmp_DD;

    while (true) {
        std::cout << "请输入年份：";
        std::cin >> tmp_YY;

        if (!std::cin) {
            std::cout << "请输入数字！\n\n";			     // 输出提示
            std::cin.clear();								// 清除std::cin异常指示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else if (tmp_YY - (int)tmp_YY != 0) {           // 当输入不是整数时
            std::cout << "请输入整数！\n\n";			     // 输出提示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else{											    // 当输入的总结点数合法时
            break;
        }
    }
    while (true) {
        std::cout << "请输入月份：（输入 0 表示无该项信息）";
        std::cin >> tmp_MM;

        if (!std::cin) {
            std::cout << "请输入数字！\n\n";			     // 输出提示
            std::cin.clear();								// 清除std::cin异常指示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else if ((tmp_MM < 0) || (tmp_MM - (int)tmp_MM != 0)) { // 当输入不是正整数时
            std::cout << "请输入非负整数！\n\n";			     // 输出提示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else{											    // 当输入的总结点数合法时
            break;
        }
    }
    while (true) {
        std::cout << "请输入日期：（输入 0 表示无该项信息）";
        std::cin >> tmp_DD;

        if (!std::cin) {
            std::cout << "请输入数字！\n\n";			     // 输出提示
            std::cin.clear();								// 清除std::cin异常指示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else if ((tmp_DD < 0) || (tmp_DD - (int)tmp_DD != 0)) { // 当输入不是正整数时
            std::cout << "请输入非负整数！\n\n";			     // 输出提示
            std::cin.ignore(500, '\n');						// 清空输入缓冲区
            continue;										// 重新开始输入循环

        } else{											    // 当输入的总结点数合法时
            break;
        }
    }

    Time r_time = {.YY = std::to_string((int)tmp_YY),
            .MM = std::to_string((int)tmp_MM),
            .DD = std::to_string((int)tmp_DD)};

    return r_time;
}