cmake_minimum_required(VERSION 4.2)
project(RedUI)

set(CMAKE_CXX_STANDARD 20)

add_library(RedUI SHARED
		include/RedUI.h
		src/RedUI.cpp
		include/RedUI/Menu.h
		include/RedUI/UIState.h
		include/RedUI/UIObject.h
		include/RedUI/Animation.h
		include/RedUI/Math/Vec3.h
		include/RedUI/Color/RGB.h
		src/RedUI/Math/Vec3.cpp
		src/RedUI/Color/RGB.cpp
		src/RedUI/UIObject.cpp
)

target_include_directories(RedUI PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/sdk/inc
)

target_link_directories(RedUI PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/sdk/lib
)

target_compile_options(RedUI PRIVATE
		/EHsc
		/O2
)

target_link_libraries(RedUI PRIVATE ScriptHookRDR2.lib)

set_target_properties(RedUI PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
		ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
		WINDOWS_EXPORT_ALL_SYMBOLS ON
)
