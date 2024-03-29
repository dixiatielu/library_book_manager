/**
 * @file kmp_algorithms_definitions.h
 * @authors
 * Chengpu
 * dixiatielu
 * @brief KMP算法函数声明
 * @version 1.0
 * @date 2024.1
 *
 * @copyright Copyright (c) 2024
 *
**/

#ifndef LIBRARY_BOOK_MANAGER_KMP_ALGORITHMS_DEFINITION_H
#define LIBRARY_BOOK_MANAGER_KMP_ALGORITHMS_DEFINITION_H

#include <string>

void index_construct(int *index_ls, const std::string &sst_patt);

int index_find(const std::string &patt, int pos_limit);

void nextval_construct(int *nextval_ls, int *index_ls, const std::string &sst_patt);

int nextval_find(int *index_ls, const std::string &patt, int pos);

int seek(const std::string &sst_main, const std::string &sst_pattern, int *nextval_ls, int main_position,
         int pattern_position);

#endif //LIBRARY_BOOK_MANAGER_KMP_ALGORITHMS_DEFINITION_H
