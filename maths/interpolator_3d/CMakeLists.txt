cmake_minimum_required(VERSION 3.10)
project(Interp3D)


file(GLOB_RECURSE Interp3D_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB_RECURSE Interp3D_SRC ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
add_library(
	Interp3D
	${Interp3D_INCLUDE}
	${Interp3D_SRC}
)
add_executable(test_interp ${Interp3D_INCLUDE} ${Interp3D_SRC})