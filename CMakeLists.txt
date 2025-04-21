cmake_minimum_required(VERSION 3.21)
project(ca3-a-bugs-life)

set(CMAKE_CXX_STANDARD 17)

# Set SFML path (adjust for your OS if needed)
set(SFML_DIR "C:/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2 REQUIRED COMPONENTS graphics window audio system)

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

# Link SFML only to game_app
target_link_libraries(game_app
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
)