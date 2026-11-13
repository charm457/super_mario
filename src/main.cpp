/**
	Игровой цикл — обобщённое представление потока событий в игре.
	1. Установка параметров игры
	2. Получение пользовательского ввода
	3. Обновление внутреннего состояния игры
	4. Обновление изображения на экране
	5. Проверка, не окончена ли игра (если нет — в п.2)
	6. Завершение
*/
#include <thread>
#include <chrono>

#include "first_level.hpp"
#include "game.hpp"
#include "game_level.hpp"
#include "game_map.hpp"
#include "keyboard.hpp"
#include "mario.hpp"
#include "os_control_settings.hpp"
#include "ui_factory.hpp"
#include "app_factory.hpp"

#ifdef QT_GUI
    #include "qt_factory.hpp"
    #include "qt_keyboard.hpp"
    #include "qt_ui_factory.hpp"
#elif defined(WINDOWS_CONSOLE)
    #include "windows_factory.hpp"
    #include "console_ui_factory.hpp"
#elif defined(LINUX_CONSOLE)
    #include "linux_factory.hpp"
    #include "console_ui_factory.hpp"
    #include "ncurses.h"
#endif

using namespace std::chrono_literals;

int main(int argc, char* argv[]) {
    const int map_height = 30;
    const int map_weight = 200;

    biv::AppFactory* app_factory = nullptr;
#ifdef QT_GUI
    app_factory = new biv::QTFactory(argc, argv);
#elif defined(WINDOWS_CONSOLE)
    app_factory = new biv::WindowsAppFactory();
#elif defined(LINUX_CONSOLE)
    app_factory = new biv::LinuxAppFactory(map_height, map_weight);
#endif

    biv::OSControlSettings* control_settings = app_factory->create_control_settings();
    biv::KeyBoard* keyboard = app_factory->create_keyboard();
    auto frame_delay = app_factory->get_frame_delay();

    control_settings->init();
    keyboard->on();

    biv::Game game;

#ifdef QT_GUI
    biv::UIFactory* ui_factory = new biv::QtUIFactory(
        &game,
        dynamic_cast<biv::QtKeyboard*>(keyboard)
    );
#else
    biv::UIFactory* ui_factory = new biv::ConsoleUIFactory(&game);
#endif

    biv::GameMap* game_map = ui_factory->get_game_map(map_height, map_weight);
    biv::GameLevel* game_level = new biv::FirstLevel(ui_factory);
    biv::Mario* mario = ui_factory->get_mario();

    biv::UserInput user_input;
    do {
        user_input = keyboard->get_user_input();
        switch (user_input) {
            case biv::UserInput::MAP_LEFT:
                mario->move_map_left();
                if (!game.check_static_collisions(mario)) {
                    game.move_map_left();
                }
                mario->move_map_right();
                break;
            case biv::UserInput::MAP_RIGHT:
                mario->move_map_right();
                if (!game.check_static_collisions(mario)) {
                    game.move_map_right();
                }
                mario->move_map_left();
                break;
            case biv::UserInput::MARIO_JUMP:
                mario->jump();
                break;
            case biv::UserInput::EXIT:
                game.finish();
                break;
        }

        game.move_objs_horizontally();
        game.check_horizontally_static_collisions();

        game.move_objs_vertically();
        game.check_mario_collision();
        game.check_vertically_static_collisions();
        game.check_moving_platform_collisions();
        game.check_finish();

        if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
            keyboard->off();
            keyboard->on();
            game_level->restart();
            mario = ui_factory->get_mario();
            std::this_thread::sleep_for(1000ms);
        }

        if (game.is_level_end()) {
            if (!game_level->is_final()) {
                game_level = game_level->get_next();
                mario = ui_factory->get_mario();
                std::this_thread::sleep_for(1000ms);
                keyboard->off();
                keyboard->on();
                game.start_level();
            } else {
                game.finish();
            }
        }

        game_map->refresh();
        control_settings->set_cursor_start_position();
        game_map->show();
        std::this_thread::sleep_for(frame_delay);
    } while (!game.is_finished());

    delete game_level;
    delete game_map;
    delete ui_factory;
    delete keyboard;
    delete control_settings;
    delete app_factory;
    return 0;
}