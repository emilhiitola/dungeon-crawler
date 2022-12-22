

# Check that the build does not happen in the source tree
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   MESSAGE(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

cmake_minimum_required (VERSION 3.1)
project(dungeon_crawler)
set(CMAKE_CXX_STANDARD 14)
#include_directories("src")
# Set the name of the executable to be produced
set(EXECUTABLE_NAME dungeon_crawler)
# Add all .cpp - files under src/ directory
#file(GLOB SOURCES src/*.cpp)
#add_executable(${EXECUTABLE_NAME} ${SOURCES})
#file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)
#message(${SOURCES})
#set(SOURCES ${SOURCES})

add_executable(${EXECUTABLE_NAME}
  src/main.cpp
  src/character.hpp
  src/character.cpp
  src/craftable.hpp
  src/craftable.cpp
  src/direction.hpp
  src/enumtypes.hpp
  src/game.hpp
  src/game.cpp
  src/inventory.hpp
  src/inventory.cpp
  src/inventoryexceptions.hpp
  src/item.hpp
  src/item.cpp
  src/map.hpp
  src/map.cpp
  src/monster.hpp
  src/monster.cpp
  src/player.hpp
  src/player.cpp
  src/potion.hpp
  src/potion.cpp
  src/renderer.hpp
  src/renderer.cpp
  src/room.hpp
  src/room.cpp
  src/tile.hpp
  src/tile.cpp
  src/weapon.hpp
  src/weapon.cpp
)


#enable_testing() 

#add_executable(tester test/tester.cpp)
#add_test(NAME tester
#COMMAND tester)


# Add 3rd party library include directory
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/3rdpartylibs/libname/include)

# Add subdirectories (in order of dependencies)
# As told before, these directories should have their own CMakeLists.txt files!
#ADD_SUBDIRECTORY(include)
#ADD_SUBDIRECTORY(apps)
#ADD_SUBDIRECTORY(RAN)
#include_directories(src)

#EDIT THIS 
set(SFML_DIR "/SFML/SFML-2.5.1-minGW/lib/cmake/SFML")

find_package(SFML COMPONENTS audio graphics window)

target_link_libraries(${EXECUTABLE_NAME} PRIVATE sfml-audio sfml-graphics sfml-window)
#
#add_subdirectory(src)

#add_executable(${EXECUTABLE_NAME} src/main.cpp)


# Detect and add SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
#find_package(SFML 2.5.1 COMPONENTS network audio graphics window system REQUIRED)


#if(SFML_FOUND)
  #include_directories(${SFML_INCLUDE_DIR})
  #target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#endif()
# For installing targets (not mandatory)
#install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

