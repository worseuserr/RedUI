cmake_minimum_required(VERSION 4.2)
project(RedUI)

set(CMAKE_CXX_STANDARD 20)

function(distribute TARGET FILE)
	if (EXISTS "${FILE}")
		add_custom_command(TARGET ${TARGET} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				"${FILE}"
				"${CMAKE_CURRENT_SOURCE_DIR}/bin/"
		)
	endif ()
endfunction()

# +-+-+-+-+-+-
# Main Library
# +-+-+-+-+-+-

add_library(RedUI SHARED
		include/RedUI.h
		src/RedUI.cpp
		include/RedUI/Object/UIObject.h
		include/RedUI/Graphics/Animation.h
		include/RedUI/Math/Vec2.h
		include/RedUI/Graphics/RGB.h
		src/RedUI/Math/Vec2.cpp
		src/RedUI/Graphics/RGB.cpp
		src/RedUI/Object/UIObject.cpp
		include/RedUI/Time/Time.h
		include/RedUI/Components/Box.h
		src/RedUI/Components/Box.cpp
		include/RedUI/Components/TextLabel.h
		src/RedUI/Components/TextLabel.cpp
		include/RedUI/Graphics/Dropshadow.h
		src/RedUI/Graphics/Dropshadow.cpp
		include/RedUI/Input/Mouse.h
		src/RedUI/Input/Mouse.cpp
		include/RedUI/Event/Event.h
		include/RedUI/Input/Key.h
		src/RedUI/Input/Key.cpp
		include/RedUI/Object/Create.h
		include/RedUI/Graphics/Sprite.h
		src/RedUI/Graphics/Sprite.cpp
		include/RedUI/Focus.h
		src/RedUI/Focus.cpp
		include/RedUI/Runtime.h
		src/RedUI/Runtime.cpp
		src/RedUI/Graphics/Animation.cpp
		include/RedUI/UIComponent.h
		src/RedUI/Object/Create.cpp
		include/RedUI/Input/Screen.h
		src/RedUI/Input/Screen.cpp
		include/RedUI/Math/Angle.h
		src/RedUI/Math/Angle.cpp
		include/RedUI/IO/File.h
		src/RedUI/IO/File.cpp
		include/RedUI/IO/Logger.h
		src/RedUI/IO/Logger.cpp
		src/RedUI/Time/Time.cpp
		include/RedUI/Debug.h
		src/RedUI/Debug.cpp
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

target_link_libraries(RedUI PRIVATE ScriptHookRDR2.lib Dbghelp)

set_target_properties(RedUI PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
		WINDOWS_EXPORT_ALL_SYMBOLS ON
		SUFFIX ".asi"
)

# +-+-+-+-+-+-
# DllMain Runtime
# +-+-+-+-+-+-

add_library(RedUIRuntime SHARED
		src/DllMain.cpp
)

target_include_directories(RedUIRuntime PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/sdk/inc
)

target_link_directories(RedUIRuntime PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/sdk/lib
)

target_compile_options(RedUIRuntime PRIVATE
		/EHsc
		/O2
)

target_link_libraries(RedUIRuntime PRIVATE RedUI ScriptHookRDR2.lib)

set_target_properties(RedUIRuntime PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
		ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
		WINDOWS_EXPORT_ALL_SYMBOLS ON
		SUFFIX ".asi"
)

# +-+-+-+-+-+-
# Distrib
# +-+-+-+-+-+-

add_custom_command(TARGET RedUI POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E make_directory
		"${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

distribute(RedUI "${CMAKE_CURRENT_BINARY_DIR}/bin/RedUI.asi")
distribute(RedUI "${CMAKE_CURRENT_BINARY_DIR}/bin/RedUI.lib")
distribute(RedUI "${CMAKE_CURRENT_BINARY_DIR}/bin/RedUI.pdb")
distribute(RedUIRuntime "${CMAKE_CURRENT_BINARY_DIR}/bin/RedUIRuntime.asi")
distribute(RedUIRuntime "${CMAKE_CURRENT_BINARY_DIR}/bin/RedUIRuntime.pdb")
