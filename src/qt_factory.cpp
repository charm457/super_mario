#include "qt_factory.hpp"
#include "qt_control_settings.hpp"
#include "qt_keyboard.hpp"

namespace biv {

QTFactory::QTFactory(int& argc, char* argv[]) : app(argc, argv) {}

OSControlSettings* QTFactory::create_control_settings() {
    return new QtControlSettings();
}

KeyBoard* QTFactory::create_keyboard() {
    return new QtKeyboard();
}

std::chrono::milliseconds QTFactory::get_frame_delay() {
    return std::chrono::milliseconds(20);
}

} 