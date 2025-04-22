cmake_minimum_required(VERSION 3.21)
project(ca3-a-bugs-life)

set(CMAKE_CXX_STANDARD 17)

# Let CMake find SFML installed by Homebrew
# (Homebrew typically installs it under /opt/homebrew)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH} /opt/homebrew/Cellar/sfml/2.5.1/lib/cmake/SFML")

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window audio system)

# === Console Version ===
add_executable(console_app
        main.cpp
        Board.cpp
        Crawler.cpp
        Hopper.cpp
        Jumper.cpp
        Bug.cpp
)

# === SFML Game Version ===
add_executable(game_app
        Game.cpp
        Board.cpp
        Crawler.cpp
        Hopper.cpp
        Jumper.cpp
        Bug.cpp
)

# Include SFML headers
include_directories(/opt/homebrew/include)

# Link SFML only to game_app
target_link_libraries(game_app
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)

# Link directories for Homebrew's lib path
link_directories(/opt/homebrew/lib)
