# command to build 
# rm -rf build
# mkdir build
# cd build
# cmake ..
# make


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Add your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# include_directories(
#     src
#     dependencies/glad/include
#     dependencies
#     /opt/homebrew/include
#     /opt/homebrew/lib
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
#     /opt/homebrew/include/freetype2


# )

# # Tell CMake where to find GLFW
# link_directories(/opt/homebrew/lib)
# include_directories(/opt/homebrew/include)


# add_executable(osu2 ${SOURCES} dependencies/glad/src/gl.c)

# find_package(OpenGL REQUIRED)

# # Link libraries (GLFW, OpenGL)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# include_directories(${GLFW_INCLUDE_DIRS})
# link_directories(${GLFW_LIBRARY_DIRS})



# target_link_libraries(osu2 ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
# # target_link_libraries(osu2 sndfile)

# target_link_libraries(osu2 glfw sndfile pthread)


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Add your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# # Add glad source explicitly
# set(GLAD_SOURCES dependencies/glad/src/gl.c)

# # Create the executable
# add_executable(osu2 ${SOURCES} ${GLAD_SOURCES})

# # Include directories
# target_include_directories(osu2 PRIVATE
#     src
#     dependencies
#     dependencies/glad/include
#     /opt/homebrew/include
#     /opt/homebrew/include/freetype2
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
# )

# # Find OpenGL
# find_package(OpenGL REQUIRED)

# # Find GLFW using pkg-config
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# # Link everything
# target_link_libraries(osu2
#     ${GLFW_LIBRARIES}
#     ${OPENGL_LIBRARIES}
#     glfw
#     sndfile
#     pthread
# )

# # If GLFW was found using pkg-config, include its headers
# target_include_directories(osu2 PRIVATE ${GLFW_INCLUDE_DIRS})
# link_directories(${GLFW_LIBRARY_DIRS})

# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Gather all your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     src/*.cpp
#     dependencies/glad/src/glad.c  # glad source
# )

# # Create the executable
# add_executable(osu2 ${SOURCES})

# # Include directories
# target_include_directories(osu2 PRIVATE
#     src
#     dependencies/glad/include         # for glad/glad.h
#     /opt/homebrew/include             # Homebrew headers (GLFW, FreeType, etc.)
#     /opt/homebrew/include/freetype2  # for ft2build.h
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
#     dependencies                       # If you have other dependencies
# )

# # Link directories (used by Homebrew)
# link_directories(/opt/homebrew/lib)

# # Link libraries
# find_package(OpenGL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)
# message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
# message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")


# # target_link_libraries(osu2
# #     ${GLFW_LIBRARIES}
# #     ${OPENGL_LIBRARIES}
# #     glfw                  # Redundant but safe
# #     sndfile               # If you're using miniaudio or similar
# #     freetype              # For FT_FREETYPE_H
# #     pthread
# # )

# target_link_libraries(osu2
#     ${GLFW_LIBRARIES}
#     ${OPENGL_LIBRARIES}
#     sndfile
#     freetype
#     pthread
#     glfw
# )


# target_include_directories(osu2 PRIVATE /opt/homebrew/include/freetype2)


# # Define macro to silence deprecation warnings (optional but useful on macOS)
# add_compile_definitions(GL_SILENCE_DEPRECATION)

# # Recommended: treat all warnings as errors for clean code
# # target_compile_options(osu2 PRIVATE -Wall -Werror)


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Gather all your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     src/*.cpp
#     dependencies/glad/src/glad.c  # glad source
# )

# # Create the executable
# add_executable(osu2 ${SOURCES})

# # Include directories
# target_include_directories(osu2 PRIVATE
#     src
#     dependencies/glad/include         # for glad/glad.h
#     /opt/homebrew/include             # Homebrew headers (GLFW, FreeType, etc.)
#     /opt/homebrew/include/freetype2  # for ft2build.h
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
#     dependencies                       # If you have other dependencies
# )

# # Link directories (used by Homebrew)
# link_directories(/opt/homebrew/lib /opt/homebrew/Cellar/glfw/3.4/lib)




# # Link libraries
# find_package(OpenGL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
# message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")

# # Remove the explicit 'glfw' here because ${GLFW_LIBRARIES} already contains it.
# target_link_libraries(osu2
#     ${GLFW_LIBRARIES}
#     ${OPENGL_LIBRARIES}
#     sndfile
#     freetype
#     pthread
# )

# target_include_directories(osu2 PRIVATE /opt/homebrew/include/freetype2 ${GLFW_INCLUDE_DIRS})

# # Define macro to silence deprecation warnings (optional but useful on macOS)
# add_compile_definitions(GL_SILENCE_DEPRECATION)


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Gather all your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     src/*.cpp
#     dependencies/glad/src/glad.c  # glad source
# )

# # Create the executable
# add_executable(osu2 ${SOURCES})

# # Include directories
# target_include_directories(osu2 PRIVATE
#     src
#     dependencies/glad/include         # for glad/glad.h
#     /opt/homebrew/include             # Homebrew headers (GLFW, FreeType, etc.)
#     /opt/homebrew/include/freetype2  # for ft2build.h
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
#     dependencies                       # If you have other dependencies
#     ${GLFW_INCLUDE_DIRS}              # Added from pkg-config
# )

# # Link directories (used by Homebrew)
# link_directories(/opt/homebrew/lib /opt/homebrew/Cellar/glfw/3.4/lib)

# # Find required packages
# find_package(OpenGL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
# message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")

# # Link libraries, explicitly adding GLFW dylib if linker can't find it
# target_link_libraries(osu2
#     ${OPENGL_LIBRARIES}
#     sndfile
#     freetype
#     pthread
#     ${GLFW_LIBRARIES}
#     /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.dylib
# )

# # Define macro to silence deprecation warnings (optional but useful on macOS)
# add_compile_definitions(GL_SILENCE_DEPRECATION)


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Gather all your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     src/*.cpp
#     dependencies/glad/src/glad.c  # glad source
# )

# # Create executable
# add_executable(osu2 ${SOURCES})

# # Include directories
# target_include_directories(osu2 PRIVATE
#     src
#     dependencies/glad/include
#     dependencies
#     /opt/homebrew/include
#     /opt/homebrew/include/freetype2
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
# )

# # Link directories
# link_directories(
#     /opt/homebrew/lib
#     /opt/homebrew/Cellar/glfw/3.4/lib
# )

# # Find required packages
# find_package(OpenGL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
# message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")

# # Add GLFW include dirs from pkg-config
# target_include_directories(osu2 PRIVATE ${GLFW_INCLUDE_DIRS})

# # Link libraries with explicit libglfw.dylib and sndfile
# target_link_libraries(osu2
#     ${OPENGL_LIBRARIES}
#     sndfile
#     pthread
#     ${GLFW_LIBRARIES}
#     /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.dylib
# )

# # Silence macOS deprecation warnings
# add_compile_definitions(GL_SILENCE_DEPRECATION)


# cmake_minimum_required(VERSION 3.10)
# project(osu2)

# set(CMAKE_CXX_STANDARD 17)

# # Gather all your source files
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
#     src/*.cpp
#     dependencies/glad/src/gl.c
# )

# add_executable(osu2 ${SOURCES})

# target_include_directories(osu2 PRIVATE
#     src
#     dependencies/glad/include
#     /opt/homebrew/include
#     /opt/homebrew/include/freetype2
#     src/audio_manager
#     src/generators
#     src/logical
#     src/renderer
#     dependencies
# )

# # Link directories where Homebrew installs libs
# link_directories(/opt/homebrew/lib /opt/homebrew/Cellar/glfw/3.4/lib)

# # Find OpenGL and PkgConfig for GLFW
# find_package(OpenGL REQUIRED)
# find_package(PkgConfig REQUIRED)
# pkg_search_module(GLFW REQUIRED glfw3)

# message(STATUS "GLFW_LIBRARIES: ${GLFW_LIBRARIES}")
# message(STATUS "GLFW_INCLUDE_DIRS: ${GLFW_INCLUDE_DIRS}")

# # Add GLFW include directories explicitly (optional, but good)
# target_include_directories(osu2 PRIVATE ${GLFW_INCLUDE_DIRS})

# # Instead of relying on GLFW_LIBRARIES, specify full path to GLFW dylib manually
# # You can get this from `pkg-config --libs glfw3` which you showed is:
# #   -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw
# target_link_libraries(osu2
#     ${OPENGL_LIBRARIES}
#     pthread
#     /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.dylib
#     /opt/homebrew/lib/libsndfile.dylib
# )


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