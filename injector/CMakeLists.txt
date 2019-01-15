cmake_minimum_required (VERSION 3.8)

add_executable (injector "injector.cpp")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.68 REQUIRED COMPONENTS filesystem)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(injector PRIVATE ${Boost_LIBRARIES})

find_package(Detours REQUIRED)
include_directories(${Detours_INCLUDE_DIRS})
target_link_libraries(injector PRIVATE ${Detours_LIBRARIES})