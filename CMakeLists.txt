cmake_minimum_required(VERSION 3.4)
project(proyecto)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(proyecto ${SOURCE_FILES})


set(CMAKE_MODULE_PATH "/home/roosevelt/Descargas/proyecto/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(proyecto ${SFML_LIBRARIES})
endif()