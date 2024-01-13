/*
**    文件名：kmp_algorithms.cpp
**    文件内容：
**        包含KMP算法所使用的所有函数
*/

#include "kmp_algorithms_definition.h"
//------------------------------------------------------
/*    函数名：index_construct
**    输入变量：(int*) index_ls, next空数组指针； (std::string) sst_patt， 模式串
**    输出变量：无
**    调用函数：index_find
**    作用：
**        根据模式串构建next数组（即此处index_ls数组）
---------------------------------------------------------*/
void index_construct(int* index_ls, const std::string& sst_patt)
{
    for (int i = 1; i <= sst_patt.length(); i++) {
        index_ls[i] = index_find(sst_patt, i) + 1;       // 注意：index_ls中的序号为自然排序序号
    }
}

//------------------------------------------------------
/*    函数名：index_find
**    输入变量：(std::string) patt，模式串； (int) pos_limit指针，当前计算数值对应的next数组、模式串中的位数
**    输出变量：accu，最长相同前后缀长度
**    调用函数：无
**    作用：
**        根据模式串计算next数组中的数值（即此处index_ls数组）
---------------------------------------------------------*/
int index_find(const std::string& patt, int pos_limit)
{
    int accu = 0;
    int pos_smp = 1; // abbr. of "position of sample"，前缀相同串的测试点
    int pos_cmp = 2; // abbr. of "position of co-sample"，后缀相同串的测试点

    if (pos_limit == 1){
        return -1; // 使next数组第一个元素（next[1]）为0

    } else {
        while (pos_cmp <= pos_limit - 1) {
            if (patt[pos_smp - 1] == patt[pos_cmp - 1]) { // 当前、后缀测试点字符相同时
                accu += 1; // 相同前后缀长度 +1

                pos_smp += 1; // 移动测试点至后一位
                pos_cmp += 1;
            } else { // 当前、后缀测试点字符不同时
                accu = 0; // 清零相同前后缀长度

                pos_smp = 1; // 移动前缀测试点至模式串的第一个元素
                pos_cmp += 1; // 移动后缀测试点至后一位
            }
        }
        return accu; // 返回最大相同前后缀长度
    }
}

//------------------------------------------------------
/*    函数名：nextval_construct
**    输入变量：(int*) nextval_ls，nextval空数组指针；(int*) index_ls，next数组指针；
**             (std::string) sst_patt，模式串
**    输出变量：无
**    调用函数：nextcval_find
**    作用：
**        根据模式串计算nextval数组中的数值
---------------------------------------------------------*/
void nextval_construct(int* nextval_ls, int* index_ls, const std::string& sst_patt)
{
    for (int i = 1; i <= sst_patt.length(); i++) {
        nextval_ls[i] = nextval_find(index_ls, sst_patt, i); // 注意：nextval_ls中的序号为自然排序序号
    }
}

//------------------------------------------------------
/*    函数名：nextval_find
**    输入变量：(int*)index_ls，next数组指针；(std::string) patt，模式串；
**              (int) pos，当前计算数值对应的nextval数组、模式串中的位数
**    输出变量：（无对应变量）直接返回0或next数组中的数值
**    调用函数：无
**    作用：
**        根据模式串计算nextval数组中的数值
**    注意：
**        存在递归调用
---------------------------------------------------------*/
int nextval_find(int* index_ls, const std::string& patt, int pos)
{
    if (pos == 1) {
        return 0; // 使nextval数组第一个元素（nextval[1]）为0

    } else if (patt[pos - 1] != patt[index_ls[pos] - 1]) { // 当该位在next数组中的对应位是不同字符时
        return index_ls[pos]; // 返回该位在next数组中对应的数值

    } else { // 当该位在next数组中的对应位是相同字符时
        return nextval_find(index_ls, patt, index_ls[pos]); // 递归调用，返回该位在 next数组 中的对应位在 nextval数组 中的数值
    }
}

//------------------------------------------------------
/*    函数名：seek
**    输入变量：(std::string) sst_main，主串；(std::string) sst_pattern，模式串；
**             (int*) nextval_ls，nextval数组指针；(int) main_position，主串开始匹配的位置；
**             (int) pattern_position，模式串开始匹配的位置
**    输出变量：（无对应变量）直接返回0（表示未找到）或模式串在主串中的位置
**    调用函数：无
**    作用：
**        使用nextval数组在主串中寻找是否存在模式串，并返回0（表示未找到）或模式串在主串中的位置
---------------------------------------------------------*/
int seek(const std::string& sst_main, const std::string& sst_pattern, int* nextval_ls, int main_position, int pattern_position)
{
    while ((main_position <= sst_main.length()) && (pattern_position <= sst_pattern.length())) { // 当主串检测位和模式串检测位均未越位时
        if ((pattern_position == 0) || (sst_main[main_position - 1] == sst_pattern[pattern_position - 1])) {
            // 当模式串检测位为零或主串和模式串检测位对应字符相同时
            main_position += 1; // 移动主串、模式串检测位至后一位
            pattern_position += 1;
        } else { // 当模式串检测位为零或主串和模式串检测位对应字符不同时
            pattern_position = nextval_ls[pattern_position]; // 移动 模式串检测位 至当前位置在 nextval数组 中对应的数值处
        }
    } // 主串检测位或模式串检测位越位时

    if (pattern_position > sst_pattern.length()) { // 当模式串越位时
        return (main_position - sst_pattern.length()); // 返回主串中模式串的对应位置

    } else { // 当主串越位时
        return 0; // 返回0，表示在主串中未找到模式串
    }
}
