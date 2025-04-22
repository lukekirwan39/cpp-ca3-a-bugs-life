#cmake_minimum_required(VERSION 3.21)
#project(ca3-a-bugs-life)
#
#set(CMAKE_CXX_STANDARD 17)
#
## Let CMake find SFML installed by Homebrew
## (Homebrew typically installs it under /opt/homebrew)
#set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} /opt/homebrew/Cellar/sfml/2.5.1/lib/cmake/SFML")
#
## Find SFML
#find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio system)
#
## === Console Version ===
#add_executable(console_app
#        main.cpp
#        Board.cpp
#        Crawler.cpp
#        Hopper.cpp
#        Jumper.cpp
#        Bug.cpp
#)
#
## === SFML Game Version ===
#add_executable(game_app
#        Game.cpp
#        Board.cpp
#        Crawler.cpp
#        Hopper.cpp
#        Jumper.cpp
#        Bug.cpp
#)
#
## Include SFML headers
#include_directories(/opt/homebrew/include)
#
## Link SFML only to game_app
#target_link_libraries(game_app
#        PRIVATE
#        sfml-graphics
#        sfml-window
#        sfml-audio
#        sfml-system
#)
#
## Link directories for Homebrew's lib path
#link_directories(/opt/homebrew/lib)
cmake_minimum_required(VERSION 3.21)
project(ca3-a-bugs-life)

set(CMAKE_CXX_STANDARD 17)

# Set the SFML 2.6.2 path explicitly
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")

# Find SFML
find_package(SFML 2 REQUIRED COMPONENTS graphics window audio system)

# Add all .cpp files used in the project
add_executable(ca3-a-bugs-life
        main.cpp
        Crawler.cpp
        Board.cpp
        Hopper.cpp
        Hopper.h
        Bug.cpp
        Jumper.cpp
        Jumper.h
)

# Include SFML headers
include_directories("C:/SFML-2.6.2/include")

# Link SFML libraries
target_link_libraries(ca3-a-bugs-life
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)
