#include "jumping_enemy.hpp"

#include "map_movable.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
    : RectMapMovableAdapter(top_left, width, height) {
    hspeed = 0;
    vspeed = 0;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
    // Враг прыгает на месте, поэтому горизонтальный разворот не нужен.
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
    if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
        kill();
    } else {
        mario->kill();
    }
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
    if (vspeed > 0) {
        top_left.y -= vspeed;
        vspeed = 0;
        grounded = true;
    }
}

void JumpingEnemy::move_horizontally() noexcept {
    // Враг стоит на месте
}

void JumpingEnemy::move_vertically() noexcept {
    if (grounded) {
        // Приземлился - снова прыгает вверх.
        vspeed = JUMP_STRENGTH;
        grounded = false;
    }

    if (vspeed < MAX_V_SPEED) {
        vspeed += V_ACCELERATION;
    }
    top_left.y += vspeed;
}