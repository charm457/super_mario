#include "qt_ui_factory.hpp"

using biv::QtUIFactory;

QtUIFactory::QtUIFactory(Game* game, QtKeyboard* keyboard)
	: UIFactory(game), keyboard(keyboard) {}

QtUIFactory::~QtUIFactory() {
	delete mario;
	mario = nullptr;
}

void QtUIFactory::clear_data() {
	game->remove_objs();
	if (game_map) {
		game_map->remove_objs();
	}
	delete mario;
	mario = nullptr;
	boxes.clear();
	full_boxes.clear();
	ships.clear();
	enemies.clear();
	finishes.clear();
	moneys.clear();
	flying_enemies.clear();
	jumping_enemies.clear();
	moving_platforms.clear();
}

void QtUIFactory::create_box(
	const Coord& top_left, const int width, const int height
) {
	QtBox* box = new QtBox(top_left, width, height);
	boxes.push_back(box);
	game->add_map_movable(box);
	game->add_static_obj(box);
	if (game_map) {
		game_map->add_obj(box);
	}
}

void QtUIFactory::create_enemy(
	const Coord& top_left, const int width, const int height
) {
	QtEnemy* enemy = new QtEnemy(top_left, width, height);
	enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	if (game_map) {
		game_map->add_obj(enemy);
	}
}

void QtUIFactory::create_finish(
	const Coord& top_left, const int width, const int height
) {
	QtFinish* finish = new QtFinish(top_left, width, height);
	finishes.push_back(finish);
	game->add_map_movable(finish);
	game->add_finish(finish);
	if (game_map) {
		game_map->add_obj(finish);
	}
}

void QtUIFactory::create_flying_enemy(
	const Coord& top_left, const int width, const int height
) {
	QtFlyingEnemy* enemy = new QtFlyingEnemy(top_left, width, height);
	flying_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	if (game_map) {
		game_map->add_obj(enemy);
	}
}

void QtUIFactory::create_jumping_enemy(
	const Coord& top_left, const int width, const int height
) {
	QtJumpingEnemy* enemy = new QtJumpingEnemy(top_left, width, height);
	jumping_enemies.push_back(enemy);
	game->add_map_movable(enemy);
	game->add_movable(enemy);
	game->add_collisionable(enemy);
	if (game_map) {
		game_map->add_obj(enemy);
	}
}

void QtUIFactory::create_moving_platform(
	const Coord& top_left, const int width, const int height
) {
	QtMovingPlatform* platform = new QtMovingPlatform(top_left, width, height);
	moving_platforms.push_back(platform);
	game->add_map_movable(platform);
	game->add_movable(platform);
	game->add_moving_platform(platform);
	if (game_map) {
		game_map->add_obj(platform);
	}
}

void QtUIFactory::create_full_box(
	const Coord& top_left, const int width, const int height
) {
	QtFullBox* full_box = new QtFullBox(top_left, width, height, this);
	full_boxes.push_back(full_box);
	game->add_collisionable(full_box);
	game->add_map_movable(full_box);
	game->add_static_obj(full_box);
	if (game_map) {
		game_map->add_obj(full_box);
	}
}

void QtUIFactory::create_mario(
	const Coord& top_left, const int width, const int height
) {
	game->remove_collisionable(mario);
	game->remove_movable(mario);
	game->remove_mario();
	if (game_map) {
		game_map->remove_obj(mario);
	}
	delete mario;
	mario = nullptr;

	mario = new QtMario(top_left, width, height);
	game->add_collisionable(mario);
	game->add_movable(mario);
	game->add_mario(mario);
	if (game_map) {
		game_map->add_obj(mario);
		game_map->set_mario(mario);
	}
}

void QtUIFactory::create_money(
	const Coord& top_left, const int width, const int height
) {
	QtMoney* money = new QtMoney(top_left, width, height);
	moneys.push_back(money);
	game->add_map_movable(money);
	game->add_movable(money);
	game->add_collisionable(money);
	if (game_map) {
		game_map->add_obj(money);
	}
}

void QtUIFactory::create_ship(
	const Coord& top_left, const int width, const int height
) {
	QtShip* ship = new QtShip(top_left, width, height);
	ships.push_back(ship);
	game->add_map_movable(ship);
	game->add_static_obj(ship);
	if (game_map) {
		game_map->add_obj(ship);
	}
}

biv::GameMap* QtUIFactory::get_game_map(const int height, const int width) {
	if (game_map == nullptr) {
		game_map = new QtGameMap(height, width, keyboard);
		if (mario != nullptr) {
			game_map->add_obj(mario);
			game_map->set_mario(mario);
		}
	}
	return game_map;
}

biv::Mario* QtUIFactory::get_mario() {
	return mario;
}
