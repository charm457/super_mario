#pragma once
#include "app_factory.hpp"

namespace biv {

class LinuxAppFactory : public AppFactory {
private:
    int map_height;
    int map_weight;
public:
    LinuxAppFactory(int height, int weight);
    OSControlSettings* create_control_settings() override;
    KeyBoard* create_keyboard() override;
    std::chrono::milliseconds get_frame_delay() override;
};

} // namespace biv
