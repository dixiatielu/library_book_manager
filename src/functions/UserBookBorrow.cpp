//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"
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
                std::cout << "请输入ISBN：";
                std::cin >> bkISBN_input;
                result_position = LibraryBookISBNSearch(lib, bkISBN_input);
                break;

            case 2:
                std::cout << "请输入书名：";
                std::cin >> bkname_input;
                result_position = LibraryBookNameSearch(lib, bkname_input);
                break;

            default:
                break;
        }
        if (!result_position.empty()) {
            std::cout << "查询到以下符合条件的图书：" << std::endl;
            for(int i = 0; i <= result_position.size() - 1; i++) {
                std::cout << "序号" << i << ". " << std::endl;
                std::cout << lib.book_list[result_position[i]] << std::endl << "--------------------------\n";
            }
            int bk_position;
            do {
                std::cout << "请输入您要借阅的图书序号：";
                std::cin >> bk_position;
                if (bk_position > result_position.size() - 1) {
                    std::cout << "输入序号超出范围！";
                    continue;
                } else{
                    break;
                }
            }while(true);

             // 历史查询，不能同时借两本相同ISBN/name的书

                if ((lib.book_list[result_position[bk_position]].lend_state_flag == -1)
                    ||(lib.book_list[result_position[bk_position]].lend_state_flag == -2)) {

                    for (int j = 0; j <= lib.book_list[result_position[bk_position]].lend_history.size() - 1; j++){

                        if (lib.book_list[result_position[bk_position]].lend_history[j].borrower_ID == user_identification) {

                            std::cout << "该用户下有相同图书处于借出/逾期状态";
                            return;

                        } else{
                            continue;
                        }
                    }
                }

                if (lib.book_list[result_position[bk_position]].lend_state_flag == 0) {
                    lib.book_list[result_position[bk_position]].lend_state_flag = -1;

                    UpdateUserBorrowHistory(gp.borrower_list[user_position].borrow_history,
                                            lib.book_list[result_position[bk_position]].identification);
                    BookLendHistory_UpdateBorrow(lib.book_list[result_position[bk_position]].lend_history
                            , user_identification);
                    std::cout << "借书成功";
                    return;
                    // 若存在该书，则此处函数结束
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