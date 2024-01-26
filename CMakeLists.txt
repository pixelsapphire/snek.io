cmake_minimum_required(VERSION 3.22.1)
project(snek_io)

set(CMAKE_CXX_STANDARD 23)

file(COPY client/c_config.txt DESTINATION config)
file(COPY server/s_config.txt DESTINATION config)
file(COPY assets/ DESTINATION assets)

file(GLOB common_sources "common/*.cpp")
include_directories(common)
add_compile_options("-Wall" "-Werror" "-Wextra" "-Wno-unused-command-line-argument")

file(GLOB client_sources "client/*.cpp")
add_executable(snek_io_client ${client_sources} ${common_sources})
target_compile_options(snek_io_client PUBLIC "-stdlib=libc++" "-lc++abi" "-v")
target_include_directories(snek_io_client PRIVATE lib/SFML-2.6.1/macos_arm64/include)
target_link_directories(snek_io_client PRIVATE lib/SFML-2.6.1/macos_arm64/lib)
target_link_libraries(snek_io_client sfml-graphics sfml-network sfml-system sfml-window)

file(GLOB server_sources "server/*.cpp")
add_executable(snek_io_server ${server_sources} ${common_sources})