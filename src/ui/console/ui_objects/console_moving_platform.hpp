#pragma once

#include "console_ui_obj_rect_adapter.hpp"
#include "moving_platform.hpp"

namespace biv {
    class ConsoleMovingPlatform : public MovingPlatform, public ConsoleUIObjectRectAdapter {
        public:
            ConsoleMovingPlatform(const Coord& top_left, int width, int height);

            char get_brush() const noexcept override;
    };
}