/**
 * @file struct.h
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief Booknode + giveback_date
 *        修改 链表结构 为 vector
 *        JSON 模块有问题
 * @version 0.6
 * @date 2023-1-3
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
    Time lend_date;                          // 借书时间
}BorrowerNode;

// 图书结构体
typedef struct Book{
    std::string name;               // 名称
    std::string classifier;    // 中图分类号
    std::vector<AuthorInfo> authors_info_list;   // 作、译者表数组
    PublishInfo publish_info;       // 出版信息
    std::string identification;     // 唯一识别码
    int lend_state_flag = 2;          // 出借状态（-3：图书废弃；-2：图书逾期；-1：图书借出；0: 图书在馆；1：图书在途；2：无图书）
    std::vector<BorrowerNode> lend_history;       // 借出历史

    Book() = default;

// 重定义运算符 <<， 用于直接输出图书信息。用法 cout << bk
// TODO: 修正 vector 下的 JSON 输出
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
    void writeAsJSON(nlohmann::json &bookJson) const
    {

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

    }
    void readFromJSON(const nlohmann::json& bookJson)
    {
        // Fill Book structure from JSON
        try
        {
            name = bookJson["name"];
            classifier = bookJson["classifier"];

            // Authors Info List
            authors_info_list.clear();
            for (const auto& authorInfoJson : bookJson["authors_info_list"])
            {
                AuthorInfo authorInfo;
                authorInfo.name = authorInfoJson["name"];
                authorInfo.gender = (authorInfoJson["gender"] == "女");
                authorInfo.nationality = authorInfoJson["nationality"];
                authorInfo.isTranslator = authorInfoJson["isTranslator"];
                authors_info_list.push_back(authorInfo);
            }

            // Publish Info
            publish_info.press = bookJson["publish_info"]["press"];
            publish_info.date.YY = bookJson["publish_info"]["date"]["YY"];
            publish_info.date.MM = bookJson["publish_info"]["date"]["MM"];
            publish_info.date.DD = bookJson["publish_info"]["date"]["DD"];
            publish_info.price = bookJson["publish_info"]["price"];

            // Other fields
            identification = bookJson["identification"];
            lend_state_flag = bookJson["lend_state_flag"];
            lend_history.lend_times = bookJson["lend_history"]["lend_times"];
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error reading data from JSON: " << e.what() << std::endl;
            return;
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

    void readFromJSONFile(const std::string& filePath)
    {
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return;
        }

        nlohmann::json libraryJson;
        try
        {
            file >> libraryJson;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error parsing JSON: " << e.what() << std::endl;
            file.close();
            return;
        }

        // Fill Library structure from JSON
        try
        {
            book_amount = libraryJson["book_amount"];
            const nlohmann::json& bookListJson = libraryJson["book_list"];

            for (int i = 0; i < book_amount; ++i)
            {
                book_list[i].readFromJSON(bookListJson[i]);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error reading data from JSON: " << e.what() << std::endl;
            file.close();
            return;
        }

        file.close();
    }

    void writeToJSONFile(const std::string& filePath) const
    {
        nlohmann::json libraryJson;
        libraryJson["book_amount"] = book_amount;

        nlohmann::json bookListJson;
        for (int i = 1; i <= book_amount; ++i)
        {
            nlohmann::json bookJson;
            book_list[i].writeAsJSON(bookJson);
            bookListJson.push_back(bookJson);
        }

        libraryJson["book_list"] = bookListJson;

        // Write JSON to file
        std::ofstream file(filePath);
        if (file.is_open())
        {
            file << libraryJson.dump(4); // Indentation level: 4 spaces
            file.close();
        }
        else
        {
            std::cerr << "Error opening file for writing: " << filePath << std::endl;
        }
    }


    /* 应使用数组建立，空0位使用自然排序（1，2，3...）
    */
};

/*-----------------------------------------------------------------------------*/
// 借书链表节点
typedef struct BookNode{
    std::string book_ID;            // 图书唯一识别码
    Time borrow_date;               // 借书时间
    Time giveback_date;             // 换书时间
    int borrow_state_flag;        // 借书状态（-2：借书逾期；-1：借书正常；0：已归还；1：归还未缴逾期罚款）
}BookNode;

// 借书历史
typedef struct{
    int borrowed_books_acc;                 // 累计借书量
    int borrowed_books_cur;                 // 当前借书量
    std::vector<BookNode> book_list;        // 借书表
}BorrowHistory;

// 借书者结构体
typedef struct Borrower{
    std::string ID;                      // 借书者ID
    unsigned int gender;               // 性别
    unsigned int permission_flag;      // 借书权限（0：允许借书；1：不允许借书）

    BorrowHistory borrow_history;        // 借阅历史
}Borrower; // 使用链表建立借书者群

// 借书者群（权限组）
typedef struct{
    int borrower_amount;                 // 借书者总量
    std::vector<Borrower> borrower_list; // 借书者名单（使用自然排序，1，2，3...）
    // TODO: 链表建立借书者群
}BorrowerGroup;

#endif
