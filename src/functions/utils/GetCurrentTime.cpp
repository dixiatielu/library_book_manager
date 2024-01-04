//
// Created by 地铁DXTL on 2024/1/3.
//

#include "../../headers/function_definitions.h"

Time GetCurrentTime()
{
    static time_t raw_curtime;
    static struct tm *curtime;
    Time r_time;

    time(&raw_curtime);
    curtime = gmtime(&raw_curtime);

    r_time.YY = std::to_string(curtime->tm_year + 1900);
    r_time.MM = std::to_string(curtime->tm_mon + 1);
    r_time.DD = std::to_string(curtime->tm_mday);

    return r_time;
}