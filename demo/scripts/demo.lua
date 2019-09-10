
local angle = 0
local radius = 0.5

-- connect: from flatland
connect(events.key, 
    function (event)
        if event.type_ == events.key.action.down and 
           event.key == events.key.ESC then
           quit() -- from flatland
        end
    end) -- ESC

connect(events.key,
    function (event)
        if event.type_ == events.key.action.down and 
           event.key == events.key.A then
            local x = radius * math.cos(angle);
            local y = radius * math.sin(angle);
            print("(" .. x .. ", " .. y .. ")")
        end
    end) -- A

-- update: from flatland
update(function ()
    angle += 0.001
end
