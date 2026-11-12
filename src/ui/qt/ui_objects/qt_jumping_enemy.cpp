#include "qt_jumping_enemy.hpp"

#include <QPainter>
#include "qt_sprite_manager.hpp"

using biv::QtJumpingEnemy;

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, const int width, const int height)
	: JumpingEnemy(top_left, width, height),
	  QtUIObjectRectAdapter(top_left, width, height) {}

void QtJumpingEnemy::draw(
	QPainter& painter, int tile_size, int camera_x, int camera_y
) const {
	int screen_x = (get_left() - camera_x) * tile_size;
	int screen_y = (get_top() - camera_y) * tile_size;
	int w = get_width() * tile_size;
	int h = get_height() * tile_size;

	const QPixmap& sprite = QtSpriteManager::instance().get_sprite("jumping_enemy");
	painter.drawPixmap(screen_x, screen_y, w, h, sprite);
}
