cmake_minimum_required(VERSION 3.16)

project(Platforrmer)

# Set C flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put the game executable in /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# Setting parameters for raylib
set(BUILD_RAYLIB_CPP_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_TESTING OFF CACHE BOOL "" FORCE) # or the tests
add_subdirectory(src/thirdparty/raylib-cpp)

# Includes
set(includes
	include
	.
)
list(TRANSFORM includes PREPEND "src/")
include_directories(${includes})

set(sources
	main.cpp
	thirdparty/physac.h
)
list(TRANSFORM sources PREPEND "src/")

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} raylib)