#include "game.hpp"

#include <algorithm>
#include "finish.hpp"
#include "moving_platform.hpp"

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
    collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
    map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
    mario = obj;
}

void Game::add_movable(Movable* obj) {
    movable_objs.push_back(obj);
}

void Game::add_static_obj(Rect* obj) {
    static_objs.push_back(obj);
}

void Game::add_moving_platform(MovingPlatform* platform) {
    moving_platforms.push_back(platform);
}

void Game::add_finish(Finish* finish) {
    finishes.push_back(finish);
}

void Game::set_mario_intent_direction(int dir) noexcept {
    mario_intent_direction = dir;
}

void Game::check_horizontally_static_collisions() noexcept {
    for (Collisionable* obj : collisionable_objs) {
        for (Rect* static_obj : static_objs) {
            if (obj->has_collision(static_obj)) {
                obj->process_horizontal_static_collision(static_obj);
                break;
            }
        }
    }
}

void Game::check_mario_collision() {
    if (mario == nullptr || !mario->is_active()) {
        return;
    }

    for (int i = 0; i < static_cast<int>(collisionable_objs.size()); i++) {
        Collisionable* obj = collisionable_objs[i];
        if (obj->has_collision(mario)) {
            obj->process_mario_collision(mario);
            if (!mario->is_active()) {
                break;
            } else if (!obj->is_active()) {
                collisionable_objs[i] = collisionable_objs.back();
                collisionable_objs.pop_back();
                i--;
            }
        }
    }
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
    for (Rect* static_obj : static_objs) {
        if (obj->has_collision(static_obj)) {
            return true;
        }
    }
    return false;
}

void Game::check_moving_platform_collisions() {
    for (MovingPlatform* platform : moving_platforms) {
        // Марио проверяется с этой платформой, если он с ней столкнулся.
        if (mario != nullptr && mario->is_active()) {
            check_obj_platform_collision(mario, platform);
        }

        // Остальные объекты, которые могут контактировать с платформой
        // (враги, деньги и т.д.). Каждый объект сам разбирается
        // со своим столкновением в process_*_static_collision.
        for (Collisionable* obj : collisionable_objs) {
            if (obj == mario || !obj->is_active()) {
                continue;
            }
            check_obj_platform_collision(obj, platform);
        }
    }
}

void Game::check_obj_platform_collision(
    Collisionable* obj, MovingPlatform* platform
) noexcept {
    Rect* platform_rect = platform->as_rect();
    Rect myself = obj->get_rect();

    const int tolerance = 2;
    const int platform_top = platform->get_platform_top();

    bool inside_x =
        myself.get_right() > platform->get_platform_left() &&
        myself.get_left() < platform->get_platform_right();

    bool on_top =
        myself.get_bottom() >= platform_top &&
        myself.get_bottom() - platform_top <= tolerance;

    if (inside_x && on_top && obj->get_speed().v >= 0) {
        if (obj->has_collision(platform_rect)) {
            // Объект приземляется на платформу: каждый объект сам
            // разбирается со своим вертикальным столкновением
            // (как и для статических объектов).
            obj->process_vertical_static_collision(platform_rect);
        }

        // Платформа везёт объект ровно на свой фактический шаг за кадр,
        // пока объект находится в зоне верхней кромки платформы.
        if (Movable* movable = dynamic_cast<Movable*>(obj)) {
            movable->move_horizontal_offset(platform->get_horizontal_speed());
        }
        return;
    }

    if (obj->has_collision(platform_rect)) {
        if (obj->get_speed().v < 0) {
            // Объект ударился о платформу снизу - платформа работает как потолок.
            obj->process_vertical_static_collision(platform_rect);
        } else {
            // Платформа работает как стена.
            obj->process_horizontal_static_collision(platform_rect);
        }
    }
}

void Game::check_finish() noexcept {
    if (mario == nullptr || !mario->is_active()) {
        return;
    }

    for (Finish* finish : finishes) {
        if (mario->has_collision(finish)) {
            is_level_end_ = true;
            return;
        }
    }
}

void Game::check_vertically_static_collisions() noexcept {
    if (mario == nullptr || !mario->is_active()) {
        return;
    }
    
    for (Collisionable* obj : collisionable_objs) {
        for (Rect* static_obj : static_objs) {
            if (obj->has_collision(static_obj)) {
                obj->process_vertical_static_collision(static_obj);
                break;
            }
        }
    }
}

void Game::finish() noexcept {
    is_finished_ = true;
}

bool Game::is_finished() const noexcept {
    return is_finished_;
}

bool Game::is_level_end() const noexcept {
    return is_level_end_;
}

void Game::move_map_left() noexcept {
    for (MapMovable* obj : map_movable_objs) {
        obj->move_map_left();
    }
}

void Game::move_map_right() noexcept {
    for (MapMovable* obj : map_movable_objs) {
        obj->move_map_right();
    }
}

void Game::move_objs_horizontally() noexcept {
    for (Movable* obj : movable_objs) {
        obj->move_horizontally();
    }
}

void Game::move_objs_vertically() noexcept {
    for (Movable* obj : movable_objs) {
        obj->move_vertically();
    }
}

void Game::remove_collisionable(Collisionable* obj) {
    remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
    remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
    mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
    remove_obj(movable_objs, obj);
}

void Game::remove_moving_platform(MovingPlatform* obj) {
    remove_obj(moving_platforms, obj);
}

void Game::remove_finish(Finish* obj) {
    remove_obj(finishes, obj);
}

void Game::remove_objs() {
    collisionable_objs.clear();
    map_movable_objs.clear();
    movable_objs.clear();
    static_objs.clear();
    moving_platforms.clear();
    finishes.clear();
    remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
    remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
    is_level_end_ = false;
}

// ----------------------------------------------------------------------------
//                                  PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
    container.erase(
        std::remove(
            container.begin(), container.end(), obj
        ), 
        container.end()
    );
}