#include <flatland/flatland.hpp>

#include <flatland/core/task.hpp>
#include <flatland/core/signal.hpp>

#include <flatland/window.hpp>
#include <flatland/sprite.hpp>
#include <flatland/debug.hpp>

#include <wsdl2/event.hpp>

#include <sol/sol.hpp>


void keypressed(const wsdl2::event::key event) {
    if (event.type == wsdl2::event::key::action::down) {
        if (event.keysym.sym == SDLK_ESCAPE) {
            flat::state::get().running = false;
        }
    }
}

int main() {
    flat::initialize();

    flat::state& engine = flat::state::create("Demo Test");

    //auto render_task = engine.render.delegate_task(&flat::window::render, &win);
    auto& win = engine.window();

    auto keylist = engine.events.connect(&keypressed);
    auto quitlist = engine.events.connect<void, wsdl2::event::quit>(
        [&](wsdl2::event::quit) {
            engine.running = false;
        }
    );

    win.insert(std::make_shared<flat::theater>());
    win.open();

    // Open lua state

    // Run flatland engine loop
    flat::run();

    // Quit flatland engine
    flat::quit();

    return 0;
}
