cmake_minimum_required(VERSION 3.10)
project(GrainWarehouseC C)

set(CMAKE_C_STANDARD 11)

add_executable(GrainWarehouseC main.c
        DataStorageStructures/eilė_2/queue.h
        DataStorageStructures/eilė_2/queue.c
        DataStorageStructures/stekas_1/stack.h
        DataStorageStructures/stekas_1/stack.c)