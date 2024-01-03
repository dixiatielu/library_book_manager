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
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].name == bk_name) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace(bk_position.end(), i);
        } else{
            continue;
        }
    }
    return bk_position;
}

std::vector<int> LibraryBookISBNSearch(Library lib, std::string bk_ISBN)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].publish_info.ISBN == bk_ISBN) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace(bk_position.end(), i);
        } else{
            continue;
        }
    }
    return bk_position;
}

std::vector<int> LibraryBookIDSearch(Library lib, std::string bk_ID)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].identification == bk_ID) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace(bk_position.end(), i);
        } else{
            continue;
        }
    }
    return bk_position;
}

/*-----------------------------------------------------------------------------*/

void LibraryBook_Delete_fast(Library &lib, int bk_position)
{
    lib.book_list[bk_position].lend_state_flag = -3;
    lib.book_amount--;
}

int Library_DeletedBooks_sort(Library &lib)
{
    std::queue<int> books_deleted_position;
    for (int i = 1; i <= BOOK_MAX_NUM; i++) {
        if (lib.book_list[i].lend_state_flag == -3) {
            books_deleted_position.push(i);
            continue;
        } else if (books_deleted_position.size() == 0) {
            continue;
        } else{
            LibraryBook_Copy(lib.book_list[books_deleted_position.front()], lib.book_list[i]);
            lib.book_list[i].lend_state_flag = -3;
            books_deleted_position.push(i);
            books_deleted_position.pop();
        }
    }
    return 0;
}

/*-----------------------------------------------------------------------------*/

int LibraryBook_Copy(Book &bk, Book bk_sample)
{
    bk = bk_sample;
    return 0;
}

/*-----------------------------------------------------------------------------*/

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
        int append_flag; // 选项，是否添加书
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
            LibraryBook_Append(lib.book_list[lib.book_amount], bkname_input, bkISBN_input);
            lib.book_amount++; // 健壮性不足，可通过返回值进一步判断是否应该增加藏书量
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

    if (!bk_name.empty()) {
        bk.name = bk_name;
//        std::cout << "书名已输入\n";
    }
    else {
        std::cout << "请输入书名\n$?-";
        std::cin >> bk.name;
    }
    std::cout << "请输入中图分类号\n$?-";
    std::cin >> bk.classifier;

    std::cout << "\n下面输入作/译者信息\n";
    system("timeout 1");
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
    for(int i = 0;i <= translator_num - 1; i++){
        std::cout << fmt::format("\n请输入第{:^3}个译者的姓名\n$?-", i+1);
        std::cin >> bk.authors_info_list[i + authors_num].name;

        std::cout << fmt::format("请输入第{:^3}个译者的性别（0 为男性，1 为女性）\n$?-", i+1);
        std::cin >> bk.authors_info_list[i + authors_num].gender;

        std::cout << fmt::format("请输入第{:^3}个译者的国籍\n$?-", i+1);
        std::cin >> bk.authors_info_list[i + authors_num].nationality;

        bk.authors_info_list[i].isTranslator = 1;
    }

    std::cout << "\n下面输入出版信息\n";
    system("timeout 1");

    std::cout << "\n下面输入出版信息\n";
    if(!bk_ISBN.empty())
    {
        bk.publish_info.ISBN = bk_ISBN;
    }
    else {
        std::cout << "请输入ISBN号\n$?-";
        std::cin >> bk.publish_info.ISBN;
    }
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


/*-----------------------------------------------------------------------------*/

int UserID_Exist(BorrowerGroup &gp, std::string id)
{
    Borrower* brrwr_nxt_ptr = gp.borrower_list;
    while (brrwr_nxt_ptr != nullptr) {
        if (brrwr_nxt_ptr->ID == id) {
            return 1;
        }
        brrwr_nxt_ptr = brrwr_nxt_ptr->next_borrower;
    }
    return 0;
}

// 需要检查用户是否有借书权限
Borrower* UserValidation_Search_Borrow(BorrowerGroup gp, std::string id)
{
    Borrower* brrwr_nxt_ptr = gp.borrower_list;
    while (brrwr_nxt_ptr != nullptr) {
        if (brrwr_nxt_ptr->ID == id) {
            if (brrwr_nxt_ptr->permission_flag == 0) {
                return brrwr_nxt_ptr;
            } else{
                return nullptr;
            }
        }
        brrwr_nxt_ptr = brrwr_nxt_ptr->next_borrower;
    }
    return nullptr;
}

// 无需检查用户是否有借书权限
Borrower* UserValidation_Search_Giveback(BorrowerGroup gp, std::string id)
{
    Borrower* brrwr_nxt_ptr = gp.borrower_list;
    while (brrwr_nxt_ptr != nullptr) {
        if (brrwr_nxt_ptr->ID == id) {
            return brrwr_nxt_ptr;
        }
        brrwr_nxt_ptr = brrwr_nxt_ptr->next_borrower;
    }
    return nullptr;
}

int UserBookHistory_Append(BorrowHistory brrw_history, std::string bk_ID)
{
    return 0;
}

int BookLendHistory_Append(LendHistory ld_history, std::string brrwr_ID)
{
    return 0;
}

void UserBookBorrow(BorrowerGroup &gp, Library &lib)
{
    Borrower* user_ptr = nullptr;

    std::string user_identification;
    std::cout << "请输入您的ID：";
    std::cin >> user_identification;
    user_ptr = UserValidation_Search_Borrow(gp, user_identification);

    if (user_ptr != nullptr) {
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
        if (result_search.size() != 0) {
            BorrowerNodePTR brrwr_nxt_ptr = nullptr;

            for (int i = 0; i <= result_search.size() - 1; i++) { // 历史查询，不能同时借两本相同ISBN/name的书

                if ((lib.book_list[result_search[i]].lend_state_flag == -1)
                    ||(lib.book_list[result_search[i]].lend_state_flag == -2)) {

                    brrwr_nxt_ptr = lib.book_list[result_search[i]].lend_history.borrower_list_hPTR;
                    for (int i = 0; i <= lib.book_list[result_search[i]].lend_history.lend_times - 1; i++){

                        if (brrwr_nxt_ptr->borrower_ID == user_identification) {

                            std::cout << "该用户下有相同图书处于借出/逾期状态";
                            return;

                        } else{
                            brrwr_nxt_ptr = brrwr_nxt_ptr->next_ptr;
                            continue;
                        }
                    }
                }
            }

            for (int i = 0; i <= result_search.size() - 1; i++) {
                if (lib.book_list[result_search[i]].lend_state_flag == 0) {
                    lib.book_list[result_search[i]].lend_state_flag = -1;

                    UserBookHistory_Append(user_ptr->borrow_history, lib.book_list[result_search[i]].identification);
                    BookLendHistory_Append(lib.book_list[result_search[i]].lend_history, user_identification);
                    // user_ptr->borrow_history.borrowed_books_acc++;
                    // user_ptr->borrow_history.borrowed_books_cur++;
                    // 并入 UB_A 函数

                    std::cout << "借书成功";
                    return;
                }
            }

            std::cout << "该书均已借出！";
            return;

        } else{
            std::cout << "查无此书！";
            return;
        }

    } else if (!UserID_Exist(gp, user_identification)) {
        std::cout << "不存在该用户！";
        return;
    } else{
        std::cout << "该用户无借书权限";
        return;
    }
}


void UserBookGiveback(BorrowerGroup &gp, Library &lib)
{
    Borrower* user_ptr = nullptr;

    std::string user_identification;
    std::cout << "请输入您的ID：";
    std::cin >> user_identification;
    user_ptr = UserValidation_Search_Giveback(gp, user_identification);

    if (user_ptr != nullptr) {
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
                result_search = User_BorrowedBook_ISBNSearch(user_ptr->borrow_history, bkISBN_input);
                // result_search = LibraryBookISBNSearch(lib, bkISBN_input);
                break;

            case 2:
                std::cout << "请输入书名";
                std::cin >> bkname_input;
                result_search = User_BorrowedBook_NameSearch(user_ptr->borrow_history, bkname_input);
                // result_search = LibraryBookNameSearch(lib, bkname_input);
                break;

            default:
                break;
        }
        if (result_search.size() != 0) {
            BorrowerNodePTR brrwr_nxt_ptr = nullptr;

        } else{
            std::cout << "该用户下无该书处于借阅/逾期状态！";
            return;
        }

    } else{

        std::cout << "不存在该用户！";
        return;
    }

}