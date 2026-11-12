#include "qt_game_window.hpp"

#include <QCloseEvent>
#include <QFont>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <algorithm>

#include "mario.hpp"
#include "qt_keyboard.hpp"
#include "qt_sprite_manager.hpp"
#include "qt_ui_obj.hpp"

using biv::QtGameWindow;

QtGameWindow::QtGameWindow(
	QtKeyboard* keyboard, int map_height, int map_width, QWidget* parent
) : QWidget(parent),
    keyboard(keyboard),
    map_height(map_height),
    map_width(map_width) {

	setWindowTitle("Super Mario");
	resize(1200, 720);
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_OpaquePaintEvent, true);
}

void QtGameWindow::update_objs(
	const std::vector<QtUIObject*>& new_objs, Mario* new_mario
) {
	objs = new_objs;
	mario = new_mario;
}

void QtGameWindow::paintEvent(QPaintEvent* /*event*/) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::SmoothPixmapTransform, false);

	const int tile_size = (map_height > 0) ? (height() / map_height) : 24;

	int mario_x = 39;
	if (mario != nullptr) {
		mario_x = mario->get_rect().get_left();
	}

	// Камера следит за Марио так, чтобы перед ним было видно препятствия
	int camera_x = std::max(0, mario_x - 18);
	int camera_y = 0;

	// 1. Небо (аутентичный небесно-голубой цвет NES Super Mario Bros)
	painter.fillRect(rect(), QColor(92, 148, 252));

	// 2. Облака и декорации
	const QPixmap& cloud = QtSpriteManager::instance().get_sprite("cloud");
	const QPixmap& bush = QtSpriteManager::instance().get_sprite("bush");

	if (!cloud.isNull()) {
		int cloud_w = 4 * tile_size;
		int cloud_h = 2 * tile_size;
		for (int cx = 10; cx < map_width; cx += 28) {
			int sx = (cx - camera_x) * tile_size;
			painter.drawPixmap(sx, 3 * tile_size, cloud_w, cloud_h, cloud);
		}
	}

	if (!bush.isNull()) {
		int bush_w = 4 * tile_size;
		int bush_h = 2 * tile_size;
		for (int bx = 22; bx < map_width; bx += 36) {
			int sx = (bx - camera_x) * tile_size;
			painter.drawPixmap(sx, (map_height - 5) * tile_size, bush_w, bush_h, bush);
		}
	}

	// 3. Объекты уровня
	for (QtUIObject* obj : objs) {
		if (obj != nullptr) {
			obj->draw(painter, tile_size, camera_x, camera_y);
		}
	}

	// 4. Вода внизу (строки от map_height - 3 до map_height)
	int sea_top_tile = map_height - 3;
	int sea_screen_y = (sea_top_tile - camera_y) * tile_size;
	if (sea_screen_y < height()) {
		int sea_h = height() - sea_screen_y;
		painter.fillRect(0, sea_screen_y, width(), sea_h, QColor(32, 56, 236));
		// Белая пена на гребне волны
		painter.fillRect(0, sea_screen_y, width(), 3, QColor(255, 255, 255, 200));
	}

	// 5. Ретро HUD
	painter.setPen(Qt::white);
	QFont hud_font("Arial", 12, QFont::Bold);
	painter.setFont(hud_font);
	painter.drawText(30, 30, "MARIO");
	painter.drawText(220, 30, "WORLD 1-1");
	painter.drawText(width() - 140, 30, "TIME");
}

void QtGameWindow::keyPressEvent(QKeyEvent* event) {
	if (keyboard) {
		keyboard->handle_key_press(event->key(), event->isAutoRepeat());
	}
	QWidget::keyPressEvent(event);
}

void QtGameWindow::keyReleaseEvent(QKeyEvent* event) {
	if (keyboard) {
		keyboard->handle_key_release(event->key(), event->isAutoRepeat());
	}
	QWidget::keyReleaseEvent(event);
}

void QtGameWindow::closeEvent(QCloseEvent* event) {
	if (keyboard) {
		keyboard->handle_close();
	}
	QWidget::closeEvent(event);
}
