//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../include/function_definitions.h"

int UserID_Exist(BorrowerGroup gp, const std::string& id)
{
    for (int i = 1; i <= gp.borrower_amount; i++) {
        if (gp.borrower_list[i].ID == id) {
            return 1;
        } else{
            continue;
        }
    }
    return 0;
}