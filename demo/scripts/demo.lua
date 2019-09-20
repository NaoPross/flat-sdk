
local angle = 0
local radius = 0.5

-- connect: from flatland
local fb = connect("quit_key", events.key, 
        function (event)
            if event.action_ == keys.action.down and 
                event.code() == keys.escape then
                quit() -- from flatland
            end
        end) -- ESC

if not fb then
    error("quit_key not bound correctly")
end

fb = connect("mod_key", events.key,
        function (event)
            if event.action_ == keys.action.down and 
               event.code() == keys.A then
                local x = radius * math.cos(angle);
                local y = radius * math.sin(angle);
                print("(" .. x .. ", " .. y .. ")")
            end
        end) -- A

if not fb then
    error("mod_key not bound correctly")
end

-- update: from flatland
flat.update.delegate_task(
    function ()
        angle += 0.001
    end, 
    1) -- priority 1
