cmake_minimum_required(VERSION 3.10)
project(DicesPalace)

# Basic configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory for executables
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# Include directories
# Include folder (all .h files are included)
include_directories(src/include)

# Source files
# Add here the new files that are created
set(SOURCES
    "src/main.cpp"
    "src/maze.cpp"
    "src/player.cpp"
    "src/bosses.cpp"
    "src/miniGames/1_riddles.cpp"
    "src/miniGames/2_spotDifference.cpp"
    "src/miniGames/3_numberSort.cpp"
    "src/miniGames/4_keySmash.cpp"
    "src/levels/level1.cpp"
    "src/levels/level2.cpp"
    "src/levels/level3.cpp"
    "src/levels/level4.cpp"
    "src/utils/consoleUtils.cpp"
    "src/utils/menu.cpp"
    "src/utils/sounds.cpp"
    "src/utils/story.cpp"


)

# Create the main executable
add_executable(DicesPalace ${SOURCES})
# It is specified that it is a console application
target_link_libraries(DicesPalace PRIVATE mingw32) 

# Copy data folder to the output directory
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${EXECUTABLE_OUTPUT_PATH})


# Windows specific configurations
if(WIN32)
    target_link_libraries(DicesPalace PRIVATE winmm)
endif()

message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "Output will be in: ${EXECUTABLE_OUTPUT_PATH}")
message(STATUS "Data files will be copied to: ${EXECUTABLE_OUTPUT_PATH}/data")