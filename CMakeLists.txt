cmake_minimum_required(VERSION 3.22.1)
project(snek_io)

set(CMAKE_CXX_STANDARD 23)

file(COPY assets/ DESTINATION assets)

if (APPLE)
    add_compile_options("-stdlib=libc++" "-lc++abi" "-v")
    include_directories(lib/SFML-2.6.1/macos_arm64/include)
    link_directories(lib/SFML-2.6.1/macos_arm64/lib)
endif (APPLE)

if (WIN32)
    file(COPY lib/SFML-2.6.1/windoez_vc/bin/ DESTINATION .)
    include_directories(lib/SFML-2.6.1/windoez_vc/include)
    link_directories(lib/SFML-2.6.1/windoez_vc/lib)
endif (WIN32)

add_executable(snek_io_client
    client/main.cpp
    client/game.cpp
    client/player.cpp
    client/scene.cpp
    client/scene_main.cpp
    client/scene_nickname.cpp
    client/utility.cpp
)
target_link_libraries(snek_io_client sfml-audio sfml-graphics sfml-system sfml-window)

add_executable(snek_io_server
    server/main.cpp
)