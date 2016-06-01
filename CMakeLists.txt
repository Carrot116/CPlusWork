cmake_minimum_required(VERSION 3.5)
project(FirstDemo)
INCLUDE_DIRECTORIES("/usr/local/mysql/include")
LINK_DIRECTORIES(/usr/local/mysql/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES cpp/main.cpp cpp/fun.cpp head/funHead.h head/FunMysql.h cpp/FunMysql.cpp cpp/HXLMysql.cpp head/HXLMysql.h)

add_executable(FirstDemo ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(FirstDemo libmysqlclient.a)