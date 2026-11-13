#pragma once
#include <QApplication>
#include "app_factory.hpp"

namespace biv {

class QTFactory : public AppFactory {
private:
    QApplication app;
public:
    QTFactory(int& argc, char* argv[]);
    OSControlSettings* create_control_settings() override;
    KeyBoard* create_keyboard() override;
    std::chrono::milliseconds get_frame_delay() override;
};

} // namespace biv
