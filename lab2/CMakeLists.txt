cmake_minimum_required(VERSION 3.10)
project(1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(LibXML++ REQUIRED)
include_directories(${LibXML++_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibXML++_LIBRARIES})

configure_file(weather.xml weather.xml COPYONLY)
configure_file(exchange_rate.xml exchange_rate.xml COPYONLY)

add_executable(1 main.cpp)

target_link_libraries(1 ${LIBS})