cmake_minimum_required(VERSION 3.25)
project(snek_io)

set(CMAKE_CXX_STANDARD 23)

if (APPLE)
    add_compile_options("-stdlib=libc++" "-lc++abi" "-v")
    include_directories(lib/SFML-3.0.0/macos/include)
    link_directories(lib/SFML-3.0.0/macos/lib)
endif (APPLE)

if (WIN32 OR MSVC)
    file(COPY lib/SFML-3.0.0/windoez/bin/ DESTINATION .)
    include_directories(lib/SFML-3.0.0/windoez/include)
    link_directories(lib/SFML-3.0.0/windoez/lib)
endif (WIN32 OR MSVC)

add_executable(snek_io_client
    client/main.cpp
    client/game.cpp
    client/player.cpp
)
target_link_libraries(snek_io_client sfml-audio sfml-graphics sfml-system sfml-window)

add_executable(snek_io_server
        server/main.cpp
)