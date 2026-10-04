#pragma once

#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
    /**
     * Движущаяся платформа знает только о самой себе:
     * она патрулирует свой участок карты и разворачивается на его границах.
     * Столкновения с Марио и с другими объектами обрабатываются в Game.
     */
    class MovingPlatform : public RectMapMovableAdapter, public Movable {
        private:
            static constexpr float BASE_SPEED = 0.2f;
            // Насколько платформа отъезжает от своей начальной позиции.
            static constexpr float PATROL_RANGE = 3.0f;

            float origin_x;        // Начальная позиция в координатах карты
            int direction = -1;    // 1 - вправо, -1 - влево, 0 - стоим

        public:
            MovingPlatform(const Coord& top_left, int width, int height);

            void move_horizontally() noexcept override;
            void move_vertically() noexcept override;

            void move_map_left() noexcept override;
            void move_map_right() noexcept override;

            void set_direction(int dir) noexcept;
            void stop() noexcept;

            // Фактический шаг платформы за кадр: с ним она "везёт"
            // объекты, которые стоят на ней.
            float get_horizontal_speed() const noexcept { return hspeed; }

            int get_platform_top() const noexcept { return RectMapMovableAdapter::get_top(); }
            int get_platform_bottom() const noexcept { return RectMapMovableAdapter::get_bottom(); }
            int get_platform_left() const noexcept { return RectMapMovableAdapter::get_left(); }
            int get_platform_right() const noexcept { return RectMapMovableAdapter::get_right(); }
            
            Rect* as_rect() noexcept { return static_cast<RectMapMovableAdapter*>(this); }
    };
}