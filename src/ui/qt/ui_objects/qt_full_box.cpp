#include "qt_full_box.hpp"

#include <QPainter>
#include "qt_sprite_manager.hpp"

using biv::QtFullBox;

QtFullBox::QtFullBox(
	const Coord& top_left,
	const int width,
	const int height,
	UIFactory* ui_factory
) : FullBox(top_left, width, height, ui_factory),
    QtUIObjectRectAdapter(top_left, width, height) {}

void QtFullBox::draw(
	QPainter& painter, int tile_size, int camera_x, int camera_y
) const {
	int screen_x = (get_left() - camera_x) * tile_size;
	int screen_y = (get_top() - camera_y) * tile_size;

	const std::string sprite_name = is_active_ ? "full_box" : "empty_box";
	const QPixmap& sprite = QtSpriteManager::instance().get_sprite(sprite_name);

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
