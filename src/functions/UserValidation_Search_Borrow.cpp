//
// Created by 地铁DXTL on 2024/1/4.
//

#include "../include/function_definitions.h"
int UserValidation_Search_Borrow(BorrowerGroup gp, const std::string& id)
{
    for (int i = 1; i <= gp.borrower_amount; i++) {
        if ((gp.borrower_list[i].ID == id)
            &&(gp.borrower_list[i].permission_flag == 0)) {
            return i;
        } else{
            continue;
        }
    }
    return 0;
}