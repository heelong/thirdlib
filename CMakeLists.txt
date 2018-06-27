project (stdlib)

cmake_minimum_required (VERSION 2.4.6)
if(WIN32)
else(WIN32)
	SET( CMAKE_CXX_FLAGS "-std=c++11 -O3")
endif(WIN32)
if(COMMAND cmake_policy)
     cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PCL 1.2 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(stdlib navi_stdlib.h navi_stdlib.cpp 
					  athena_lib.h athena_lib.cpp
					  mytime.h mytime.cpp
					  main.cpp)
target_link_libraries(stdlib  ${PCL_LIBRARIES})