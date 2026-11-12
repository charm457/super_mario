#include "qt_ui_obj_rect_adapter.hpp"

using biv::QtUIObjectRectAdapter;

QtUIObjectRectAdapter::QtUIObjectRectAdapter(
	const Coord& top_left, const int width, const int height
) : Rect(top_left, width, height) {}

int QtUIObjectRectAdapter::get_bottom() const noexcept {
	return Rect::get_bottom();
}

int QtUIObjectRectAdapter::get_height() const noexcept {
	return Rect::get_height();
}

int QtUIObjectRectAdapter::get_left() const noexcept {
	return Rect::get_left();
}

int QtUIObjectRectAdapter::get_right() const noexcept {
	return Rect::get_right();
}

int QtUIObjectRectAdapter::get_top() const noexcept {
	return Rect::get_top();
}

int QtUIObjectRectAdapter::get_width() const noexcept {
	return Rect::get_right() - Rect::get_left();
}
