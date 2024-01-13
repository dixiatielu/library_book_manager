//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

void LibraryBook_Update_Copy_Delete_Director(Library &lib, std::vector<int> bk_position) {
    time_t id;
//    time(&id); // 使用时间戳作为书本唯一识别码

    int mode_flag;
    std::cout << "请选择操作\n"
                 "\t1. 修改某一副本\n"
                 "\t2. 修改所有副本\n"
                 "\t3. 删除某一副本\n"
                 "\t4. 删除所有副本\n"
                 "\t5. 添加一本副本\n"
                 "\t6. 查看副本唯一识别码\n"
                 "\t输入其他任意字符以退出\n"
                 "$?-";
    std::cin >> mode_flag;
    std::cin.ignore(500, '\n');                        // 清空输入缓冲区

    if (!std::cin) {
        std::cout << "输入非数字！\n"
                     "将退出图书信息录入与更新程序\n";
        std::cin.clear();
        mode_flag = -1;
    }

    int bkpos_numero_selected = 0;

    int tmp_lend_state_flag = 0;
    std::string tmp_identification;
    std::vector<BorrowerNode> tmp_lend_history;
    switch (mode_flag) {
        case 1:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n", i + 1, lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请输入要修改副本对应的唯一识别码序号：";
            std::cin >> bkpos_numero_selected;
            std::cin.ignore(500, '\n');                        // 清空输入缓冲区

            if (!std::cin) {

                std::cout << "输入非数字！\n"
                             "将退出图书信息录入与更新程序\n";
                std::cin.clear();
                return; // 函数出口

            } else if ((bkpos_numero_selected < 0) || (bkpos_numero_selected > bk_position.size() - 1)) {

                std::cout << "序号不在范围内！\n"
                             "将退出图书信息录入与更新程序\n";
                std::cin.clear();
                return; // 函数出口
            }

            LibraryBook_Update(lib.book_list[bk_position[bkpos_numero_selected - 1]]);

            std::cout << "\n该副本修改完成！\n";
            break;

        case 2:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n", i + 1, lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请修改样本\n";
            LibraryBook_Update(lib.book_list[bk_position[0]]);
            for (int i = 1; i <= bk_position.size() - 1; i++) {
                tmp_lend_state_flag = lib.book_list[bk_position[i]].lend_state_flag;
                tmp_identification = lib.book_list[bk_position[i]].identification;
                tmp_lend_history = lib.book_list[bk_position[i]].lend_history;
                LibraryBook_Copy(lib.book_list[bk_position[i]], lib.book_list[bk_position[0]]);

                lib.book_list[bk_position[i]].lend_state_flag = tmp_lend_state_flag;
                lib.book_list[bk_position[i]].identification = tmp_identification;
                lib.book_list[bk_position[i]].lend_history = tmp_lend_history;
            }
            std::cout << "\n所有副本修改完成！\n";
            break;

        case 3:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n", i + 1, lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n请输入要修改副本对应的唯一识别码序号：";
            std::cin >> bkpos_numero_selected;
            LibraryBook_Delete_fast(lib, bk_position[bkpos_numero_selected - 1]);
            std::cout << "\n该副本删除成功！\n";
            break;

        case 4:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n", i + 1, lib.book_list[bk_position[i]].identification);
            }

            for (int i = 0; i <= bk_position.size() - 1; i++) {

                LibraryBook_Delete_fast(lib, bk_position[i]);
            }

            std::cout << "\n所有副本删除成功！\n";
            break;

        case 5:
            LibraryBook_Copy(lib.book_list[lib.book_amount_total + 1], lib.book_list[bk_position[0]]);
            time(&id); // 使用时间戳作为书本唯一识别码
            lib.book_list[lib.book_amount_total + 1].identification = std::to_string(id);
            lib.book_amount_total++;
            lib.book_amount_real++;

            std::cout << "\n新副本添加成功！\n";
            break;

        case 6:
            std::cout << "\n各副本唯一识别码如下\n";
            for (int i = 0; i <= bk_position.size() - 1; i++) {

                std::cout << fmt::format("\t{}. {}\n", i + 1, lib.book_list[bk_position[i]].identification);
            }

            std::cout << "\n所有副本唯一识别码输出成功！\n";
            break;

        default:
            break;
    }
}