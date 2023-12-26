cmake_minimum_required(VERSION 3.27)
project(library_book_manager)

set(CMAKE_CXX_STANDARD 17)

add_executable(library_book_manager src/main.cpp
        src/classes/Library.h
        src/classes/Book.h
        src/classes/User.h
        src/utils/constant_definitions.h
)
