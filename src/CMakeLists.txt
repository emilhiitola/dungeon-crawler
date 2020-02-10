set(BINARY ${EXECUTABLE_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${SOURCES})

add_executable(run ${SOURCES})

add_library(${BINARY}_lib STATIC ${SOURCES})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML COMPONENTS network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(run ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
# For installing targets (not mandatory)
install (TARGETS run DESTINATION bin)
