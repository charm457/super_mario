#pragma once

#include <vector>

#include "game_map.hpp"
#include "qt_game_window.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
	class QtKeyboard;
	class Mario;

	class QtGameMap : public GameMap {
		private:
			QtGameWindow* window = nullptr;
			std::vector<QtUIObject*> objs;
			Mario* mario = nullptr;

		public:
			QtGameMap(const int height, const int width, QtKeyboard* keyboard);
			~QtGameMap();

			void add_obj(QtUIObject* obj);
			void set_mario(Mario* m);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(QtUIObject* obj);
			void remove_objs() override;
			void show() const noexcept override;
	};
}
