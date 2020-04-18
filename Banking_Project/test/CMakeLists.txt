cmake_minimum_required(VERSION 3.10)

set(This BankTests)

set(Sources
    BankTests.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    Banking_main
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
    
