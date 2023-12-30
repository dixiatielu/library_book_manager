/**
 * @file struct.h
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief 1. 中图分类号由 char(*)[4] classify_letter
 *                    改为 std::string classifier
 * @version 0.2
 * @date 2023-12-29
 *
 * @copyright Copyright (c) 2023
 *
**/

#ifndef MY_STRUCT

// 时间结构体
typedef struct{
    std::string YY, MM, DD;
}Time;

/*-----------------------------------------------------------------------------*/


// 作者信息
typedef struct{
    std::string name;
    char nation[3] = {0};     // 使用ISO3166-1 alpha-2两字符代码标注国籍
    unsigned int gender:1;
    unsigned int isTranslator:1;
}AuthorInfo, *AuthorList;

// 出版信息
typedef struct{
    std::string press;              // 出版社
    Time date;                      // 出版日期
    float price = 0;                // 价格
}PublishInfo;

// 图书编号
typedef struct{
    std::string ISBN;               // ISBN号（eg：9787020024759）
    int copy;                       // 副本号
    Time store_date;                // 藏书日期
}BookID;


// 借书者链表节点
typedef struct BorrowerNode{
    std::string borrower_ID;                 // 借书者ID
    Time lend_date;                       // 借书时间

    BorrowerNode* next_ptr = nullptr;
}BorrowerNode, *BorrowerNodePTR;

// 借出历史
typedef struct{
    int lend_times;                   // 借出次数
    BorrowerNodePTR borrower_list_hPTR;   // 借书者链表头指针
}LendHistory;


// 图书结构体
typedef struct{
    std::string name;               // 名称
    std::string classifier;         // 中图分类号
    AuthorList authors_info_list;   // 作、译者表数组
    PublishInfo publish_info;       // 出版信息
    BookID identification;          // 编号
                                        /* 待解决
                                            副本问题
                                        */
    int lend_state_flag:3;          // 出借状态（-2：图书逾期；-1：图书借出；0: 图书在馆；1：图书在途）
    LendHistory lend_history;       // 借出历史
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
    BookID book_ID;                 // 图书编号
    Time borrow_date;               // 借书时间
    int borrow_state_flag:3;        // 借书状态（-2：借书逾期；-1：借书正常；0：已归还；1：归还未缴逾期罚款）

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
    unsigned int gender:1;               // 性别
    unsigned int permission_flag:1;      // 借书权限（0：允许借书；1：不允许借书）

    BorrowHistory borrow_history;        // 借阅历史
}Borrower, *BorrowerList; // 使用链表建立借书者群

typedef struct{
    int borrower_amount;                 // 借书者总量
    BorrowerList borrower_list;          // 借书者名单
                                             /* 应使用链表建立
                                             */
}Group;

#endif