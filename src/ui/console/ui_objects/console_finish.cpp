#include "console_finish.hpp"

using biv::ConsoleFinish;

ConsoleFinish::ConsoleFinish(const Coord& top_left, const int width, const int height) 
	: Finish(top_left, width, height) {}

char ConsoleFinish::get_brush() const noexcept {
	return 'F';
}