#include "qt_game_map.hpp"

#include <QCoreApplication>
#include <algorithm>

using biv::QtGameMap;

QtGameMap::QtGameMap(const int height, const int width, QtKeyboard* keyboard)
	: GameMap(height, width) {
	window = new QtGameWindow(keyboard, height, width);
}

QtGameMap::~QtGameMap() {
	delete window;
	window = nullptr;
}

void QtGameMap::add_obj(QtUIObject* obj) {
	objs.push_back(obj);
}

void QtGameMap::set_mario(Mario* m) {
	mario = m;
}

void QtGameMap::clear() noexcept {}

void QtGameMap::refresh() noexcept {
	if (window) {
		window->update_objs(objs, mario);
	}
}

void QtGameMap::remove_obj(QtUIObject* obj) {
	objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
	if (reinterpret_cast<void*>(mario) == reinterpret_cast<void*>(obj)) {
		mario = nullptr;
	}
}

void QtGameMap::remove_objs() {
	objs.clear();
	mario = nullptr;
}

void QtGameMap::show() const noexcept {
	if (window) {
		window->show();
		window->update();
	}
	QCoreApplication::processEvents();
}
