cmake_minimum_required(VERSION 4.2)
project(RedUI)

set(CMAKE_CXX_STANDARD 20)

include_directories(
		include
		sdk/inc
)

link_directories(
		sdk/lib
)

add_library(RedUI SHARED
		include/RedUI.h
		src/RedUI.cpp
)

target_compile_options(RedUI PRIVATE
		/EHsc
		/O2
)

target_link_libraries(RedUI PRIVATE ScriptHookRDR2.lib)

set_target_properties(RedUI PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
		ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)
