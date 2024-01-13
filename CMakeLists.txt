cmake_minimum_required(VERSION 3.22.1)
project(snek_io)

set(CMAKE_CXX_STANDARD 23)

file(COPY assets/ DESTINATION assets)

if (APPLE)
    add_compile_options("-stdlib=libc++" "-lc++abi" "-v")
    include_directories(lib/SFML-2.6.1/macos_arm64/include)
    link_directories(lib/SFML-2.6.1/macos_arm64/lib)
endif (APPLE)

if (UNIX AND NOT APPLE)
    include_directories(lib/SFML-2.6.1/linux_gcc/include)
    link_directories(lib/SFML-2.6.1/linux_gcc/lib)
endif (UNIX AND NOT APPLE)

if (WIN32)
    file(COPY lib/SFML-2.6.1/windoez_vc/bin/ DESTINATION .)
    include_directories(lib/SFML-2.6.1/windoez_vc/include)
    link_directories(lib/SFML-2.6.1/windoez_vc/lib)
endif (WIN32)

file(GLOB client_sources "client/*.cpp")
add_executable(snek_io_client ${client_sources})
target_link_libraries(snek_io_client sfml-audio sfml-graphics sfml-network sfml-system sfml-window)

file(GLOB server_sources "server/*.cpp")
add_executable(snek_io_server ${server_sources})