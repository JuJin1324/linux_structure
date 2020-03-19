cmake_minimum_required(VERSION 3.15)
project(linux_structure C)

set(CMAKE_C_STANDARD 99)

## Chapter 2
add_executable(hello chapter2/hello.c)
add_executable(loop chapter2/loop.c)
add_executable(ppidloop chapter2/ppidloop.c)

## Chapter 3
add_executable(fork chapter3/fork.c)
add_executable(fork_and_exec chapter3/fork_and_exec.c)