//
// Created by Cp on 2024/01/04.
//
#include "../../headers/function_definitions.h"

void Library_User_InfoMenu(const Library &lib, const BorrowerGroup &gp) {
    std::cout << fmt::format("当前图书馆中有{:-^5}本图书，{:-^5}名借书者\n\n", lib.book_amount_real, gp.borrower_amount);
}