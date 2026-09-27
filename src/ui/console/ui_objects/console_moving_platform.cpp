#include "console_moving_platform.hpp"

using biv::ConsoleMovingPlatform;

ConsoleMovingPlatform::ConsoleMovingPlatform(
	const Coord& top_left, const int width, const int height,
	UIFactory* ui_factory
) : MovingPlatform(top_left, width, height, ui_factory) {}

char ConsoleMovingPlatform::get_brush() const noexcept {
	return '=';
}
