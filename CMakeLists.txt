cmake_minimum_required(VERSION 3.25)
project(library_book_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(library_book_manager
        src/functions/utils/GetCurrentTime.cpp
        src/functions/utils/GetTimeInput.cpp
        src/functions/LibraryBookNameSearch.cpp
        src/functions/LibraryBookISBNSearch.cpp
        src/functions/LibraryBookIDSearch.cpp
        src/functions/LibraryBook_Delete_fast.cpp
        src/functions/Library_DeletedBooks_sort.cpp
        src/functions/LibraryBook_Copy.cpp
        src/functions/LibraryBook_Append.cpp
        src/functions/LibraryBook_Update_Copy_Delete_Director.cpp
        src/functions/UserID_Exist.cpp
        src/functions/UserValidation_Search_Borrow.cpp
        src/functions/UserValidation_Search_Giveback.cpp
        src/functions/borrow_history/UpdateUserBorrowHistory.cpp
        src/functions/BookLendHistory_UpdateBorrow.cpp
        src/functions/UserBookBorrow.cpp
        src/functions/User_BorrowedBook_NameSearch.cpp
        src/functions/User_BorrowedBook_ISBNSearch.cpp
        src/functions/borrow_history/UpdateUserGivebackHistory.cpp
        src/functions/BookLendState_UpdateGiveback.cpp
        src/functions/UserBookGiveback.cpp
        src/functions/LibraryBook_Update.cpp
        src/functions/menus/ShowMainMenu.cpp
        src/functions/menus/LibraryBookAppendUpdateDeleteDirector.cpp
        src/functions/menus/DataBackupAndRestoreMenu.cpp
        src/functions/menus/LibrarySearchMenu.cpp
        src/functions/menus/UserBorrowAndGiveBackMenu.cpp
        src/main.cpp
        src/functions/menus/UserManagement.cpp
        src/functions/menus/Library_User_infoMenu.cpp

)
