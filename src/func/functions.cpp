#include <utility>
#include "../include/main.h"


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

std::vector<int> LibraryBookNameSearch(Library lib, const std::string& bk_name)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].name == bk_name) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    return bk_position;
}

std::vector<int> LibraryBookISBNSearch(Library lib, const std::string& bk_ISBN)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].publish_info.ISBN == bk_ISBN) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
        } else{
            continue;
        }
    }
    return bk_position;
}

std::vector<int> LibraryBookIDSearch(Library lib, const std::string& bk_ID)
{
    std::vector<int> bk_position;
    for (int i = 1; i <= lib.book_amount; i++)
    {
        if ((lib.book_list[i].identification == bk_ID) && (lib.book_list[i].lend_state_flag != -3)) {
            bk_position.emplace_back(i);
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
        } else if (books_deleted_position.empty()) {
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
    bk = std::move(bk_sample);
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
                 "\t输入其他任意字符以退出\n"
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

        default:// 程序出口
            return;
    }

    if (result_search.empty()) {
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
            lib.book_amount++;
            LibraryBook_Append(lib.book_list[lib.book_amount], bkname_input, bkISBN_input);
        }
    } else{
        std::cout << "图书馆中有相同书\n";
        LibraryBook_Update_Copy_Delete_Director(lib, result_search);
    }
}

int LibraryBook_Append(Book &bk, const std::string& bk_name, const std::string& bk_ISBN)
{
    time_t id;
//    time(&id); // 使用时间戳作为书本唯一识别码

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
    bk.publish_info.date = GetTimeInput();

    std::cout << "请输入价格\n$?-";
    std::cin >> bk.publish_info.price;

    bk.lend_state_flag = 0;
    bk.lend_history = {};
    time(&id); // 使用时间戳作为书本唯一识别码
    bk.identification = std::to_string(id);

    return 0;
}

/*-----------------------------------------------------------------------------*/

void LibraryBook_Update_Copy_Delete_Director(Library &lib, std::vector<int> bk_position)
{
    time_t id;
//    time(&id); // 使用时间戳作为书本唯一识别码

    int mode_flag;
    std::cout << "请选择操作\n"
                 "\t1. 修改某一副本\n"
                 "\t2. 修改所有副本\n"
                 "\t3. 删除某一副本\n"
                 "\t4. 删除所有副本\n"
                 "\t5. 添加一本副本\n"
                 "\t输入其他任意字符以退出\n"
                 "$?-";
    std::cin >> mode_flag;

    int bkpos_numero_selected;
    int         tmp_lend_state_flag;
    std::string tmp_identification;
    switch (mode_flag) {
        case 1:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n"
                                         ,i+1 , lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请输入要修改副本对应的唯一识别码序号：";
            std::cin >> bkpos_numero_selected;
            LibraryBook_Update(lib.book_list[bk_position[bkpos_numero_selected - 1]]);
            break;

        case 2:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n"
                        ,i+1 , lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请修改样本\n";
            LibraryBook_Update(lib.book_list[bk_position[0]]);
            for (int i = 1; i <= bk_position.size() - 1; i++) {
                tmp_lend_state_flag = lib.book_list[bk_position[i]].lend_state_flag;
                tmp_identification  = lib.book_list[bk_position[i]].identification;
                LibraryBook_Copy(lib.book_list[bk_position[i]], lib.book_list[bk_position[0]]);

                lib.book_list[bk_position[i]].lend_state_flag = tmp_lend_state_flag;
                lib.book_list[bk_position[i]].identification  = tmp_identification;
            }
            std::cout << "\n所有副本修改完成\n";
            break;

        case 3:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n"
                        ,i+1 , lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请输入要修改副本对应的唯一识别码序号：";
            std::cin >> bkpos_numero_selected;
            LibraryBook_Delete_fast(lib, bk_position[bkpos_numero_selected - 1]);
            std::cout << "\n删除成功\n";
            break;
        case 4:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n"
                        ,i+1 , lib.book_list[bk_position[i]].identification);
            }

            for (int i = 0; i <= bk_position.size() - 1; i++){

                LibraryBook_Delete_fast(lib, bk_position[i]);
            }
            std::cout << "\n删除成功\n";
            break;
        case 5:
            LibraryBook_Copy(lib.book_list[lib.book_amount]
                             , lib.book_list[bk_position[0]]);

            time(&id); // 使用时间戳作为书本唯一识别码
            lib.book_list[lib.book_amount].identification = std::to_string(id);
            break;
        default:
            return;
    }
}

/*-----------------------------------------------------------------------------*/

int UserID_Exist(BorrowerGroup gp, const std::string& id)
{
    for (int i = 1; i <= gp.borrower_amount; i++) {
        if (gp.borrower_list[i].ID == id) {
            return 1;
        } else{
            continue;
        }
    }
    return 0;
}


int UserValidation_Search_Borrow(BorrowerGroup gp, const std::string& id)
{
    for (int i = 1; i <= gp.borrower_amount; i++) {
        if ((gp.borrower_list[i].ID == id)
            &&(gp.borrower_list[i].permission_flag == 0)) {
            return i;
        } else{
            continue;
        }
    }
    return 0;
}

int UserValidation_Search_Giveback(BorrowerGroup gp, const std::string& id)
{
    for (int i = 1; i <= gp.borrower_amount; i++) {
        if ((gp.borrower_list[i].ID == id)) {
            return i;
        } else{
            continue;
        }
    }
    return 0;
}

/*-----------------------------------------------------------------------------*/

int UserBrrwHistory_UpdateBorrow(BorrowHistory &brrw_history, std::string bk_ID)
{
    BookNode  brrw_bk_node = {
            .book_ID           = std::move(bk_ID),
            .borrow_date       = GetCurrentTime(),
            .giveback_date     = {},
            .borrow_state_flag = -1
    };

    brrw_history.borrowed_books_cur++;
    brrw_history.borrowed_books_acc++;
    brrw_history.book_list.emplace_back(brrw_bk_node);
    return 0;
}

int BookLendHistory_UpdateBorrow(std::vector<BorrowerNode> &ld_history, std::string brrwr_ID)
{
    BorrowerNode brrwr_node = {
            .borrower_ID = std::move(brrwr_ID),
            .lend_date = GetCurrentTime()
    };

    ld_history.emplace_back(brrwr_node);
    return 0;
}

/*-----------------------------------------------------------------------------*/

void UserBookBorrow(BorrowerGroup &gp, Library &lib)
{
    int user_position;

    std::string user_identification;
    std::cout << "请输入您的ID：";
    std::cin >> user_identification;
    user_position = UserValidation_Search_Borrow(gp, user_identification);

    if (user_position != 0) {
        std::string bkISBN_input, bkname_input;
        std::vector<int> result_position;

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
                result_position = LibraryBookISBNSearch(lib, bkISBN_input);
                break;

            case 2:
                std::cout << "请输入书名";
                std::cin >> bkname_input;
                result_position = LibraryBookNameSearch(lib, bkname_input);
                break;

            default:
                break;
        }
        if (!result_position.empty()) {

            for (int i = 0; i <= result_position.size() - 1; i++) { // 历史查询，不能同时借两本相同ISBN/name的书

                if ((lib.book_list[result_position[i]].lend_state_flag == -1)
                    ||(lib.book_list[result_position[i]].lend_state_flag == -2)) {

                    for (int j = 0; j <= lib.book_list[result_position[i]].lend_history.size() - 1; j++){

                        if (lib.book_list[result_position[i]].lend_history[j].borrower_ID == user_identification) {

                            std::cout << "该用户下有相同图书处于借出/逾期状态";
                            return;

                        } else{
                            continue;
                        }
                    }
                }
            }

            for (int i = 0; i <= result_position.size() - 1; i++) {
                if (lib.book_list[result_position[i]].lend_state_flag == 0) {
                    lib.book_list[result_position[i]].lend_state_flag = -1;

                    UserBrrwHistory_UpdateBorrow(gp.borrower_list[user_position].borrow_history,
                                                 lib.book_list[result_position[i]].identification);
                    BookLendHistory_UpdateBorrow(lib.book_list[result_position[i]].lend_history
                                                 , user_identification);
                    // user_ptr->borrow_history.borrowed_books_acc++;
                    // user_ptr->borrow_history.borrowed_books_cur++;
                    // 并入 UB_A 函数
                    std::cout << "借书成功";
                    return;
                    // 若存在该书，则此处函数结束
                }
            }

            std::cout << "该书均已借出！";
            return;

        } else{
            std::cout << "图书馆无该藏书！";
            return;
        }

    } else if (!UserID_Exist(gp, user_identification)) {
        std::cout << "不存在该用户！";
        return;
    } else{
        std::cout << "该用户无借书权限！";
        return;
    }
}

/*-----------------------------------------------------------------------------*/

std::vector<int> User_BorrowedBook_NameSearch(Library lib, BorrowHistory brrw_history, const std::string& bk_name)
{
    std::string tmp_bkID;
    std::vector<int> tmp_bk_position;
    std::vector<int> rt_bk_position;
    for (int i = 0; i <= brrw_history.book_list.size() - 1; i++) {
        if ((brrw_history.book_list[i].borrow_state_flag == -1)
            ||(brrw_history.book_list[i].borrow_state_flag == -2)) {

            tmp_bkID = brrw_history.book_list[i].book_ID;
            tmp_bk_position = LibraryBookIDSearch(lib, tmp_bkID);

            if (lib.book_list[tmp_bk_position.front()].name == bk_name) {

                rt_bk_position.emplace_back(i);
                return rt_bk_position; // 函数出口，因为已限制用户相同图书只能借一本

            } else{
                continue;
            }

        } else{
            continue;
        }
    }
    return rt_bk_position;
}

std::vector<int> User_BorrowedBook_ISBNSearch(Library lib, BorrowHistory brrw_history, const std::string& bk_ISBN)
{
    std::string tmp_bkID;
    std::vector<int> tmp_bk_position;
    std::vector<int> rt_bk_position;
    for (int i = 0; i <= brrw_history.book_list.size() - 1; i++) {
        if ((brrw_history.book_list[i].borrow_state_flag == -1)
            ||(brrw_history.book_list[i].borrow_state_flag == -2)) {

            tmp_bkID = brrw_history.book_list[i].book_ID;
            tmp_bk_position = LibraryBookIDSearch(lib, tmp_bkID);

            if (lib.book_list[tmp_bk_position.front()].publish_info.ISBN == bk_ISBN) {

                rt_bk_position.emplace_back(i);
                return rt_bk_position; // 函数出口，因为已限制用户相同图书只能借一本

            } else{
                continue;
            }

        } else{
            continue;
        }
    }
    return rt_bk_position;
}

/*-----------------------------------------------------------------------------*/

int UserBookHistory_UpdateGiveback(BorrowHistory &brrw_history, int giveback_brrwedbook_numero)
{
    brrw_history.borrowed_books_cur--;
    brrw_history.book_list[giveback_brrwedbook_numero].borrow_state_flag = 0; // TODO: 若要考虑罚款问题，可赋值为1
    brrw_history.book_list[giveback_brrwedbook_numero].giveback_date = GetCurrentTime();
    return 0;
}

int BookLendState_UpdateGiveback(Library &lib, const std::string& giveback_bkID)
{
    std::vector<int> result_position = LibraryBookIDSearch(lib, giveback_bkID);
    lib.book_list[result_position.front()].lend_state_flag = 0; // TODO: 若要考虑运输时间，可赋值为1
    return 0;
}

/*-----------------------------------------------------------------------------*/

void UserBookGiveback(BorrowerGroup &gp, Library &lib)
{
    std::string user_identification;
    std::cout << "请输入您的ID：";
    std::cin >> user_identification;
    int user_position = UserValidation_Search_Giveback(gp, user_identification);

    if (user_position != 0) {
        std::string bkISBN_input, bkname_input;
        std::vector<int> result_position;

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
                result_position = User_BorrowedBook_ISBNSearch(lib,
                                                               gp.borrower_list[user_position].borrow_history,
                                                               bkISBN_input);
                // result_position = LibraryBookISBNSearch(lib, bkISBN_input);
                break;

            case 2:
                std::cout << "请输入书名";
                std::cin >> bkname_input;
                result_position = User_BorrowedBook_NameSearch(lib,
                                                               gp.borrower_list[user_position].borrow_history,
                                                               bkname_input);
                // result_position = LibraryBookNameSearch(lib, bkname_input);
                break;

            default:
                break;
        }
        if (!result_position.empty()) { // TODO: 可添加罚款功能
            UserBookHistory_UpdateGiveback(gp.borrower_list[user_position].borrow_history
                                           , result_position.front());
            BookLendState_UpdateGiveback(lib,
                                         gp.borrower_list[user_position].borrow_history.book_list[result_position.front()].book_ID);

        } else{
            std::cout << "该用户下无该书处于借阅/逾期状态！";
            return;
        }

    } else{

        std::cout << "不存在该用户！";
        return;
    }

}

int LibraryBook_Update(Book &bk) {
    return 0;
}

Library InitializeLibrary() {
    return Library(0);
}
