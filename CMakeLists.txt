#CMakelists shamelessly based on shared files in the discord


project(vleesjongen)
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)


# The program we're compiling with the sources set above
add_executable( vleesjongen src/game.cpp src/game.h src/main.cpp src/clock.cpp src/clock.h src/models/model.cpp src/models/model.h src/observer.h
        src/object.cpp src/object.h src/events/adjust.cpp src/events/adjust.h src/events/baseevent.cpp src/events/baseevent.h
        src/models/jongenmodel.cpp src/models/jongenmodel.h src/position.cpp src/position.h src/controllers/controller.cpp
        src/controllers/controller.h src/controllers/jongencontroller.cpp
        src/controllers/jongencontroller.h src/events/sfmlevent.cpp src/events/sfmlevent.h src/events/moveevent.cpp src/events/moveevent.h
        src/screen.cpp src/screen.h src/events/jongenmovedevent.cpp src/events/jongenmovedevent.h src/botser.cpp src/botser.h
        src/projectiescherm.cpp src/projectiescherm.h src/events/touchside.cpp src/events/touchside.h
        src/events/touchabove.h src/events/goaltouch.h src/events/touchbelow.h src/events/jongendood.h src/models/movablemodel.cpp src/models/movingblokmodel.h src/models/movingstekelmodel.h src/events/movablemovedevent.h src/events/movablemovedevent.cpp src/models/portaalmodel.cpp src/events/portaalevent.cpp src/events/portaalevent.h)

# Extend the CMake module path to find the FindSFML.cmake
# file in {project root}/cmake/Modules
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")


# Look for SFML >= 2.0, with the specific subcomponents listed below
FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)

# Add include dirs for SFML
# (The SFML_INCLUDE_DIR variable is defined by FindSFML.cmake, if SFML was found)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})


# Link target to SFML libs
# (The SFML_LIBRARIES variable is defined by FindSFML.cmake, if SFML was found)
TARGET_LINK_LIBRARIES(vleesjongen ${SFML_LIBRARIES})

INSTALL(TARGETS vleesjongen DESTINATION ${PROJECT_SOURCE_DIR}/bin)
