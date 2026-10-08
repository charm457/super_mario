#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "finish.hpp"

namespace biv {
	class ConsoleFinish : public Finish, public ConsoleUIObjectRectAdapter {
		public:
			ConsoleFinish(const Coord& top_left, const int width, const int height);

			char get_brush() const noexcept override;
	};
}