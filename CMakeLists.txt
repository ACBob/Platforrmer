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
include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set(sources
	main.cpp
)

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)