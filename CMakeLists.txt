cmake_minimum_required(VERSION 3.5.0)
project(tgabasic VERSION 0.1.0 LANGUAGES C CXX)

add_library(tgabasic tgabasic.cpp)

install (TARGETS tgabasic
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib
         RUNTIME DESTINATION bin)