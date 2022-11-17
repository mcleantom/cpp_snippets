cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_FLAGS "-O3")
project(Graph)

include_directories(include)
file(GLOB_RECURSE Graph_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include" *.h)

add_library(
	Graph
	OBJECT
	${Graph_INCLUDE}
)
set_target_properties(Graph PROPERTIES LINKER_LANGUAGE CXX)

add_executable(graph_example "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

target_link_libraries(
	graph_example
	PUBLIC
	Graph
)