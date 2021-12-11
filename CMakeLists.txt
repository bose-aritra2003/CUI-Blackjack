cmake_minimum_required(VERSION 3.20)
project(CUI_Blackjack)

set(CMAKE_CXX_STANDARD 17)

add_executable(CUI_Blackjack source/main.cpp source/define.cpp source/define.h source/blackjack.cpp source/sleep.h)
