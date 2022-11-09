cmake_minimum_required(VERSION 3.9)

project(Interp3D)

include_directories(include)
file(GLOB_RECURSE Interp3D_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)
file(GLOB_RECURSE Interp3D_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src" *.cpp)

add_library(
	Interp3D
	${Interp3D_INCLUDE}
	${Interp3D_SRC}
)
target_include_directories (Interp3D PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)