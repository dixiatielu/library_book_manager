cmake_minimum_required(VERSION 3.27)
project(library_book_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(library_book_manager src/main.cpp
        src/functions/GetCurrentTime.cpp
        src/functions/GetTimeInput.cpp
        src/functions/LibraryBookNameSearch.cpp
        src/functions/LibraryBookISBNSearch.cpp
        src/functions/LibraryBookIDSearch.cpp
        src/functions/LibraryBook_Delete_fast.cpp
        src/functions/Library_DeletedBooks_sort.cpp
        src/functions/LibraryBook_Copy.cpp
        src/functions/LibraryBook_Append_Update_Delete_Director.cpp
        src/functions/LibraryBook_Append.cpp
        src/functions/LibraryBook_Update_Copy_Delete_Director.cpp
        src/functions/UserID_Exist.cpp
        src/functions/UserValidation_Search_Borrow.cpp
        src/functions/UserValidation_Search_Giveback.cpp
        src/functions/UserBrrwHistory_UpdateBorrow.cpp
        src/functions/BookLendHistory_UpdateBorrow.cpp
        src/functions/UserBookBorrow.cpp
        src/functions/User_BorrowedBook_NameSearch.cpp
        src/functions/User_BorrowedBook_ISBNSearch.cpp
        src/functions/UserBookHistory_UpdateGiveback.cpp
        src/functions/BookLendState_UpdateGiveback.cpp
        src/functions/UserBookGiveback.cpp
        src/functions/LibraryBook_Update.cpp
)
