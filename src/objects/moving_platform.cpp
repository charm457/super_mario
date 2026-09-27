#include "moving_platform.hpp"

using biv::MovingPlatform;

MovingPlatform::MovingPlatform(
	const Coord& top_left, const int width, const int height,
	UIFactory* ui_factory
) : RectMapMovableAdapter(top_left, width, height), ui_factory(ui_factory) {
	vspeed = 0;
	hspeed = PLATFORM_SPEED;
}

void MovingPlatform::move_horizontally() noexcept {
	carry_mario();

	top_left.x += hspeed;

	// Считаем только собственные шаги платформы: прокрутка карты тоже меняет x,
	// но она не должна влиять на длину патруля.
	passed_distance += (hspeed > 0 ? hspeed : -hspeed);
	if (passed_distance >= PATROL_DISTANCE) {
		passed_distance = 0;
		hspeed = -hspeed;
	}
}

void MovingPlatform::move_vertically() noexcept {
	// Платформа летит над морем и не падает: гравитация для неё отключена.
}

void MovingPlatform::carry_mario() noexcept {
	if (ui_factory == nullptr) {
		return;
	}

	Mario* mario = ui_factory->get_mario();
	if (mario == nullptr || !mario->is_active()) {
		return;
	}

	if (is_mario_on_platform(mario)) {
		mario->move_horizontal_offset(hspeed);
	}
}

bool MovingPlatform::is_mario_on_platform(const Mario* mario) const noexcept {
	const int feet = mario->get_bottom();
	const int deck = get_top();

	// Марио стоит (или висит в пределах допуска) на верхней грани платформы.
	if (feet > deck || deck - feet > MARIO_TOP_TOLERANCE) {
		return false;
	}

	// И при этом действительно находится над платформой, а не сбоку от неё.
	return mario->get_right() > get_left() && mario->get_left() < get_right();
}
