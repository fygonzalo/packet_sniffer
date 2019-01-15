cmake_minimum_required (VERSION 3.8)

add_library (sniffer SHARED 
				"sniffer.cpp"
				"hook.cpp" "hook.h"
				"logger.cpp" "logger.h"
				"util.h")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.68 REQUIRED COMPONENTS filesystem date_time)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(sniffer PRIVATE ${Boost_LIBRARIES})

find_package(Detours REQUIRED)
include_directories(${Detours_INCLUDE_DIRS})
target_link_libraries(sniffer PRIVATE ${Detours_LIBRARIES})

find_package(nlohmann_json 3.3.0 REQUIRED)
target_link_libraries(sniffer PRIVATE nlohmann_json::nlohmann_json)

target_link_libraries(sniffer PRIVATE Ws2_32.lib)