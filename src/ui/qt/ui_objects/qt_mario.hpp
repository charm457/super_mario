#pragma once

#include "mario.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class QtMario : public Mario, public QtUIObjectRectAdapter {
		public:
			QtMario(const Coord& top_left, const int width, const int height);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
