-- Demo main script --
local ev = require_symbol("events")

angle = 0
radius = 0.5

quit_fct = function (event)
            if event.action == keys.action.down and 
                event:code() == keys.esc then
                print("Exiting using lua binding!!")
                flat:quit() -- from flatland
            end
        end

-- connect: from flatland
local quit_fb = ev.connect("quit_key", events.key, quit_fct) -- ESC

if not quit_fb then
    error("quit_key not bound correctly")
end

mod_fct = function (event)
            if event.action == keys.action.down and 
               event:code() == keys.a then
                local x = radius * math.cos(angle)
                local y = radius * math.sin(angle)
                print("(" .. x .. ", " .. y .. ")")
            end
        end

local mod_fb = ev.connect("mod_key", events.key, mod_fct) -- A

if not mod_fb then
  error("mod_key not bound correctly")
end

up_task = function ()
                --print(angle) it works!!
                angle = angle + 0.001
            end

-- update: from flatland
flat.update:delegate_task(up_task, 1) -- priority 1

return 1
