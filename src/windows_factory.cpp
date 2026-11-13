// windows_factory.cpp
#include "windows_factory.hpp"
#include "windows_control_settings.hpp"
#include "windows_keyboard.hpp"

namespace biv {

OSControlSettings* WindowsAppFactory::create_control_settings() {
    return new WindowsControlSettings();
}

KeyBoard* WindowsAppFactory::create_keyboard() {
    return new WindowsKeyBoard();
}

std::chrono::milliseconds WindowsAppFactory::get_frame_delay() {
    return std::chrono::milliseconds(10);
}

} 