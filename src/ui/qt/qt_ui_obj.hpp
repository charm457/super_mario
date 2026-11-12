#pragma once

class QPainter;

namespace biv {
	class QtUIObject {
		public:
			virtual ~QtUIObject() = default;

			virtual int get_bottom() const noexcept = 0;
			virtual int get_height() const noexcept = 0;
			virtual int get_left() const noexcept = 0;
			virtual int get_right() const noexcept = 0;
			virtual int get_top() const noexcept = 0;
			virtual int get_width() const noexcept = 0;

			virtual void draw(QPainter& painter, int tile_size, int camera_x = 0, int camera_y = 0) const = 0;
	};
}
