/**
 * @file struct.h
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief 1. 删除了BookID, ISBN信息并入Publish_Info结构体
 *        2. 增加的书本唯一识别码 （std::string identification）
 *        3. 对 Book 结构体重载运算符，现在可以直接通过 std::cout 输出Book类型变量
 * @version 0.4
 * @date 2023-1-2
 *
 * @copyright Copyright (c) 2023
 *
**/
#ifndef MY_STRUCT
#define MY_STRUCT
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
                                        /* 待解决
                                            副本问题
                                        */
    int lend_state_flag;          // 出借状态（-2：图书逾期；-1：图书借出；0: 图书在馆；1：图书在途）
    LendHistory lend_history;       // 借出历史

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
}Book, *BookList, *BookPTR;


// 图书馆结构体
typedef struct{
    int book_amount;               // 图书馆藏书量
    BookList book_list;            // 图书馆书单
                                        /* 应使用数组建立，空0位使用自然排序（1，2，3...）
                                        */
}Library;

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
    BookNodePTR book_list_hPTR;             // 借书链表头指针
}BorrowHistory;

// 借书者结构体
typedef struct{
    std::string ID;                      // 借书者ID
    unsigned int gender;               // 性别
    unsigned int permission_flag;      // 借书权限（0：允许借书；1：不允许借书）

    BorrowHistory borrow_history;        // 借阅历史
}Borrower, *BorrowerList; // 使用链表建立借书者群

typedef struct{
    int borrower_amount;                 // 借书者总量
    BorrowerList borrower_list;          // 借书者名单
                                             /* 应使用链表建立
                                             */
}Group;

#endif