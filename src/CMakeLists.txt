cmake_minimum_required(VERSION 3.2...3.27.5)

project(super_mario)

SET(CMAKE_CXX_FLAGS "-finput-charset=utf-8 -fexec-charset=utf-8")

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

if(GAME_TYPE STREQUAL "Qt")
	target_sources(${PROJECT_NAME} PRIVATE qt_factory.cpp)
	find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
	find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)
	set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC ON AUTORCC ON AUTOUIC ON)
	target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
	target_compile_definitions(${PROJECT_NAME} PRIVATE QT_GUI)
endif()

add_subdirectory(os_controls)
add_subdirectory(controller)
add_subdirectory(levels)
add_subdirectory(model)
add_subdirectory(objects)
add_subdirectory(ui)
add_subdirectory(util)

if(GAME_TYPE STREQUAL "WindowsConsole")
	target_sources(${PROJECT_NAME} PRIVATE windows_factory.cpp)
	target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS_CONSOLE)
elseif(GAME_TYPE STREQUAL "LinuxConsole")
	target_sources(${PROJECT_NAME} PRIVATE linux_factory.cpp)
	target_link_libraries(${PROJECT_NAME} ncurses pthread)
	target_compile_definitions(${PROJECT_NAME} PRIVATE LINUX_CONSOLE)
endif()
