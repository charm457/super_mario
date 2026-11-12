#pragma once

#include "ship.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtShip : public Ship, public QtUIObjectRectAdapter {
		public:
			QtShip(const Coord& top_left, const int width, const int height);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
