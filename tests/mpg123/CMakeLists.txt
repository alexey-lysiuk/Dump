cmake_minimum_required(VERSION 3.0)

project(mpg123_test)

find_package(mpg123 REQUIRED)

add_executable(mpg123_test mpg123_test.c)

target_link_libraries(mpg123_test PRIVATE MPG123::libmpg123)
