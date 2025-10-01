cmake_minimum_required(VERSION 3.10)   
project(MyShell CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/command)

# set sources
set(SOURCES
    main.cpp
    command/command.cpp
)

# create exec file
add_executable(myshell ${SOURCES})


if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(shell stdc++fs)
endif()
