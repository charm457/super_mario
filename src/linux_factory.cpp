#include "linux_factory.hpp"
#include "linux_control_settings.hpp"
#include "linux_keyboard.hpp"

namespace biv {

LinuxAppFactory::LinuxAppFactory(int height, int weight)
    : map_height(height), map_weight(weight) {}

OSControlSettings* LinuxAppFactory::create_control_settings() {
    return new LinuxControlSettings(map_height, map_weight);
}

KeyBoard* LinuxAppFactory::create_keyboard() {
    return new LinuxKeyboard();
}

std::chrono::milliseconds LinuxAppFactory::get_frame_delay() {
    return std::chrono::milliseconds(50);
}

} 
