# command to build 
# rm -rf build
# mkdir build
# cd build
# cmake ..
# make



cmake_minimum_required(VERSION 3.10)
project(osu2)

set(CMAKE_CXX_STANDARD 17)

# Gather all your source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    dependencies/glad/src/gl.c
)

add_executable(osu2 ${SOURCES})

# Find required packages
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

# Find FreeType
pkg_check_modules(FREETYPE REQUIRED freetype2)

message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")
message(STATUS "FREETYPE_LIBRARIES: ${FREETYPE_LIBRARIES}")
message(STATUS "FREETYPE_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")

target_include_directories(osu2 PRIVATE
    src
    dependencies/glad/include
    /opt/homebrew/include
    /opt/homebrew/include/freetype2
    src/audio_manager
    src/generators
    src/logical
    src/renderer
    src/input_manager
    src/game_session
    src/utils
    dependencies
    ${GLFW_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
)

# Link directories where Homebrew installs libs
link_directories(/opt/homebrew/lib /opt/homebrew/Cellar/glfw/3.4/lib)

# Link libraries
target_link_libraries(osu2
    ${OPENGL_LIBRARIES}
    pthread
    /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.dylib
    /opt/homebrew/lib/libsndfile.dylib
    /opt/homebrew/lib/libfreetype.dylib
)

# Add FreeType compiler flags if needed
target_compile_options(osu2 PRIVATE ${FREETYPE_CFLAGS_OTHER})