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

add_executable(snek_io
    main.cpp
    game.cpp
    player.cpp
)
target_link_libraries(snek_io sfml-audio sfml-graphics sfml-system sfml-window)

