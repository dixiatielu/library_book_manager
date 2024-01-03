//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"
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