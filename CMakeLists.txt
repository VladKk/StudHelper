cmake_minimum_required(VERSION 3.14)

project(StudHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(StudHelper main.cpp StudHelper.cpp StudHelper.h)

target_link_libraries(StudHelper ${PQXX_LIB} ${PQ_LIB})