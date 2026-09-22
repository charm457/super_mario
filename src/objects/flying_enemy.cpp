#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0; // Враг не падает
	hspeed = 0.2; // Скорость полета по горизонтали
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	// При столкновении со стеной меняем направление полета
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	// Если Марио прыгает на врага сверху, враг умирает, иначе умирает Марио
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

void FlyingEnemy::move_vertically() noexcept {
	if (vspeed < 0) {
		vspeed += V_ACCELERATION;
	}
	top_left.y += vspeed;
	if (hspeed > 0 && top_left.x > 250) {
		hspeed = -hspeed;
		top_left.x = 250;
	} else if (hspeed < 0 && top_left.x < 0) {
		hspeed = -hspeed;
		top_left.x = 0;
	}
}