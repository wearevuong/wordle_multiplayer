cmake_minimum_required(VERSION 3.10)
project(WordleMultiplayer C)

set(CMAKE_C_STANDARD 11)

if(WIN32)
    set(LIBS ws2_32)
endif()

include_directories(src)

set(COMMON_SRC src/common/protocol.c)

add_executable(wordle_server src/server/main.c src/server/game.c src/server/room.c src/server/scoreboard.c ${COMMON_SRC})
target_link_libraries(wordle_server ${LIBS})

add_executable(wordle_client src/client/main.c ${COMMON_SRC})
target_link_libraries(wordle_client ${LIBS})
