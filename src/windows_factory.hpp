#pragma once
#include "app_factory.hpp"

namespace biv {

class WindowsAppFactory : public AppFactory {
public:
    OSControlSettings* create_control_settings() override;
    KeyBoard* create_keyboard() override;
    std::chrono::milliseconds get_frame_delay() override;
};

} 
