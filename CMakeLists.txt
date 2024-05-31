cmake_minimum_required(VERSION 3.27)
project(cursova)

set(CMAKE_CXX_STANDARD 17)

add_executable(cursova main.cpp)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(cursova ${CURL_LIBRARIES})