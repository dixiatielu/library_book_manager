//
// Created by 地铁DXTL on 2024/1/4.
//
#include "../headers/function_definitions.h"
int BookLendHistory_UpdateBorrow(std::vector<BorrowerNode> &ld_history, std::string brrwr_ID)
{
    BorrowerNode brrwr_node = {
            .borrower_ID = std::move(brrwr_ID),
            .lend_date = GetCurrentTime()
    };

    ld_history.emplace_back(brrwr_node);
    return 0;
}