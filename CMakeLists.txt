cmake_minimum_required(VERSION 4.2)
project(RedUI)

set(CMAKE_CXX_STANDARD 20)

add_library(RedUI SHARED
		include/RedUI.h
		src/RedUI.cpp
		include/RedUI/UIState.h
		include/RedUI/UIObject.h
		include/RedUI/Animation.h
		include/RedUI/Math/Vec2.h
		include/RedUI/Color/RGB.h
		src/RedUI/Math/Vec2.cpp
		src/RedUI/Color/RGB.cpp
		src/RedUI/UIObject.cpp
		include/RedUI/Time/Time.h
		include/RedUI/Components/Box.h
		src/RedUI/Components/Box.cpp
		src/RedUI/UIState.cpp
		include/RedUI/Components/TextLabel.h
		src/RedUI/Components/TextLabel.cpp
		include/RedUI/Color/Dropshadow.h
		src/RedUI/Update.cpp
		src/RedUI/Color/Dropshadow.cpp
		include/RedUI/Input/Mouse.h
		src/RedUI/Input/Mouse.cpp
		include/RedUI/Event/Event.h
		include/RedUI/Event/MouseEvent.h
		include/RedUI/Update.h
		include/RedUI/Input/Key.h
		src/RedUI/Input/Key.cpp
		include/RedUI/Remove.h
		src/RedUI/Remove.cpp
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
