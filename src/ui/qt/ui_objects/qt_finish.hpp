#pragma once

#include "finish.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtFinish : public Finish, public QtUIObjectRectAdapter {
		public:
			QtFinish(const Coord& top_left, const int width, const int height);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
