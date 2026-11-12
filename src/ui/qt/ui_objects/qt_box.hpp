#pragma once

#include "box.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtBox : public Box, public QtUIObjectRectAdapter {
		public:
			QtBox(const Coord& top_left, const int width, const int height);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
