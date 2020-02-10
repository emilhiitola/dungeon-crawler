

# Check that the build does not happen in the source tree
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
   MESSAGE(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

cmake_minimum_required (VERSION 2.6)
#project (../)
set(CMAKE_CXX_STANDARD 14)
#include_directories("src")
# Set the name of the executable to be produced
set(EXECUTABLE_NAME dungeon_crawler)
# Add all .cpp - files under src/ directory
#file(GLOB SOURCES src/*.cpp)
#add_executable(${EXECUTABLE_NAME} ${SOURCES})

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
include_directories(src)
add_subdirectory(src)



# Detect and add SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
#find_package(SFML COMPONENTS network audio graphics window system)
#if(SFML_FOUND)
  #include_directories(${SFML_INCLUDE_DIR})
  #target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
#endif()
# For installing targets (not mandatory)
#install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

