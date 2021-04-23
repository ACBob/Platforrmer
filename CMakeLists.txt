cmake_minimum_required(VERSION 3.16)

project(Platforrmer)

# Set C flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-missing-field-initializers")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Put the game executable in /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
add_subdirectory(src/thirdparty/raylib)

# Setting parameters for box2d
set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE) # don't build the supplied tests
set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "" FORCE) # or the testbed
add_subdirectory(src/thirdparty/box2d)

# Includes
set(includes
	headers
	thirdparty/box2d/include
	thirdparty
)
list(TRANSFORM includes PREPEND "src/")
include_directories(${includes})

set(sources
	main.cpp
	material.cpp
	entities.cpp
	b2debugdraw.cpp
	levelload.cpp

	# Loguru
	thirdparty/loguru.cpp
	thirdparty/loguru.hpp
)
list(TRANSFORM sources PREPEND "src/")

add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} raylib pthread box2d dl)