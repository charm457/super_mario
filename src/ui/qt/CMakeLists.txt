target_sources(${PROJECT_NAME}
	PRIVATE
		qt_control_settings.cpp
		qt_game_map.cpp
		qt_game_window.cpp
		qt_keyboard.cpp
		qt_sprite_manager.cpp
		qt_ui_factory.cpp
		qt_ui_obj_rect_adapter.cpp
		resources.qrc
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(ui_objects)
