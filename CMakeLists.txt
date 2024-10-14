cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(serialization)
add_executable(${PROJECT_NAME}
    src/main.cpp

	src/color.h
	src/key.h

	src/element.cpp		src/element.h
	src/gui.cpp			src/gui.h
	src/keyEvents.cpp	src/keyEvents.h

	src/terminal.cpp	src/terminal.h
	src/tHandler.cpp	src/tHandler.h
)
