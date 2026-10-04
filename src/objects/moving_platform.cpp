#include "moving_platform.hpp"

#include <algorithm>

#include "map_movable.hpp"

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(const Coord& top_left, int width, int height)
    : Rect(top_left, width, height),
      RectMapMovableAdapter(top_left, width, height),
      Movable(top_left, width, height, 0, 0),
      origin_x(top_left.x) {}

void MovingPlatform::set_direction(int dir) noexcept {
    if (dir > 0) {
        direction = 1;
    } else if (dir < 0) {
        direction = -1;
    } else {
        stop();
    }
}

void MovingPlatform::stop() noexcept {
    direction = 0;
    hspeed = 0;
}

void MovingPlatform::move_horizontally() noexcept {
    if (direction == 0) {
        hspeed = 0;
        return;
    }
    const float min_x = std::max(0.0f, origin_x - PATROL_RANGE);
    const float max_x = origin_x + PATROL_RANGE;

    float next_x = top_left.x + direction * BASE_SPEED;
    if (next_x <= min_x) {
        next_x = min_x;
        direction = 1;
    } else if (next_x >= max_x) {
        next_x = max_x;
        direction = -1;
    }

    hspeed = next_x - top_left.x;
    top_left.x = next_x;
}

void MovingPlatform::move_vertically() noexcept {
    // Парит в воздухе
}

void MovingPlatform::move_map_left() noexcept {
    RectMapMovableAdapter::move_map_left();
    origin_x -= MapMovable::MAP_STEP;
}

void MovingPlatform::move_map_right() noexcept {
    RectMapMovableAdapter::move_map_right();
    origin_x += MapMovable::MAP_STEP;
}