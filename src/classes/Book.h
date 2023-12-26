//
// Created by 地铁DXTL on 2023/12/26.
//

#ifndef LIBRARY_BOOK_MANAGER_BOOK_H
#define LIBRARY_BOOK_MANAGER_BOOK_H


#include <string>

class Book {
public:
    Book() = default;

private:
    int id; // 系统标识符id
    std::string name; // 书名
    std::string ISBN; // 书的ISBN
    std::string classification_id; // 中国图书馆分类号
    int year; // 出版年
    int version = 0; // 版本id
    enum type{ // 书的类型，根据中国图书馆分类号来
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
    };
};


#endif //LIBRARY_BOOK_MANAGER_BOOK_H
