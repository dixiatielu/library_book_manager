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

    while (1) {
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
    while (1) {
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
    while (1) {
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

std::vector<int> LibraryBookNameSearch(Library lib, std::string bk_name)
{
    std::vector<int> a;
    return a;
}

std::vector<int> LibraryBookISBNSearch(Library lib, std::string ISBN)
{
    std::vector<int> a;
    return a;
}

void LibraryBook_Append_Update_Delete_Director(Library &lib)
{
    std::string bkISBN_input, bkname_input;
    std::vector<int> result_search;

    int mode_flag;
    std::cout << "请选择输入模式\n"
                  "\t1. ISBN\n"
                  "\t2. 书名\n"
                  "$?-";
    std::cin >> mode_flag;

    switch (mode_flag)
    {
    case 1:
        std::cout << "请输入ISBN:";
        std::cin >> bkISBN_input;
        result_search = LibraryBookISBNSearch(lib, bkISBN_input);
        break;

    case 2:
        std::cout << "请输入书名";
        std::cin >> bkname_input;
        result_search = LibraryBookNameSearch(lib, bkname_input);
        break;

    default:
        break;
    }

    if (result_search.size() == 0) {
        int append_flag;
        std::cout << "图书馆中无相同书\n";
        std::cout << "是否要添加该书？\n"
                      "\t0. 否\n"
                      "\t1. 是\n"
                      "$?-";
        std::cin >> append_flag;

        if (append_flag == 0){
            std::cout << "退出\n";
        } else if (lib.book_amount >= BOOK_MAX_NUM) {
            std::cout << "图书馆藏书已满\n";
        } else{
            LibraryBook_Append(lib.book_list[lib.book_amount + 1], bkname_input, bkISBN_input);
        }
    } else{
        std::cout << "图书馆中有相同书\n";
        LibraryBook_Update_Copy_Delete_Director(lib, result_search);
    }
}

int LibraryBook_Append(Book &bk, const std::string& bk_name, std::string bk_ISBN)
{
    time_t id;
    time(&id); // 使用时间戳作为书本唯一识别码

    if (bk_name.size() != 0) {
        bk.name = bk_name;
        std::cout << "书名已输入\n";
    }
    else {
        std::cout << "请输入书名\n$?-";
        std::cin >> bk.name;
    }
        std::cout << "请输入中图分类号\n$?-";
        std::cin >> bk.classifier;

        std::cout << "\n下面输入作/译者信息\n";
        int authors_num, translator_num;
        std::cout << "请输入作者、译者人数（以空格隔开）\n$?-";
        std::cin >> authors_num >> translator_num;

        bk.authors_info_list.resize(authors_num + translator_num);
        for(int i = 0; i <= authors_num - 1; i++) {
            std::cout << fmt::format("请输入第{:^3}个作者的姓名\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].name;

            std::cout << fmt::format("请输入第{:^3}个作者的性别（0 为男性，1 为女性）\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].gender;

            std::cout << fmt::format("请输入第{:^3}个作者的国籍\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].nationality;

            bk.authors_info_list[i].isTranslator = 0;
        }
        for(int i = authors_num;i <= authors_num + translator_num - 1; i++){
            std::cout << fmt::format("请输入第{:^3}个译者的姓名\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].name;

            std::cout << fmt::format("请输入第{:^3}个译者的性别（0 为男性，1 为女性）\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].gender;

            std::cout << fmt::format("请输入第{:^3}个译者的国籍\n$?-", i+1);
            std::cin >> bk.authors_info_list[i].nationality;

            bk.authors_info_list[i].isTranslator = 1;
        }

        std::cout << "\n下面输入出版信息\n";
        std::cout << "请输入ISBN号\n$?-";
        std::cin >> bk.publish_info.ISBN;

        std::cout << "请输入出版社名称\n$?-";
        std::cin >> bk.publish_info.press;

        std::cout << "请输入出版日期\n";
        bk.publish_info.date = TimeGetInput();

        std::cout << "请输入价格\n$?-";
        std::cin >> bk.publish_info.price;

        bk.lend_state_flag = 0;
        bk.lend_history.lend_times = 0;
        bk.identification = std::to_string(id);

    return 0;
}

void LibraryBook_Update_Copy_Delete_Director(Library &lib, std::vector<int> bk_position)
{

}