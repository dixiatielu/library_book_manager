//
// Created by 地铁DXTL on 2024/1/4.
//
#include <iostream>
#include "../../headers/function_definitions.h"

using namespace std;

void displayUserManagementMenu() {

//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_INTENSITY|FOREGROUND_GREEN);	// 设置输出字符颜色为强调、红色
    cout << fmt::format("\n{:*^34}\n", "用户信息管理菜单");
    cout << "1. 显示所有用户信息" << endl;
    cout << "2. 添加新用户" << endl;
    cout << "3. 删除用户" << endl;
    cout << "4. 修改用户信息" << endl;
    cout << "0. 返回上一级菜单" << endl;
    cout << "请输入相应的数字进行操作: ";
//    SetConsoleTextAttribute(ConsoleColorHandle, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE); // 还原字符颜色
}

void displayAllUsers(const BorrowerGroup& g) {
    if (g.borrower_amount == 0) {
        cout << "\n当前无用户信息\n\n";
    } else{
        cout << "\n所有用户信息：\n" << endl;
        bool first_flag = true;
        for (const User& user : g.borrower_list) {
            if(first_flag){
                first_flag = false;
                continue;
            }
            cout << user << endl;
        }
        cout << fmt::format("\n当前有{:-^5}名用户\n", g.borrower_amount);
    }

}

void addUser(BorrowerGroup& g) {
    User newUser;

    cout << "\n请输入新用户的信息" << endl;
    cout << "用户ID\n"
            "&?-";
    cin >> newUser.ID;

    // Check if the user already exists
    auto it = find_if(g.borrower_list.begin(), g.borrower_list.end(),
                      [&](const User& existingUser) { return existingUser.ID == newUser.ID; });

    if (it != g.borrower_list.end()) {
        cout << "用户已存在，添加失败。" << endl;
        return;
    }

    cout << "性别（0表示男，1表示女）\n"
            "&?-";
    cin >> newUser.gender;

    cout << "借书权限（0表示允许借书，1表示不允许借书）\n"
            "&?-";
    cin >> newUser.permission_flag;
    newUser.borrow_history.borrowed_books_cur = 0;
    newUser.borrow_history.borrowed_books_acc = 0;
    // Add the new user to the group
    g.borrower_amount++;
    g.borrower_list.emplace_back(newUser);

    cout << "用户添加成功。" << endl;
}

// TODO: 只有用户当前没有借书、还清罚款时才能删除
void deleteUser(BorrowerGroup& g) {
    string userID;
    cout << "请输入要删除的用户ID\n"
            "&?-";
    cin >> userID;

    // Find the user by ID
    auto it = find_if(g.borrower_list.begin(), g.borrower_list.end(),
                      [&](const User& user) { return user.ID == userID; });

    if (it != g.borrower_list.end()) {
        // Remove the user from the group
        g.borrower_list.erase(it);
        g.borrower_amount--;

        cout << "用户删除成功!" << endl;
    } else {
        cout << "未找到该用户!" << endl;
    }
}

void modifyUserInfo(BorrowerGroup& g) {
    string userID;
    cout << "请输入要修改的用户ID\n"
            "&?-";
    cin >> userID;

    // Find the user by ID
    auto it = find_if(g.borrower_list.begin(), g.borrower_list.end(),
                      [&](const User& user) { return user.ID == userID; });

    if (it != g.borrower_list.end()) {
        // Modify user information
        int choice;
        cout << "请选择要修改的字段：" << endl;
        cout << "1. 修改性别" << endl;
        cout << "2. 修改借书权限" << endl;
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "请输入新的性别（0表示男，1表示女）: ";
                cin >> it->gender;
                cout << "用户性别修改成功!" << endl;
                break;

            case 2:
                cout << "请输入新的借书权限（0表示允许借书，1表示不允许借书）: ";
                cin >> it->permission_flag;
                cout << "用户借书权限修改成功!" << endl;
                break;

            default:
                cout << "无效的选项!" << endl;
                break;
        }
    } else {
        cout << "未找到该用户!" << endl;
    }
}

void UserManagement(BorrowerGroup& g) {
    int choice;

    do {
        displayUserManagementMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllUsers(g);
                break;

            case 2:
                addUser(g);
                break;

            case 3:
                deleteUser(g);
                break;

            case 4:
                modifyUserInfo(g);
                break;

            case 0:
                cout << "返回上一级菜单" << endl;
                break;

            default:
                cout << "无效的选项，请重新输入" << endl;
        }
    } while (choice != 0);
}
