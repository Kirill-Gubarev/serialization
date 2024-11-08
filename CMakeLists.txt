cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(serialization)
add_executable(${PROJECT_NAME}
    src/main.cpp
	src/app.cpp				src/app.h
)
include_directories(src)

add_library(ter STATIC
    src/ter/color.h
    src/ter/key.h

    src/ter/keyEvents.cpp	src/ter/keyEvents.h
    src/ter/terminal.cpp	src/ter/terminal.h
    src/ter/tHandler.cpp	src/ter/tHandler.h
)
add_library(ser STATIC
	src/ser/ser.cpp			src/ser/ser.h
)
add_library(gui STATIC
	src/gui/gCode.h

	src/gui/element.cpp		src/gui/element.h
	src/gui/gui.cpp			src/gui/gui.h
	src/gui/guiDefault.cpp	src/gui/guiDefault.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE gui)
target_link_libraries(gui PRIVATE ter)
target_link_libraries(gui PRIVATE ser)
