/**
 * @file struct.h
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief
 * @version 0.5
 * @date 2023-1-2
 *
 * @copyright Copyright (c) 2023
 *
**/
#ifndef MY_STRUCT
#define MY_STRUCT

#include <vector>
#include <fstream>
#include "fmt/core.h"
#include "nlohmann/json.hpp"
#include "macro.h"

// 时间结构体
typedef struct{
    std::string YY, MM, DD; // 取 10000 为无效值
}Time;

/*-----------------------------------------------------------------------------*/


// 作者信息
typedef struct{
    std::string name;
    std::string nationality;     // 使用ISO3166-1 alpha-2两字符代码标注国籍
    unsigned int gender;       // 0 为男性，1 为女性
    unsigned int isTranslator; // 0 表示为非译者，1 表示为译者
}AuthorInfo;

// 出版信息
typedef struct{
    std::string ISBN;               // ISBN号（eg：9787020024759）
    std::string press;              // 出版社
    Time date;                      // 出版日期
    float price = 0;                // 价格
}PublishInfo;


// 借书者链表节点
typedef struct BorrowerNode{
    std::string borrower_ID;                 // 借书者ID
    Time lend_date;                       // 借书时间

    BorrowerNode* next_ptr = nullptr;
}BorrowerNode, *BorrowerNodePTR;

// 借出历史
typedef struct{
    int lend_times;                   // 借出次数
    BorrowerNodePTR borrower_list_hPTR = nullptr;   // 借书者链表头指针
}LendHistory;


// 图书结构体
typedef struct Book{
    std::string name;               // 名称
    std::string classifier;    // 中图分类号
    std::vector<AuthorInfo> authors_info_list;   // 作、译者表数组
    PublishInfo publish_info;       // 出版信息
    std::string identification;     // 唯一识别码
    int lend_state_flag = 2;          // 出借状态（-3：图书废弃；-2：图书逾期；-1：图书借出；0: 图书在馆；1：图书在途；2：无图书）
    LendHistory lend_history;       // 借出历史

    Book() = default;

// 重定义运算符 <<， 用于直接输出图书信息。用法 cout << bk
    friend std::ostream &operator << (std::ostream &o_s, Book &bk)
    {
        o_s << fmt::format("书名          ：{:<30}\n"
                           "中图分类号    ：{:<10}\n"
                           "作/译者（{:^1}人）：\n", bk.name, bk.classifier, bk.authors_info_list.size());

        int author_total_calc     = 1;
        int translator_total_calc = 1;
        for (int i = 0; i <= bk.authors_info_list.size()-1; i++) {
            o_s << fmt::format("\t{:->6}{:-<3}:\n"
                               "\t\t姓名：{}\n"
                               "\t\t性别：{}\n"
                               "\t\t国籍：{}\n", bk.authors_info_list[i].isTranslator
                                                ? "译者" : "作者"
                                              , bk.authors_info_list[i].isTranslator
                                                ? translator_total_calc : author_total_calc
                                              , bk.authors_info_list[i].name
                                              , bk.authors_info_list[i].gender ? "女" : "男"
                                              , bk.authors_info_list[i].nationality);
            bk.authors_info_list[i].isTranslator ? translator_total_calc++ : author_total_calc++;
        }

        o_s << fmt::format("出版社  ：{}\n"
                           "出版日期：{}/{}/{}\n"
                           "价格    ：{:<.2f}\n", bk.publish_info.press
                                          , bk.publish_info.date.YY
                                          , bk.publish_info.date.MM == (std::string)"0" ? "N.A." : bk.publish_info.date.MM
                                          , bk.publish_info.date.DD == (std::string)"0" ? "N.A." : bk.publish_info.date.DD
                                          , bk.publish_info.price);

        o_s << fmt::format("图书唯一识别码：{}\n", bk.identification);
        o_s << fmt::format("图书借阅状态  ：{}\n", bk.lend_state_flag);
        o_s << fmt::format("借阅次数      ：{}\n", bk.lend_history.lend_times);
        return o_s;
    }

    void writeAsJSON(std::ostream& o_s, const std::string& filePath) const
    {
        nlohmann::json bookJson;

        bookJson["name"] = name;
        bookJson["classifier"] = classifier;

        // Authors Info List
        nlohmann::json authorsInfoListJson;
        for (const auto& authorInfo : authors_info_list)
        {
            nlohmann::json authorInfoJson;
            authorInfoJson["name"] = authorInfo.name;
            authorInfoJson["gender"] = authorInfo.gender;
            authorInfoJson["nationality"] = authorInfo.nationality;
            authorInfoJson["isTranslator"] = authorInfo.isTranslator;
            authorsInfoListJson.push_back(authorInfoJson);
        }
        bookJson["authors_info_list"] = authorsInfoListJson;

        // Publish Info
        nlohmann::json publishInfoJson;
        publishInfoJson["press"] = publish_info.press;
        publishInfoJson["date"]["YY"] = publish_info.date.YY;
        publishInfoJson["date"]["MM"] = publish_info.date.MM;
        publishInfoJson["date"]["DD"] = publish_info.date.DD;
        publishInfoJson["price"] = publish_info.price;
        bookJson["publish_info"] = publishInfoJson;

        // Other fields
        bookJson["identification"] = identification;
        bookJson["lend_state_flag"] = lend_state_flag;
        bookJson["lend_history"]["lend_times"] = lend_history.lend_times;

        // Write JSON to ostream
        o_s << bookJson.dump(4); // 缩进等级: 4 空格

        // Optionally, write JSON to file
        if (!filePath.empty())
        {
            std::ofstream file(filePath);
            file << bookJson.dump(4);
            file.close();
        }
    }

}Book, *BookList, *BookPTR;


// 图书馆结构体
struct Library{
    int book_amount;               // 图书馆藏书量
    BookList book_list;            // 图书馆书单
    // 构造函数
    explicit Library(const int& BookAmount)
    {
        book_amount = BookAmount;
        book_list = new Book[BOOK_MAX_NUM + 1];
    }
                                        /* 应使用数组建立，空0位使用自然排序（1，2，3...）
                                        */
};

/*-----------------------------------------------------------------------------*/
// 借书链表节点
typedef struct BookNode{
    std::string book_ID;            // 图书唯一识别码
    Time borrow_date;               // 借书时间
    int borrow_state_flag;        // 借书状态（-2：借书逾期；-1：借书正常；0：已归还；1：归还未缴逾期罚款）

    BookNode* next_ptr = nullptr;
}BookNode, *BookNodePTR;

// 借书历史
typedef struct{
    int borrowed_books_acc;                 // 累计借书量
    int borrowed_books_cur;                 // 当前借书量
    BookNodePTR book_list_hPTR = nullptr;             // 借书链表头指针
}BorrowHistory;

// 借书者结构体
typedef struct Borrower{
    std::string ID;                      // 借书者ID
    unsigned int gender;               // 性别
    unsigned int permission_flag;      // 借书权限（0：允许借书；1：不允许借书）

    BorrowHistory borrow_history;        // 借阅历史
    Borrower* next_borrower;
}Borrower, *BorrowerList; // 使用链表建立借书者群

// 借书者群（权限组）
typedef struct{
    int borrower_amount;                 // 借书者总量
    BorrowerList borrower_list = nullptr;          // 借书者名单
    // TODO: 链表建立借书者群
}BorrowerGroup;

#endif
