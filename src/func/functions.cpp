Time TimeGetCurrent(void)
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

Time TimeGetInput(void)
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

        } else if ((tmp_YY <= 0) || (tmp_YY - (int)tmp_YY != 0)) { // 当输入不是正整数时
			std::cout << "请输入正整数！\n\n";			     // 输出提示
			std::cin.ignore(500, '\n');						// 清空输入缓冲区
			continue;										// 重新开始输入循环

		} else{											    // 当输入的总结点数合法时
            break;
		}
    }
    while (true) {
        std::cout << "请输入月份：";
        std::cin >> tmp_MM;

        if (!std::cin) {
			std::cout << "请输入数字！\n\n";			     // 输出提示
			std::cin.clear();								// 清除std::cin异常指示
			std::cin.ignore(500, '\n');						// 清空输入缓冲区
			continue;										// 重新开始输入循环

        } else if ((tmp_MM <= 0) || (tmp_MM - (int)tmp_MM != 0)) { // 当输入不是正整数时
			std::cout << "请输入正整数！\n\n";			     // 输出提示
			std::cin.ignore(500, '\n');						// 清空输入缓冲区
			continue;										// 重新开始输入循环

		} else{											    // 当输入的总结点数合法时
            break;
		}
    }
    while (true) {
        std::cout << "请输入日期：";
        std::cin >> tmp_DD;

        if (!std::cin) {
			std::cout << "请输入数字！\n\n";			     // 输出提示
			std::cin.clear();								// 清除std::cin异常指示
			std::cin.ignore(500, '\n');						// 清空输入缓冲区
			continue;										// 重新开始输入循环

        } else if ((tmp_DD <= 0) || (tmp_DD - (int)tmp_DD != 0)) { // 当输入不是正整数时
			std::cout << "请输入正整数！\n\n";			     // 输出提示
			std::cin.ignore(500, '\n');						// 清空输入缓冲区
			continue;										// 重新开始输入循环

		} else{											    // 当输入的总结点数合法时
            break;
		}
    }

    Time r_time = {.YY = std::to_string(tmp_YY),
                   .MM = std::to_string(tmp_MM),
                   .DD = std::to_string(tmp_DD)};

    return r_time;
}
