cmake_minimum_required(VERSION 3.13.4)
project(GreetingGame VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

set(SOURCES src/Agent.cpp src/Game.cpp src/main.cpp inc/Agent.h inc/Game.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)
add_executable(GreetingGame ${SOURCES})

target_link_libraries(GreetingGame LINK_PUBLIC sqlite3)

# This didn't work, but I thought it would.
# find_package (SQLite3)
# include_directories(${SQLITE3_INCLUDE_DIRS})
# target_link_libraries (GreetingGame ${SQLITE3_LIBRARIES})

