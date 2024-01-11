cmake_minimum_required(VERSION 3.25)
project(projekt)

add_compile_options("-stdlib=libc++" "-lc++abi" "-v")

set(CMAKE_CXX_STANDARD 23)

if (APPLE)
    include_directories(lib/SFML-3.0.0/macos/include)
    link_directories(lib/SFML-3.0.0/macos/lib)
endif (APPLE)

if (MSVC)
    include_directories(lib/SFML-3.0.0/windows/include)
    link_directories(lib/SFML-3.0.0/windows/lib)
endif (MSVC)
if (WIN32)
    include_directories(lib/SFML-3.0.0/windows/include)
    link_directories(lib/SFML-3.0.0/windows/lib)
endif (WIN32)

add_executable(projekt
    main.cpp
    game.cpp
    player.cpp
)
target_link_libraries(projekt sfml-audio sfml-graphics sfml-system sfml-window)

