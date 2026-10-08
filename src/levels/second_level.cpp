#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);

	ui_factory->create_ship({20, 25}, 40, 2);

	ui_factory->create_ship({60, 20}, 40, 7);

	ui_factory->create_box({65, 12}, 10, 3);
	ui_factory->create_full_box({75, 12}, 5, 3);
	ui_factory->create_box({80, 12}, 5, 3);
	ui_factory->create_full_box({85, 12}, 5, 3);

	ui_factory->create_ship({100, 25}, 30, 2);

	ui_factory->create_moving_platform({140, 25}, 4, 1);

	ui_factory->create_ship({160, 20}, 40, 7);
	ui_factory->create_ship({200, 25}, 40, 2);

	ui_factory->create_enemy({210, 5}, 3, 2);

	ui_factory->create_ship({265, 20}, 25, 7);
	ui_factory->create_ship({290, 25}, 40, 2);

	ui_factory->create_jumping_enemy({300, 22}, 3, 2);

	ui_factory->create_flying_enemy({140, 6}, 3, 2);

	ui_factory->create_ship({355, 20}, 15, 7);
	
	// Финиш уровня: зона-триггер на палубе последнего корабля.
	ui_factory->create_finish({355, 17}, 15, 3);
}
