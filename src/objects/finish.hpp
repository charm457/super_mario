#pragma once

#include "rect_map_movable_adapter.hpp"

namespace biv {

	class Finish : public RectMapMovableAdapter {
		public:
			Finish(
				const Coord& top_left, const int width, const int height
			) : RectMapMovableAdapter(top_left, width, height) {}
	};
}