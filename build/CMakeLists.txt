cmake_minimum_required(VERSION 2.8.3)
project( PFace )

# Set version number
set (PFace_VERSION_MAJOR 1)
set (PFace_VERSION_MINOR 0)

# User c++11
set (CMAKE_CXX_STANDARD 11)

# Include opencv minimum
find_package(OpenCV 3.3.1 REQUIRED)

file(GLOB_RECURSE PFace_SOURCES "../src/*.cpp")
file(GLOB_RECURSE PFace_HEADERS "../incldue/*.h")
include_directories( ${OpenCV_INCLUDE_DIRS} "../include/" "../src/")

set (PFace_INCLUDE_DIRS "")
foreach (_headerFile ${PFace_HEADERS})
	    get_filename_component(_dir ${_headerFile} PATH)
	        list (APPEND PFace_INCLUDE_DIRS ${_dir})
endforeach()

list(REMOVE_DUPLICATES PFace_INCLUDE_DIRS)

add_executable (PFace ${PFace_SOURCES})
target_link_libraries(PFace ${OpenCV_LIBRARIES})
target_include_directories(PFace PRIVATE ${PFace_INCLUDE_DIRS})
