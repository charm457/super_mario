#pragma once
#include <chrono>
#include "os_control_settings.hpp"
#include "keyboard.hpp"

namespace biv {

class AppFactory {
public:
    virtual ~AppFactory() = default;
    virtual OSControlSettings* create_control_settings() = 0;
    virtual KeyBoard* create_keyboard() = 0;
    virtual std::chrono::milliseconds get_frame_delay() = 0;
};

} 