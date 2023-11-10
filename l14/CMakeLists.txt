cmake_minimum_required(VERSION 3.10)
find_package(LLVM REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
set(LLVM_INCLUDE_DIRS /usr/lib/llvm-9/include)
include_directories(${LLVM_INCLUDE_DIRS})

add_subdirectory(src)
