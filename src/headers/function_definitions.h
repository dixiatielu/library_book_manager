/**
 * @file main.h
 * @author ChengPu (chengpu@stu.scu.edu.cn)
 * @brief
 * @version 0.4
 * @date 2024-01-02
 *
 * @copyright Copyright (c) 2024
 *
**/
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

#include "../include/fmt.h"
#include "struct.h"
#include "../include/macro.h"

/**
 * @brief Get the Time Current object
 *        获取当前时间并返回Time结构体
 * @return Time
**/
Time GetCurrentTime();

/**
 * @brief Get the Time Input object
 *        在函数中获取用户输入的年、月、日时间并返回Time结构体
 * @return Time
**/
Time GetTimeInput();

/**
 * @brief 按唯一识别码查找图书（先查找ISBN，再查找副本号）
 *
 * @param lib
 * @param id
 * @return int 返回书单中的自然位置（1，2，3...）
 *             失败返回长度为0的vector
**/
std::vector<int> LibraryBookIDSearch(Library lib, const std::string &id);

/**
 * @brief 按名称查找图书，并以vector返回书单中所有满足条件的图书的自然位置
 *
 * @param lib
 * @param bk_name
 * @return vector 返回书单中的自然位置（1，2，3...）
 *                失败返回长度为0的vector
**/
std::vector<int> LibraryBookNameSearch(Library lib, const std::string &bk_name);

/**
 * @brief 按ISBN查找图书，并以vector返回书单中所有满足条件的图书的自然位置
 *
 * @param lib
 * @param ISBN
 * @return vector 返回书单中的自然位置（1，2，3...）
 *                失败返回长度为0的vector
**/
std::vector<int> LibraryBookISBNSearch(Library lib, const std::string &ISBN);

/*-----------------------------------------------------------------------------*/

void LibraryBook_Delete_fast(Library &lib, int bk_position);

int Library_DeletedBooks_sort(Library &lib);

/*-----------------------------------------------------------------------------*/


/**old
 * @brief 录入和修改图书
 *        可增强修改部分的方便性
 *        注意：
 *        没有 book_sample 参数时，copy 置 1；否则不做修改
 *        不修改藏书日期
 * @param book_ptr
 * @param book_sample
 * @return int
**/
int LibraryBook_Append(Book &bk, const std::string &bk_name, const std::string &bk_ISBN);

/**
 * @brief 添加图书副本
 *        将 book_sample 复制到 book_ptr 所指的位置
 * @param book_ptr
 * @param book_sample
 * @return int
**/
int LibraryBook_Copy(Book &bk, Book book_sample);

int LibraryBook_Update(Book &bk);


/**
 * @brief 图书录入与修改、删除向导                                  // 未考虑藏书日期，可默认从 GetCurrentTime 返回值赋值
 *        要求用户输入书名或ISBN
 *        1. 当书单中不存在该书时，询问是否要录入该书，若是则在图书馆书单数组末尾录入；
 *        2. 当书单中存  在该书时，返回副本数，询问要
 *          a. 修改 一 副本；
 *          b. 删除 一 副本；
 *          bb.删除所有副本；
 *          c. 录入（复制）一本副本。(副本号置 原副本数+1)
 *          d. 退出
 *          并从最后一本副本开始传入相关函数
 *        注意：
 *        1. 使用 ...Search 函数查找图书；
 *        2. 使用 LibraryBook_Append_Update 函数修改和录入图书，
 *           修改所有副本时，使用 LibraryBook_Copy 函数将首个修改后的图书复制到其他副本位置；
 *        3. 使用 LibraryBook_Delete 函数删除图书。
 * @param lib
 * @param bk_position
**/
void LibraryBook_Append_Update_Delete_Director(Library &lib);

void LibraryBook_Update_Copy_Delete_Director(Library &lib, std::vector<int> bk_position);

/*-----------------------------------------------------------------------------*/

/**
 * @brief 按ID查找是否存在该借书者
 *
 * @param gp
 * @param id
 * @return int 存在则返回1，不存在返回0
**/
int UserID_Exist(BorrowerGroup gp, const std::string &id);


/**
 * @brief 需要检查用户是否有借书权限，
 *        存在用户且有结束权限时，返回用户在名单中的位置1，2，3...，
 *        否则返回0
 *
 * @param gp
 * @param id
 * @return
 */
int UserValidation_Search_Borrow(BorrowerGroup gp, const std::string &id);

/**
 * @brief 无需检查用户是否有借书权限
 *        存在用户时，返回用户在名单中的位置1，2，3...，
 *        否则返回0
 *
 * @param gp
 * @param id
 * @return
 */
int UserValidation_Search_Giveback(BorrowerGroup gp, const std::string &id);

/*-----------------------------------------------------------------------------*/

/**
 * @brief 图书借出
 *        要求用户输入
 *          1. ID                       // 后续可添加密码
 *          使用函数查找是否有该人
 *          若有：
 *              检测其是否具备借书资格（0：允许借书）（1：不允许借书）
 *          若无则输出“查无此人”
 *          2. 书名/ISBN
 *          使用函数查找是否有该书
 *          若返回vector长度不为0，则遍历：
 *              检测是否有剩余图书（0：图书在馆）（-2：图书逾期；-1：图书借出1：图书在途）
 *          若返回vector长度 为 0，则输出“查无此书”
 *        检测该用户是否已借出该书副本
 *        如以上任一条件不满足时，立即按值输出不满足原因并退出函数；
 *        如以上条件均满足，修改该 BookID 对应图书借出历史和用户借阅历史，借书时间从 GetCurrentTime 返回值赋值（仅精确到天） // 存在跨日可能
 *                        修改该 BookID 对应图书出借状态
 *
 * @param gp
 * @param lib
**/
void UserBookBorrow(BorrowerGroup &gp, Library &lib);

/*-----------------------------------------------------------------------------*/

int UserBrrwHistory_UpdateBorrow(BorrowHistory &brrw_history, std::string bk_ID);

int BookLendHistory_UpdateBorrow(std::vector<BorrowerNode> &ld_history, std::string brrwr_ID);

/*-----------------------------------------------------------------------------*/

/**
 * @brief 按名称查找图书，并以vector返回书单中所有满足条件的图书的自然位置
 *
 * @param lib
 * @param bk_name
 * @return vector 返回书单中的自然位置（1，2，3...）
 *                失败返回长度为0的vector
**/
std::vector<int> User_BorrowedBook_NameSearch(Library lib, BorrowHistory brrw_history, const std::string &bk_name);

/**
 * @brief 按ISBN查找图书，并以vector返回书单中所有满足条件的图书的自然位置
 *
 * @param lib
 * @param bk_ISBN
 * @return vector 返回书单中的自然位置（1，2，3...）
 *                失败返回长度为0的vector
**/
std::vector<int> User_BorrowedBook_ISBNSearch(Library lib, BorrowHistory brrw_history, const std::string &bk_ISBN);

/*-----------------------------------------------------------------------------*/
/**
 * @brief 图书归还
 *        要求用户输入
 *          1. ID                       // 后续可添加密码
 *          使用函数查找是否有该人
 *          若有：
 *              检测其当前借书量是否为0，为 0 则输出“无借书记录”，否则继续
 *          若无则输出“查无此人”
 *          2. 书名/ISBN
 *          查找该人借书链表中是否有该书
 *          若有：
 *              检查该书借书状态（-2：借书逾期；-1：借书正常）（0：已归还） // 暂不考虑逾期的处理问题
 *          若无则输出“未借出该书”
 *        以上条件任一不满足时，立即输出不满足原因并退出函数
 *        如以上条件均满足，修改该 BookID 对应图书出借状态（0：图书在馆）和
 *                            该用户的当前借书量、借阅历史中该 BookID 对应的借书状态（0：已归还） // 暂不考虑逾期罚款问题
 *
 * @param gp
 * @param lib
**/
void UserBookGiveback(BorrowerGroup &gp, Library &lib);

int UserBookHistory_UpdateGiveback(BorrowHistory &brrw_history, int giveback_brrwedbook_numero);

int BookLendState_UpdateGiveback(Library &lib, const std::string &giveback_bkID);


int ShowMainMenu(Library &lib);

void DataBackupAndRestoreMenu(Library& lib);
