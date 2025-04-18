cmake_minimum_required(VERSION 3.16)
project(Swordlord)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include src directory
include_directories(src)

# Gather all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add executable
add_executable(Swordlord ${SOURCES})

# Find SDL2, SDL2_ttf, SDL2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

# Include SDL headers
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link SDL libraries
target_link_libraries(Swordlord
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    SDL2 SDL2_ttf SDL2_image
)

# Copy assets directory after build
add_custom_command(TARGET Swordlord POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Swordlord>/assets
)
