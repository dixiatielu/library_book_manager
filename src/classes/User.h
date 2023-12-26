//
// Created by 地铁DXTL on 2023/12/26.
//

#ifndef LIBRARY_BOOK_MANAGER_USER_H
#define LIBRARY_BOOK_MANAGER_USER_H


#include <string>

class User {
public:
    User() = default;

private:
    int id = 0; // 用户id
    std::string name; // 用户名
    enum permission{ // 权限管理
        SuperAdmin,
        Admin,
        OrdinaryUser
    };
};


#endif //LIBRARY_BOOK_MANAGER_USER_H
