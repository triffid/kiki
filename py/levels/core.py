# .................................................................................................................
level_dict["core"] = {   
                        "scheme":   "yellow_scheme",
                        "size":     (9,9,9),    
                        "intro":    "core", 
                        "help":     ( 
                                        "reach the exit\nto reach the exit, move the stones",
                                    ),
                        "player":   {   "position":         (1,1,1),
                                              "orientation":      rotz90,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

for y in range (-s.y/2+1.5, s.y/2+0.5, 2):
    for x in range (-s.x/2+1.5, s.x/2+0.5):
        for z in range (-s.z/2+1.5, s.z/2+0.5):
            world.addObjectAtPos (KikiStone (), world.decenter (x, y, z))
            
for y in [-1, 1]:
    for x in range (-1, 2):
        for z in range (-1, 2):
            world.removeObject (world.getOccupantAtPos(world.decenter (x, y, z)))
    for z in [-2, 2]:
        world.removeObject (world.getOccupantAtPos(world.decenter (0, y, z)))
            
    for x in [-2, 2]:
        world.removeObject (world.getOccupantAtPos(world.decenter (x, y, 0)))
        
for y in [-3, 3]:
    world.removeObject (world.getOccupantAtPos(world.decenter (0, y, 0)))

for y in [-4, 4]:
    world.addObjectAtPos (KikiStone (), world.decenter (0, y, 0))

""",                                 
}
