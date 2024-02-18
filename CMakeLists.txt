cmake_minimum_required(VERSION 3.18.4)



# Lib

project(
	serializer
	VERSION 1.0.1
	LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	CXX_STANDARD 23
	CXX_EXTENSIONS OFF
)

target_include_directories(${PROJECT_NAME} INTERFACE
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
)
