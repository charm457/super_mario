#include "qt_keyboard.hpp"

#include <QCoreApplication>
#include <Qt>

using biv::QtKeyboard;
using biv::UserInput;

UserInput QtKeyboard::get_user_input() {
	QCoreApplication::processEvents();

	if (!is_active) {
		return UserInput::NO_INPUT;
	}

	if (window_closed || pressed_keys.count(Qt::Key_Q) || pressed_keys.count(Qt::Key_Escape)) {
		return UserInput::EXIT;
	}

	if (jump_requested) {
		jump_requested = false;
		return UserInput::MARIO_JUMP;
	}

	if (pressed_keys.count(Qt::Key_A) || pressed_keys.count(Qt::Key_Left)) {
		return UserInput::MAP_RIGHT;
	}

	if (pressed_keys.count(Qt::Key_D) || pressed_keys.count(Qt::Key_Right)) {
		return UserInput::MAP_LEFT;
	}

	return UserInput::NO_INPUT;
}

void QtKeyboard::on() {
	is_active = true;
}

void QtKeyboard::off() {
	is_active = false;
	pressed_keys.clear();
	jump_requested = false;
}

void QtKeyboard::handle_key_press(int key, bool is_auto_repeat) {
	pressed_keys.insert(key);
	if (key == Qt::Key_Space || key == Qt::Key_W || key == Qt::Key_Up) {
		jump_requested = true;
	}
}

void QtKeyboard::handle_key_release(int key, bool is_auto_repeat) {
	if (!is_auto_repeat) {
		pressed_keys.erase(key);
	}
}

void QtKeyboard::handle_close() {
	window_closed = true;
}
