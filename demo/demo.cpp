#include <wsdl2/event.hpp>

#include <flatland/flatland.hpp>
#include <flatland/core/task.hpp>
#include <flatland/core/signal.hpp>

#include <flatland/sprite.hpp>
#include <flatland/debug.hpp>

#include <flatlua/lua_state.hpp>
#include "demo/resources.hpp"

void keypressed(const wsdl2::event::key event) {
    if (event.type == wsdl2::event::key::action::down) {
        if (event.code() == SDLK_e) {
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

    //win.insert(std::make_shared<flat::theater>());
    win.open();

    // Open lua state
    flat::lua::state lua_state(engine);

    build::resource r_demo = LOAD_RESOURCE(scripts_demo_lua);                 
    auto demo_script = lua_state.safe_script(r_demo.str(),                              
        [](lua_State*, sol::protected_function_result pfr) {                    
            sol::error err = pfr;                                               
            npdebug("Could not load utils.lua: ", err.what());                  
            return pfr;                                                         
        });

    // Run flatland engine loop
    flat::run();

    // TODO, avoid this call, Quit flatland engine
    flat::quit();

    return 0;
}
