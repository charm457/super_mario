#pragma once

#include <vector>

#include "collisionable.hpp"
#include "map_movable.hpp"
#include "mario.hpp"
#include "movable.hpp"
#include "rect.hpp"

namespace biv {
    class Finish;
    class MovingPlatform;

    class Game {
        private:
            std::vector<MapMovable*> map_movable_objs;
            std::vector<Rect*> static_objs;
            std::vector<Collisionable*> collisionable_objs;
            std::vector<Movable*> movable_objs;
            std::vector<MovingPlatform*> moving_platforms;
            std::vector<Finish*> finishes;
            
            Mario* mario = nullptr;
            
            bool is_finished_ = false;
            bool is_level_end_ = false;
            
            // Направление, куда игрок пытается идти (-1: влево, 0: стоит, 1: вправо)
            int mario_intent_direction = 0;

        public:
            Game();
            
            void add_collisionable(Collisionable*);
            void add_map_movable(MapMovable*);
            void add_mario(Mario*);
            void add_movable(Movable*);
            void add_static_obj(Rect*);
            void add_moving_platform(MovingPlatform* platform);
            void add_finish(Finish* finish);
            
            void check_horizontally_static_collisions() noexcept;
            void check_mario_collision();
            bool check_static_collisions(Collisionable* obj) const noexcept;
            void check_vertically_static_collisions() noexcept;

            // Конец уровня наступает, когда Марио касается
            // любого из объектов-финишей.
            void check_finish() noexcept;

            // Марио проверяется с каждой движущейся платформой,
            // с которой столкнулся, - а также со всеми остальными объектами,
            // которые могут контактировать с этой платформой.
            void check_moving_platform_collisions();
            
            void set_mario_intent_direction(int dir) noexcept;
            
            void finish() noexcept;
            
            bool is_finished() const noexcept;
            bool is_level_end() const noexcept;
            
            void move_map_left() noexcept;
            void move_map_right() noexcept;
            void move_objs_horizontally() noexcept;
            void move_objs_vertically() noexcept;
            
            void remove_collisionable(Collisionable*);
            void remove_map_movable(MapMovable*);
            void remove_mario() noexcept;
            void remove_movable(Movable*);
            void remove_moving_platform(MovingPlatform*);
            void remove_finish(Finish*);
            void remove_objs();
            void remove_static_obj(Rect*);
            
            void start_level() noexcept;

        private:
            template<class T>
            void remove_obj(std::vector<T*>& container, T* obj);

            // Разбор контакта одного объекта с одной движущейся платформой.
            void check_obj_platform_collision(
                Collisionable* obj, MovingPlatform* platform) noexcept;
    };
}