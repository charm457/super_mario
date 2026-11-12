#pragma once

#include "full_box.hpp"
#include "qt_ui_obj_rect_adapter.hpp"

namespace biv {
	class UIFactory;

	class QtFullBox : public FullBox, public QtUIObjectRectAdapter {
		public:
			QtFullBox(
				const Coord& top_left,
				const int width,
				const int height,
				UIFactory* ui_factory
			);

			void draw(QPainter& painter, int tile_size, int camera_x, int camera_y) const override;
	};
}
