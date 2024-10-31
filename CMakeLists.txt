cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(serialization)
add_executable(${PROJECT_NAME}
    src/main.cpp

	src/element.cpp		src/element.h
	src/gui.cpp			src/gui.h
)

include_directories(libs)

add_subdirectory(libs/ter)
target_link_libraries(${PROJECT_NAME} PRIVATE terminal)
