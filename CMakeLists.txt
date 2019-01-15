cmake_minimum_required (VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

project ("packet_sniffer")

add_subdirectory ("injector")
add_subdirectory ("sniffer")
