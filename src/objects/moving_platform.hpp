/**
	Движущаяся платформа над морем.

	Особенности архитектуры игры, которые здесь учтены:

	1. Марио перемещается не сам, а прокруткой карты (Mario::move_map_left /
	   Mario::move_map_right). Поэтому платформа - MapMovable: при прокрутке
	   карты она смещается вместе с уровнем и остаётся над тем же участком моря.

	2. Movable::move_vertically() включает гравитацию, поэтому метод переопределён:
	   платформа не падает.

	3. Дистанция патрулирования считается по собственным шагам платформы, а не по
	   абсолютной координате x. Прокрутка карты сдвигает x всех объектов, но не
	   должна менять границы патруля.

	4. Платформа регистрируется в Game как static obj, чтобы Марио мог на неё
	   приземлиться (вертикальные статические столкновения). Поэтому платформу нужно
	   создавать до последнего статического объекта уровня: последний статический
	   объект считается финишем (Game::check_vertically_static_collisions).

	5. Платформа не является Collisionable: она уже лежит в static_objs, а
	   has_collision(self) всегда истинно, что ломало бы обработку столкновений.

	6. Чтобы увезти Марио, платформа получает UIFactory* (как FullBox) и берёт
	   актуального Марио через get_mario().
*/

#pragma once

#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"
#include "ui_factory.hpp"

namespace biv {
	class MovingPlatform : public RectMapMovableAdapter, public Movable {
		private:
			static constexpr float PLATFORM_SPEED = 0.1f;
			static constexpr float PATROL_DISTANCE = 12.0f;

			// Марио может находиться над опорой с небольшим зазором: вертикальное
			// столкновение откатывает последний шаг падения. Допуск на этот зазор.
			static constexpr int MARIO_TOP_TOLERANCE = 2;

			UIFactory* ui_factory = nullptr;

			float passed_distance = 0;

			void carry_mario() noexcept;
			bool is_mario_on_platform(const Mario*) const noexcept;

		public:
			MovingPlatform(
				const Coord& top_left, const int width, const int height,
				UIFactory* ui_factory);

			void move_horizontally() noexcept override;
			void move_vertically() noexcept override;
	};
}
