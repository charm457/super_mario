#include "qt_box.hpp"

#include <QPainter>
#include "qt_sprite_manager.hpp"

using biv::QtBox;

QtBox::QtBox(const Coord& top_left, const int width, const int height)
	: Box(top_left, width, height),
	  QtUIObjectRectAdapter(top_left, width, height) {}

void QtBox::draw(
	QPainter& painter, int tile_size, int camera_x, int camera_y
) const {
	int screen_x = (get_left() - camera_x) * tile_size;
	int screen_y = (get_top() - camera_y) * tile_size;

	const QPixmap& sprite = QtSpriteManager::instance().get_sprite("box");
	for (int i = 0; i < get_width(); ++i) {
		for (int j = 0; j < get_height(); ++j) {
			painter.drawPixmap(
				screen_x + i * tile_size,
				screen_y + j * tile_size,
				tile_size,
				tile_size,
				sprite
			);
		}
	}
}
