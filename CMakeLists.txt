cmake_minimum_required(VERSION 3.27)
project(cursova)

set(CMAKE_CXX_STANDARD 17)

add_executable(cursova main.cpp
        API.cpp
        account.cpp
        leaderboard.cpp
        view.cpp
        wordsgame.cpp
        wordsClassic.cpp
        wordsSentence.cpp
        wordsHidden.cpp
        mode_enum.cpp
        difficulty_enum.cpp
)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})
target_link_libraries(cursova ${CURL_LIBRARIES})