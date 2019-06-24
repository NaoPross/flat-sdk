#include "flatland/flatland.hpp"

#include "flatland/core/task.hpp"
#include "flatland/core/signal.hpp"

#include "flatland/window.hpp"
#include "flatland/sprite.hpp"
#include "flatland/debug.hpp"

#include <wsdl2/event.hpp>


void keypressed(const wsdl2::event::key event) {
    if (event.type == wsdl2::event::key::action::down) {
        if (event.keysym.sym == SDLK_ESCAPE) {
            flat::state::get().running = false;
        }
    }
}

int main() {
    flat::initialize();

    flat::state& engine = flat::state::get();
    flat::window win("Scene Test");

    auto render_task = engine.render.delegate_task(&flat::window::render, &win);

    auto keylist = engine.events.connect(&keypressed);
    auto quitlist = engine.events.connect<void, wsdl2::event::quit>(
        [&](wsdl2::event::quit) {
            engine.running = false;
        }
    );

    engine.set_renderer(win.get_renderer());

    win.insert(std::make_shared<flat::theater>());
    win.open();

    flat::run();
    flat::quit();

    return 0;
}
