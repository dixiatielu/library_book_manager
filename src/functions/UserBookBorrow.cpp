//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../include/function_definitions.h"
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