project(Platforrmer)

# Set C flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Put the game executable in /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Includes
include_directories(
	${PROJECT_SOURCE_DIR}/include
)

set(sources
	main.cpp
)

add_executable(${PROJECT_NAME} ${sources})