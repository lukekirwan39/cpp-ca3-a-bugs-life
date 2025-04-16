cmake_minimum_required(VERSION 3.21)
project(ca3-a-bugs-life)

set(CMAKE_CXX_STANDARD 17)

# Set the SFML 2.6.2 path explicitly
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")


find_package(SFML 2 REQUIRED COMPONENTS graphics window audio system)

# Add ALL .cpp files used in the project
add_executable(ca3-a-bugs-life
        main.cpp
        Crawler.cpp
        Board.cpp
        Hopper.cpp
        Hopper.h
        Bug.cpp
)

# Link SFML libraries
target_link_libraries(ca3-a-bugs-life
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)