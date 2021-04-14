cmake_minimum_required(VERSION 3.16)

project(Platforrmer)

# Set C flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Put the game executable in /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# required
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

# Includes
set(includes
	include
)
list(TRANSFORM includes PREPEND "src/")
include_directories(${includes})

set(sources
	main.cpp
	glad.c
)
list(TRANSFORM sources PREPEND "src/")

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL dl)