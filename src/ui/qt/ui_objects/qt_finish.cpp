#include "qt_finish.hpp"

#include <QPainter>
#include "qt_sprite_manager.hpp"

using biv::QtFinish;

QtFinish::QtFinish(const Coord& top_left, const int width, const int height)
	: Finish(top_left, width, height),
	  QtUIObjectRectAdapter(top_left, width, height) {}

void QtFinish::draw(
	QPainter& painter, int tile_size, int camera_x, int camera_y
) const {
	int screen_x = (get_left() - camera_x) * tile_size;
	int screen_y = (get_top() - camera_y) * tile_size;
	int w = get_width() * tile_size;
	int h = get_height() * tile_size;

	const QPixmap& sprite = QtSpriteManager::instance().get_sprite("finish");
	painter.drawPixmap(screen_x, screen_y, w, h, sprite);
}
