#include <iostream>
#include <entt/entt.hpp>
#include <fmt/core.h>

struct Color {
	float r{0.0}, g{0.0}, b{0.0};
};

struct Position {
    float x{0.0};
    float y{0.0};
};

struct Renderable {
    char glyph;
    Color fg;
    Color bg;
};

struct Velocity {
    float dx;
    float dy;
};

void render(entt::registry &registry) {
    auto view = registry.view<const Position, Renderable>();

    view.each([](const auto &pos, auto &renderable) {
        fmt::print("(x: {}, y: {}) {} \n", pos.x, pos.y, renderable.glyph);
     });
}

void update(entt::registry &registry) {
    auto view = registry.view<const Position, Velocity>();

    // use a callback
    view.each([](const auto &pos, auto &vel) { 
        std::cout << pos.x << " " << pos.y << '\n';
     });

    // use an extended callback
    view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

    // use a range-for
    for(auto [entity, pos, vel]: view.each()) {
        // ...
    }

    // use forward iterators and get only the components of interest
    for(auto entity: view) {
        auto &vel = view.get<Velocity>(entity);
        // ...
    }
}

int main() {
    entt::registry registry;

    // const auto entity = registry.create();
    // registry.emplace<Position>(entity, 1.f, 1.f);
    // registry.emplace<Renderable>(entity, '@', Color(250.f, 200.f, 50.f), Color(0.f, 0.f, 0.f));


    for(auto i = 0u; i < 10u; ++i) {
        const auto entity = registry.create();
        registry.emplace<Position>(entity, i * 1.f, i * 1.f);
        registry.emplace<Renderable>(entity, 'x', Color{250.f, 200.f, 50.f}, Color{0.f, 0.f, 0.f});
        // if(i % 2 == 0) { registry.emplace<Velocity>(entity, i * .1f, i * .1f); }
    }

    render(registry);

    // update(registry);
}