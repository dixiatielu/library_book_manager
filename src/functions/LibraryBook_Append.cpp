//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"

int LibraryBook_Append(Book &bk, const std::string& bk_name, const std::string& bk_ISBN)
{
    time_t id;
//    time(&id); // 使用时间戳作为书本唯一识别码

    /*-----------------------------------------------------------------------------*/

    if (!bk_name.empty()) {
        bk.name = bk_name;
        std::cout << "书名已输入\n";
    }
    else {
        std::cout << "请输入书名\n$?-";
        std::cin >> bk.name;
    }
    std::cout << "请输入中图分类号\n$?-";
    std::cin >> bk.classifier;

    /*-----------------------------------------------------------------------------*/

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

    /*-----------------------------------------------------------------------------*/

    std::cout << "\n下面输入出版信息\n";
    system("timeout 1");

    if(!bk_ISBN.empty())
    {
        bk.publish_info.ISBN = bk_ISBN;
        std::cout << "ISBN号已输入\n";
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

    /*-----------------------------------------------------------------------------*/

    bk.lend_state_flag = 0;
    bk.lend_history = {};
    time(&id); // 使用时间戳作为书本唯一识别码
    bk.identification = std::to_string(id);


    std::cout << "\n已完成图书信息录入！\n\n";

    return 0;
}