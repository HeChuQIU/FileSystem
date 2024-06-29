cmake_minimum_required(VERSION 3.28)
project(FileSystem)

set(CMAKE_CXX_STANDARD 26)

add_subdirectory(lib/CLI11)

set (CLI11_DIR "lib/CLI11")

include_directories(${CLI11_DIR}/include)

add_subdirectory(lib/googletest)

add_subdirectory(user)

add_subdirectory(disk)

add_executable(FileSystem main.cpp)
target_link_libraries(FileSystem PRIVATE user)
