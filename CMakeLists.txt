cmake_minimum_required(VERSION 3.7)
project(TI)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_NAME TI)

set(SOURCE_FILES main.cpp include/TI.h src/TI.cpp include/sftools/Chronometer.hpp)
add_executable(TI ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")


find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(TI ${SFML_LIBRARIES})
endif()

find_package(sfeMovie REQUIRED)
if(SFEMOVIE_FOUND)
    include_directories(${SFEMOVIE_INCLUDE_DIR})
    target_link_libraries(TI ${SFEMOVIE_LIBRARY})
endif()