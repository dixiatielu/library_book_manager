//
// Created by 地铁DXTL on 2023/12/26.
//

#ifndef LIBRARY_BOOK_MANAGER_LIBRARY_H
#define LIBRARY_BOOK_MANAGER_LIBRARY_H


#include <vector>
#include "../utils/constant_definitions.h"
#include "Book.h"
#include "User.h"

class Library {
public:
    Library() = default;

    Status showMainMenu();
private:
    std::vector<Book> books; // 存放图书馆里书的vector
    std::vector<User> users;
};

Status Library::showMainMenu() {
    std::cout << "欢迎来到图书馆！" << std::endl;
    std::cout << "主菜单" << std::endl;
    return 0;
}


#endif //LIBRARY_BOOK_MANAGER_LIBRARY_H
