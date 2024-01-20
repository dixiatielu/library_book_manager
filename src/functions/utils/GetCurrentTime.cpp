//
// Created by 地铁DXTL on 2024/1/3.
//

#include "../../headers/function_definitions.h"

Time Get_CurrentTime() {
    static time_t raw_curtime; // 从 1900 年至当前时间的秒数
    static struct tm *curtime; // 秒数转换为年、月、日信息变量结构体
    Time r_time;               // 用于返回的自定义时间结构体

    time(&raw_curtime); // 获取从 1900 年至当前时间的秒数，并保存在 (time_t) raw_curtime 变量中
    curtime = gmtime(&raw_curtime); // 将 (time_t) raw_curtime 对应的秒数转换为年月日信息保存在 curtime 中

    r_time.YY = std::to_string(curtime->tm_year + 1900); // 获取 curtime 中的年份信息并转换为公历
    r_time.MM = std::to_string(curtime->tm_mon + 1);     // 获取 curtime 中的月份信息并转换为公历
    r_time.DD = std::to_string(curtime->tm_mday);        // 获取 curtime 中的日期信息

    return r_time; // 返回获取并转换后的信息
}