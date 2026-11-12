#pragma once

#include "keyboard.hpp"
#include <unordered_set>

namespace biv {
	class QtKeyboard : public KeyBoard {
		private:
			std::unordered_set<int> pressed_keys;
			bool is_active = true;
			bool window_closed = false;
			bool jump_requested = false;

		public:
			QtKeyboard() = default;

			UserInput get_user_input() override;
			void on() override;
			void off() override;

			void handle_key_press(int key, bool is_auto_repeat);
			void handle_key_release(int key, bool is_auto_repeat);
			void handle_close();
	};
}
