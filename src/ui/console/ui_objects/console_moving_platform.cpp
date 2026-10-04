#include "console_moving_platform.hpp"

using biv::ConsoleMovingPlatform;

ConsoleMovingPlatform::ConsoleMovingPlatform(const Coord& top_left, int width, int height)
    : MovingPlatform(top_left, width, height),
      ConsoleUIObjectRectAdapter(top_left, width, height) {}

char ConsoleMovingPlatform::get_brush() const noexcept {
    return '=';
}