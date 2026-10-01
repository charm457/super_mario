#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() {
	return nullptr;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({50, 10}, 3, 3);

	ui_factory->create_ship({181, 24}, 70, 7);

	ui_factory->create_jumping_enemy({196, 22}, 3, 2);

	ui_factory->create_flying_enemy({138, 6}, 3, 2);

	ui_factory->create_moving_platform({107, 22}, 4, 1);

	ui_factory->create_ship({-109, 22}, 200, 5);
	ui_factory->create_ship({-309, 22}, 200, 5);
	ui_factory->create_ship({-509, 22}, 200, 5);
	ui_factory->create_ship({-709, 22}, 200, 5);
	ui_factory->create_ship({-909, 22}, 200, 5);

	ui_factory->create_box({-209, 12}, 10, 3);
	ui_factory->create_full_box({-304, 12}, 5, 3);
	ui_factory->create_box({-409, 12}, 10, 3);
	ui_factory->create_full_box({-504, 12}, 5, 3);
	ui_factory->create_box({-609, 12}, 10, 3);
	ui_factory->create_full_box({-704, 12}, 5, 3);

	ui_factory->create_ship({-924, 24}, 15, 7);
}