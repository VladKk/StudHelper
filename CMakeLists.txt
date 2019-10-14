cmake_minimum_required(VERSION 3.14)
project(StudHelper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)
set(SFML_INCLUDE_DIR "/usr/include/SFML")
set(SFML_LIBRARY_DIR "/usr/lib/x86_64-linux-gnu")
set(SFML_DIR "/usr/lib/x86_64-linux-gnu/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)
find_package(SFML COMPONENTS system window graphics network audio)

add_executable(StudHelper main.cpp StudHelper.cpp StudHelper.h)
target_link_libraries(StudHelper ${PQXX_LIB} ${PQ_LIB} sfml-graphics sfml-window sfml-system sfml-network)