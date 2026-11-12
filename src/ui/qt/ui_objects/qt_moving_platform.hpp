#pragma once

#include "moving_platform.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtMovingPlatform : public MovingPlatform, public QtUIObjectRectAdapter {
		public:
			QtMovingPlatform(const Coord& top_left, int width, int height);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
