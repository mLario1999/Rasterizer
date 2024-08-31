cmake_minimum_required(VERSION 3.10)

# Define the project
project(tgabasic)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# Add the library target
add_library(${PROJECT_NAME} STATIC
    src/tgabasic.cpp
    src/tgashapes.cpp
)

# Specify the location of the header files
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Add an executable for testing
add_executable(tgabasic_test
    tests/test_tgabasic.cpp
)

# Link the tgabasic library with the executable
target_link_libraries(tgabasic_test
    ${PROJECT_NAME}
)