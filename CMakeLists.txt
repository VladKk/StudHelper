cmake_minimum_required(VERSION 3.14)
project(StudHelper)

set(CMAKE_CXX_STANDARD 17)

add_executable(StudHelper main.cpp StudHelper.cpp StudHelper.h)

include_directories("/usr/include/LibXL")

target_link_libraries(StudHelper "/usr/lib/x86_64-linux-gnu/libxl.so")