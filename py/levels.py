# -*- coding: utf-8 -*-

if Controller.isDebugVersion(): print "[levels.py]"

level_dict = {}

# .................................................................................................................
level_dict["start"] = {   
                        "scheme":   "default_scheme",
                        "size":     (7,7,11),
                        "intro":    "start",
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\njump on the stones",
                                        "to jump,\npress \"$key(jump)\"\nwhile moving",
                                        "to move, press \"$key(move forward)\" or \"$key(move backward)\",\n\n" + \
                                        "to turn, press \"$key(turn left)\" or \"$key(turn right)\""
                                    ),
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,3),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiWall(), world.decenter (0,0,-2))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,-4))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,1))
""",                                 
}

# .................................................................................................................
level_dict["steps"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (7,7,13),
                        "intro":    "steps",    
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\njump on the stones",
                                        "to jump,\npress \"$key(jump)\"\nwhile moving",
                                        "to move, press \"$key(move forward)\" or \"$key(move backward)\",\n\n" + \
                                        "to turn, press \"$key(turn left)\" or \"$key(turn right)\""
                                    ),
                        "player":   {   "coordinates":     (3,0,6),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,1,3),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiWall(), world.decenter (0,0,3))
world.addObjectAtPos (KikiWall(), world.decenter (0,-1,1))
world.addObjectAtPos (KikiWall(), world.decenter (0,-2,-1))
world.addObjectAtPos (KikiWall(), world.decenter (0,-3,-3))
""",                                 
}

# .................................................................................................................
level_dict["move"] = {   
                        "scheme":   "red_scheme",
                        "intro":    "move",
                        "size":     (7,7,7),    
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nactivate the switch\n\n" + \
                                        "to activate the switch,\nshoot it\n\n" + \
                                        "to be able to shoot the switch,\nmove the stone", 
                                        "to move a stone, press \"$key(push)\" while moving\n\n" + \
                                        "to shoot, press \"$key(shoot)\"",
                                    ),
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2+1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2+1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2,   0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2,   0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2+1, 0))

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2,   1))

exit_switch = KikiSwitch()
exit_switch.getEventWithName ("switched").addAction (continuous (lambda : world.toggle("exit")))
world.addObjectAtPos (exit_switch, KikiPos (s.x/2,  s.y/2, 0))
""",                                 
}

# .................................................................................................................
level_dict["switch"] = {   
                        "scheme":   "yellow_scheme",
                        "size":     (7,7,7),
                        "intro":    "switch",    
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nactivate the 4 switches\n\n" + \
                                        "to activate the switches,\nshoot them\n\n" + \
                                        "to be able to shoot the switches,\nmove the center stone", 
                                        "to move the center stone,\n\nuse the bomb.\n\n" + \
                                        "the bomb will detonate if you shoot it"
                                    ),
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-1,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()
h = 0
# bomb and stones

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2, s.z/2))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y-2, s.z/2))

world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, 1, s.z/2))

# stone frames for switches

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h-1, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h+1, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  h, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  h, s.z/2))

world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h+1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h,  1))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h, -1))

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h-1, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h+1, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  h, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  h, -s.z/2+1))

world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h+1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h,  1))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h, -1))

# switches

world.switch_counter = 0

def switched (switch):
    world.switch_counter += switch.isActive() and 1 or -1
    exit = kikiObjectToGate(world.getObjectWithName("exit"))
    exit.setActive(world.switch_counter == 4)

switch1 = KikiSwitch()
switch1.getEventWithName("switched").addAction (continuous (lambda s=switch1: switched(s)))
switch2 = KikiSwitch()
switch2.getEventWithName("switched").addAction (continuous (lambda s=switch2: switched(s)))
switch3 = KikiSwitch()
switch3.getEventWithName("switched").addAction (continuous (lambda s=switch3: switched(s)))
switch4 = KikiSwitch()
switch4.getEventWithName("switched").addAction (continuous (lambda s=switch4: switched(s)))

world.addObjectAtPos (switch1, world.decenter (-s.x/2+1, 0, 0))
world.addObjectAtPos (switch2, world.decenter ( s.x/2, 0, 0))
world.addObjectAtPos (switch3, world.decenter (0, 0, -s.z/2+1))
world.addObjectAtPos (switch4, world.decenter (0, 0,  s.z/2))
""",                                 
}

# .................................................................................................................
level_dict["electro"] = {   
                        "scheme":   "metal_scheme",
                        "size":     (9,7,9),
                        "intro":    "electro",    
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor",
                                    ),
                        "player":   {   "position":         (4,0,4),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()
d = 2

world.addObjectLine ( KikiWireStone, world.decenter (-d, s.y/2, 0), world.decenter (-d, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter ( d, s.y/2, 0), world.decenter ( d, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter ( d, 0, 0), world.decenter ( 0, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter (-d, 0, 0), world.decenter ( 0, 0, 0))

world.addObjectAtPos ( KikiGear (KikiFace.PY), KikiPos (s.x/2-1, 0, s.z/2-1))

world.addObjectAtPos (KikiGenerator (KikiFace.PY), KikiPos (s.x/2+1, 0, s.z/2+1))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.PY), KikiPos (s.x/2, 1, s.z/2))
world.addObjectAtPos (KikiMotorGear (KikiFace.PY), KikiPos (s.x/2, 0, s.z/2))

# floor wire square
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2-d), KikiPos (s.x/2+d, 0, s.z/2-d))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2+d), KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2-d, 0, s.z/2-d+1), KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2+d, 0, s.z/2-d+1), KikiPos (s.x/2+d, 0, s.z/2+d))
# corners of wire square
world.addObjectAtPos (KikiWire (KikiFace.PY, 6),  KikiPos (s.x/2-d, 0, s.z/2-d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 3),  KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 9),  KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 12), KikiPos (s.x/2+d, 0, s.z/2-d))

world.addObjectLine ("KikiWire (KikiFace.PX, 5)",  KikiPos (    0, 0, s.z/2), KikiPos (    0, s.y, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NX, 5)",  KikiPos (s.x-1, 0, s.z/2), KikiPos (s.x-1, s.y, s.z/2))

world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (0, s.y-1, s.z/2), KikiPos (s.x/2-d, s.y-1, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (s.x-d, s.y-1, s.z/2), KikiPos (s.x, s.y-1, s.z/2))

world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (0, 0, s.z/2), KikiPos (s.x/2-d, 0, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x-d, 0, s.z/2), KikiPos (s.x, 0, s.z/2))

world.addObjectAtPos (KikiWire (KikiFace.PY, 13),  KikiPos (s.x/2-d, 0, s.z/2))
world.addObjectAtPos (KikiWire (KikiFace.PY, 7),  KikiPos (s.x/2+d, 0, s.z/2))
""",                                 
}

# .................................................................................................................
level_dict["bronze"] = {   
                        "scheme":   "bronze_scheme",
                        "size":     (9,6,9),    
                        "intro":    "bronze",
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n"+ \
                                        "and close the circuit\nwith the wire stones",
                                    ),
                        "player":   {   "position":         (0,1,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()
d = 2

world.addObjectAtPos (KikiMotorCylinder (KikiFace.PY),  KikiPos (s.x/2, 1,      s.z/2))
world.addObjectAtPos (KikiMotorGear (KikiFace.PY),      KikiPos (s.x/2, 0,      s.z/2))

world.addObjectAtPos (KikiGear (KikiFace.PY),           KikiPos (s.x/2-1, s.y-1,  s.z/2-1))
world.addObjectAtPos (KikiGenerator (KikiFace.PY),      KikiPos (s.x/2+1, s.y-1,  s.z/2-1))
                               
#world.addObjectAtPos (KikiHealthAtom (),                KikiPos (s.x/2+1, s.y-1,  s.z/2+1))
world.addObjectAtPos (KikiBomb (),                      KikiPos (s.x/2-1, s.y-1,  s.z/2+1))

world.addObjectAtPos (KikiWireStone (),                 KikiPos (s.x/2, s.y-1,  s.z/2))
world.addObjectAtPos (KikiWireStone (),                 KikiPos (s.x/2+1, s.y-2,  s.z/2))
world.addObjectAtPos (KikiWireStone (),                 KikiPos (s.x/2-1, s.y-2,  s.z/2))


# floor wire square
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2-d), KikiPos (s.x/2+d, 0, s.z/2-d))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2+d), KikiPos (s.x/2+d, 0, s.z/2+d))

world.addObjectAtPos (KikiWire (KikiFace.PY, 5),  KikiPos (s.x/2-d, 0, s.z/2+1))
world.addObjectAtPos (KikiWire (KikiFace.PY, 5),  KikiPos (s.x/2-d, 0, s.z/2-1))
world.addObjectAtPos (KikiWire (KikiFace.PY, 13),  KikiPos (s.x/2-d, 0, s.z/2))

world.addObjectAtPos (KikiWire (KikiFace.PY, 5),  KikiPos (s.x/2+d, 0, s.z/2+1))
world.addObjectAtPos (KikiWire (KikiFace.PY, 5),  KikiPos (s.x/2+d, 0, s.z/2-1))
world.addObjectAtPos (KikiWire (KikiFace.PY, 7),  KikiPos (s.x/2+d, 0, s.z/2))

# corners of wire square
world.addObjectAtPos (KikiWire (KikiFace.PY, 6),  KikiPos (s.x/2-d, 0, s.z/2-d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 3),  KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 9),  KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 12), KikiPos (s.x/2+d, 0, s.z/2-d))

world.addObjectLine ("KikiWire (KikiFace.PY, 10)",  KikiPos (0, 0, s.z/2), KikiPos (s.x/2-d, 0, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)",  KikiPos (s.x/2+d+1, 0, s.z/2), KikiPos (s.x, 0, s.z/2))

# ceiling wire square
world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (s.x/2-d+1, s.y-1, s.z/2-d), KikiPos (s.x/2+d, s.y-1, s.z/2-d))
world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (s.x/2-d+1, s.y-1, s.z/2+d), KikiPos (s.x/2+d, s.y-1, s.z/2+d))

world.addObjectAtPos (KikiWire (KikiFace.NY, 5),  KikiPos (s.x/2-d, s.y-1, s.z/2+1))
world.addObjectAtPos (KikiWire (KikiFace.NY, 5),  KikiPos (s.x/2-d, s.y-1, s.z/2-1))
world.addObjectAtPos (KikiWire (KikiFace.NY, 13),  KikiPos (s.x/2-d, s.y-1, s.z/2))

world.addObjectAtPos (KikiWire (KikiFace.NY, 5),  KikiPos (s.x/2+d, s.y-1, s.z/2+1))
world.addObjectAtPos (KikiWire (KikiFace.NY, 5),  KikiPos (s.x/2+d, s.y-1, s.z/2-1))
world.addObjectAtPos (KikiWire (KikiFace.NY, 7),  KikiPos (s.x/2+d, s.y-1, s.z/2))

# corners of wire square
world.addObjectAtPos (KikiWire (KikiFace.NY, 3),  KikiPos (s.x/2-d, s.y-1, s.z/2-d))
world.addObjectAtPos (KikiWire (KikiFace.NY, 6),  KikiPos (s.x/2-d, s.y-1, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.NY, 12),  KikiPos (s.x/2+d, s.y-1, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.NY, 9), KikiPos (s.x/2+d, s.y-1, s.z/2-d))

world.addObjectLine ("KikiWire (KikiFace.NY, 10)",  KikiPos (0, s.y-1, s.z/2), KikiPos (s.x/2-d, s.y-1, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NY, 10)",  KikiPos (s.x/2+d+1, s.y-1, s.z/2), KikiPos (s.x, s.y-1, s.z/2))

# wall wire lines
world.addObjectLine ("KikiWire (KikiFace.PX, 5)",  KikiPos (    0, 0, s.z/2), KikiPos (    0, s.y, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NX, 5)",  KikiPos (s.x-1, 0, s.z/2), KikiPos (s.x-1, s.y, s.z/2))

""",                                 
}

# .................................................................................................................
level_dict["gears"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (9,9,9),    
                        "intro":    "gears", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n"+ \
                                        "and close the circuit\nwith the wire stones",
                                    ),
                        "player":   {   "position":         (0,0,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,4,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectAtPos ( KikiWireStone (), world.decenter (-1, 0, 0))
world.addObjectAtPos ( KikiWireStone (), world.decenter ( 1, 0, 0))
world.addObjectAtPos ( KikiWireStone (), world.decenter ( 0,-1, 0))
world.addObjectAtPos ( KikiWireStone (), world.decenter ( 0, 1, 0))
world.addObjectAtPos ( KikiWireStone (), world.decenter ( 0, 0,-1))
world.addObjectAtPos ( KikiWireStone (), world.decenter ( 0, 0, 1))

world.addObjectAtPos ( KikiGear (KikiFace.PY), KikiPos (s.x/2-1, 0, s.z/2-1))
world.addObjectAtPos ( KikiGear (KikiFace.PY), KikiPos (s.x/2+1, 0, s.z/2-1))
world.addObjectAtPos ( KikiGear (KikiFace.PY), KikiPos (s.x/2-1, 0, s.z/2+1))

d = 3
world.addObjectAtPos (KikiGenerator (KikiFace.PY), KikiPos (s.x/2+1, 0, s.z/2+1))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.PY), KikiPos (s.x/2, 1, s.z/2))
world.addObjectAtPos (KikiMotorGear (KikiFace.PY), KikiPos (s.x/2, 0, s.z/2))

# floor wire square
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2-d), KikiPos (s.x/2+d, 0, s.z/2-d))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2+d), KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2-d, 0, s.z/2-d+1), KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2+d, 0, s.z/2-d+1), KikiPos (s.x/2+d, 0, s.z/2+d))
# corners of wire square
world.addObjectAtPos (KikiWire (KikiFace.PY, 6),  KikiPos (s.x/2-d, 0, s.z/2-d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 3),  KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 9),  KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 12), KikiPos (s.x/2+d, 0, s.z/2-d))

world.addObjectAtPos (KikiWire (KikiFace.PX, 1), KikiPos (0, 0, s.z/2))
world.addObjectAtPos (KikiWire (KikiFace.NX, 1), KikiPos (s.x-1, 0, s.z/2))

world.addObjectLine ("KikiWire (KikiFace.PX, 5)",  KikiPos (    0, 1, s.z/2), KikiPos (    0, s.y, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NX, 5)",  KikiPos (s.x-1, 1, s.z/2), KikiPos (s.x-1, s.y, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (0, s.y-1, s.z/2), KikiPos (s.x, s.y-1, s.z/2))

""",                                 
}

# .................................................................................................................
level_dict["stones"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (11,11,12),    
                        "intro":    "stones", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the stones",
                                        "to move a stone,\npress \"$key(push)\"\nwhile moving",
                                    ),
                        "player":   {   "position":         (0,0,5),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "coordinates":  (5,5,6),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

num = 4
for i in range(1,num+1):
    world.addObjectPoly (KikiWall, [(s.x/2-i, s.y/2-i, i-1), \
                                    (s.x/2+i, s.y/2-i, i-1), \
                                    (s.x/2+i, s.y/2+i, i-1), \
                                    (s.x/2-i, s.y/2+i, i-1)])

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-2, s.y/2, 3))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+2, s.y/2, 3))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2+2, 3))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2-2, 3))

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2, 2))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2, 2))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2+1, 2))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2-1, 2))
""",                                 
}

# .................................................................................................................
level_dict["jump"] = {   
                        "scheme":   "red_scheme",
                        "size":     (7,7,13),    
                        "intro":    "jump", 
                        "help":     (  Controller.getLocalizedString ("HELP_JUMP_1"),
                                        Controller.getLocalizedString ("HELP_JUMP_2"),
                                    ),
                        "player":   {   "position":         (0,0,5),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,4),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectAtPos (KikiWall(), world.decenter (0,0,1 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,3 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,6 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (0,1,10 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (1,0,10 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (-1,0,10 - s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (0,-1,10 - s.z/2))
""",                                 
}

# .................................................................................................................
level_dict["energy"] = {   
                        "scheme":   "default_scheme",
                        "size":     (9,17,9),    
                        "intro":    "energy", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nshoot the 4 switches",
                                    ),
                        "player":   {   "position":         (0,1,0),
                                        "orientation":      roty90,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectLine (KikiWall, (0, s.y/2, s.z/2), (s.x, s.y/2, s.z/2))
world.addObjectLine (KikiWall, (s.x/2, s.y/2, 0), (s.x/2, s.y/2, s.z))
world.deleteObject  (world.getOccupantAtPos (world.decenter (0,0,0)))

world.addObjectAtPos (KikiWall(), world.decenter (0, 3, 0))
world.addObjectAtPos (KikiWall(), world.decenter (0, 6, 0))

world.addObjectAtPos (KikiWall(), world.decenter (0, -4, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 2,-5, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,-5, 2))
world.addObjectAtPos (KikiWall(), world.decenter (-2,-5,-1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,-5,-2))

world.addObjectAtPos (KikiMutant(), world.decenter ( 2,-5, 2))
world.addObjectAtPos (KikiMutant(), world.decenter (-2,-5,-2))
world.addObjectAtPos (KikiMutant(), world.decenter ( 1,-5, 1))
world.addObjectAtPos (KikiMutant(), world.decenter (-1,-5,-1))
world.addObjectAtPos (KikiMutant(), world.decenter ( 2,-5,-2))
world.addObjectAtPos (KikiMutant(), world.decenter (-2,-5, 2))
world.addObjectAtPos (KikiMutant(), world.decenter ( 1,-5,-1))
world.addObjectAtPos (KikiMutant(), world.decenter (-1,-5, 1))

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  3, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  5, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  4, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  4, s.z/2))

world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, 3,  0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, 5,  0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, 4,  1))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, 4, -1))

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  3, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  5, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  4, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  4, -s.z/2+1))

world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, 3,  0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, 5,  0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, 4,  1))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, 4, -1))

world.switch_counter = 0

def switched (switch):
    world.switch_counter += switch.isActive() and 1 or -1
    exit = kikiObjectToGate (world.getObjectWithName("exit"))
    exit.setActive (world.switch_counter == 4)

switch1 = KikiSwitch()
switch1.getEventWithName("switched").addAction (continuous (lambda sw=switch1: switched(sw)))
switch2 = KikiSwitch()
switch2.getEventWithName("switched").addAction (continuous (lambda sw=switch2: switched(sw)))
switch3 = KikiSwitch()
switch3.getEventWithName("switched").addAction (continuous (lambda sw=switch3: switched(sw)))
switch4 = KikiSwitch()
switch4.getEventWithName("switched").addAction (continuous (lambda sw=switch4: switched(sw)))

world.addObjectAtPos (switch1, world.decenter (-s.x/2+1, 4, 0))
world.addObjectAtPos (switch2, world.decenter ( s.x/2, 4, 0))
world.addObjectAtPos (switch3, world.decenter (0, 4, -s.z/2+1))
world.addObjectAtPos (switch4, world.decenter (0, 4,  s.z/2))
""",                                 
}

# .................................................................................................................
level_dict["escape"] = {   
                        "scheme":   "metal_scheme",
                        "size":     (7,9,7),    
                        "intro":    "escape", 
                        "help":     ( 
                                        "$scale(1.5)mission:\ntry to escape!\n\n" + \
                                        "to escape,\nactivate the exit\n\n" + \
                                        "to activate the exit,\nshoot the switch\n\n" + \
                                        "to be able to\nshoot the switch,\nmove the stones",
                                    ),
                        "player":   {   "position":         (0,0,0),
                                        "orientation":      rotx180,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-3,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

exit_switch = KikiSwitch()
exit_switch.getEventWithName ("switched").addAction (continuous (lambda : world.toggle("exit")))
world.addObjectAtPos (exit_switch, world.decenter ( 0, -2, 0))

world.addObjectAtPos (KikiStone(), world.decenter ( 0, s.y/2, 0))
world.addObjectAtPos (KikiStone(), world.decenter ( 1, s.y/2, 0))
world.addObjectAtPos (KikiStone(), world.decenter ( 0, s.y/2, 1))
world.addObjectAtPos (KikiStone(), world.decenter ( 0, s.y/2,-1))
world.addObjectAtPos (KikiStone(), world.decenter (-1, s.y/2, 0))

world.addObjectLine (KikiStone, world.decenter (-2, s.y/2,-2), world.decenter ( 2, s.y/2,-2))
world.addObjectLine (KikiStone, world.decenter ( 2, s.y/2,-2), world.decenter ( 2, s.y/2, 2))
world.addObjectLine (KikiStone, world.decenter ( 2, s.y/2, 2), world.decenter (-2, s.y/2, 2))
world.addObjectLine (KikiStone, world.decenter (-2, s.y/2, 2), world.decenter (-2, s.y/2,-2))

world.addObjectAtPos (KikiWall(), world.decenter ( 1, 0, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0, 0, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1, 0, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0, 0,-1))

world.addObjectAtPos (KikiWall(), world.decenter ( 1,-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,-1, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,-1,-1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,-1, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,-1, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,-1,-1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,-1,-1))

world.addObjectAtPos (KikiWall(), world.decenter ( 1,-2, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,-2, 1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,-2, 0))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,-2,-1))
""",                                 
}

# .................................................................................................................
def outro (index=0):
    """well hidden outro :-)"""
    outro_text = [  "$scale(1.5)congratulations!\n\n$scale(1)you rescued\nthe nano world!\n\n" +
                "the last dumb mutant bot\nhas been destroyed.\n\nthe maker is functioning again.\n" + 
                "kiki will go now\nand see all his new friends.\n\nyou should maybe\ndo the same?",
                "the maker want's to thank you!\n\n(btw.: you thought\nyou didn't see\nkiki's maker in the game?\n" +
                "you are wrong!\nyou saw him\nall the time,\nbecause kiki\nlives inside him!)\n\n$scale(1.5)the end", 
                "p.s.: the maker of the game\nwants to thank you as well!\n\n(i am sorry\nthat there are not\n" +
                "more levels yet\nand i hope you didn't cheat ;-)\n\ni definitely want your feedback:\n" + 
                "please send me a mail (monsterkodi@gmx.net)\nwith your experiences,\n" +
                "which levels you liked, etc.\n\nthanks in advance and have a nice day,\n\nyours kodi" ]
    
    more_text = index < len(outro_text)-1
    less_text = index > 0
    
    page_text = outro_text[index]
    page_text += "\n\n$scale(0.5)(%d/%d)" % (index+1, len (outro_text))

    page = KikiPageText (page_text, more_text, less_text)
    page.getEventWithName ("hide").addAction (once (display_main_menu))
    
    if more_text:
        page.getEventWithName ("next").addAction (once (lambda i=index+1: outro (i)))
    if less_text:
        page.getEventWithName ("previous").addAction (once (lambda i=index-1: outro (i)))

# .................................................................................................................
level_dict["mutants"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (9,9,9),    
                        "intro":    "mutants", 
                        "help":     ( 
                                        "$scale(1.5)mission:\ndeactivate the mutants!\n\n" + \
                                        "to deactivate a mutant,\nshoot him until it get's transparent\n\n" + \
                                        "the exit will open,\nwhen all mutant bots\nare deactivated",
                                    ),
                        "player":   {   "position":         (0,-1,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                            "world":       lambda: outro(),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectLine (KikiWall, (2, 2, 2), (s.x - 3, 2, 2))
world.addObjectLine (KikiWall, (s.x - 3, 2, 2), (s.x - 3, s.y - 3, 2))
world.addObjectLine (KikiWall, (s.x - 3, s.y - 3, 2), (s.x - 3, s.y - 3, s.z - 3))
world.addObjectLine (KikiWall, (s.x - 3, s.y - 3, s.z - 3), (2, s.y - 3, s.z - 3))
world.addObjectLine (KikiWall, (2, s.y - 3, s.z - 3), (2, 2, s.z - 3))
world.addObjectLine (KikiWall, (2, 2, s.z - 3), (2, 2, 2))

world.num_mutants   = 5
world.death_counter = 0

def botDied():
    world.death_counter += 1
    if world.death_counter >= world.num_mutants:
        world.activate("exit")

for i in range (world.num_mutants):
    mutant = KikiMutant()
    mutant.getEventWithName ("died").addAction (once (botDied))
    world.setObjectRandom (mutant)
""",                                 
}

# .................................................................................................................
level_dict["bombs"] = {   
                        "scheme":   "red_scheme",
                        "size":     (9,9,9),    
                        "intro":    "bombs", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the bombs\n\n" + \
                                        "be careful,\nwatch your health",
                                    ),
                        "player":   {   "position":         (0,-4,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,2,0),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiBomb(), world.decenter (0,-4,2))
world.addObjectAtPos (KikiBomb(), world.decenter (0,-4,-2))
world.addObjectAtPos (KikiBomb(), world.decenter (-2,-2,0))
#world.addObjectAtPos (KikiHealthAtom(), world.decenter (0,-1,0))
#world.addObjectAtPos (KikiHealthAtom(), world.decenter (0, 0,0))
#world.addObjectAtPos (KikiHealthAtom(), world.decenter (0, 1,0))
#world.addObjectAtPos (KikiHealthAtom(), world.decenter (0, 2,0))
""",                                 
}

# .................................................................................................................
level_dict["grid"] = {   
                        "scheme":   "candy_scheme",
                        "size":     (9,9,9),    
                        "intro":    "grid", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the stones",
                                    ),
                       "player":    {   "position":         (1,0,1),
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

for y in [-1, 1]:
    for x in range (-s.x/2+3, s.x/2-1, 2):
        for z in range (-s.z/2+3, s.z/2-1, 2):
            world.addObjectAtPos (KikiWall (), world.decenter (x, y, z))
            
for y in [-4, 4]:
    for x in range (-s.x/2+1, s.x/2+1, 2):
        for z in range (-s.z/2+1, s.z/2+1, 2):
            world.addObjectAtPos (KikiWall (), world.decenter (x, y, z)) 
            
world.addObjectAtPos (KikiStone (), world.decenter (3,-3,0))
world.addObjectAtPos (KikiStone (), world.decenter (-3,-3,0))

world.addObjectAtPos (KikiStone (), world.decenter (3,3,0))
world.addObjectAtPos (KikiStone (), world.decenter (-3,3,0))

world.addObjectAtPos (KikiStone (), world.decenter (0,-3,0))
world.addObjectAtPos (KikiStone (), world.decenter (0,3,0))
""",                                 
}
            
# .................................................................................................................
level_dict["columns"] = {   
                        "scheme":   "green_scheme",
                        "size":     (7,9,7),    
                        "intro":    "columns", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the stones",
                                    ),
                        "player":   {   "position":         (0,-1,0),
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

for y in range (-s.y/2+1, s.y/2+1):
    for x in range (-s.x/2+1, s.x/2+1, 2):
        for z in range (-s.z/2+1, s.z/2+1, 2):
            world.addObjectAtPos (KikiStone (), world.decenter (x, y, z))
            
world.deleteObject (world.getOccupantAtPos (world.decenter (-1, 0, 1)))
world.deleteObject (world.getOccupantAtPos (world.decenter ( 1, 0,-1)))
world.deleteObject (world.getOccupantAtPos (world.decenter ( 1, 0, 1)))
world.deleteObject (world.getOccupantAtPos (world.decenter (-1, 0,-1)))
""",                                 
}

# .................................................................................................................
level_dict["gold"] = {   
                        "scheme":   "yellow_scheme",
                        "size":     (3,11,3),    
                        "intro":    "gold", 
                        "help":     ( 
                                        Controller.getLocalizedString("HELP_GOLD_1"),
                                    ),
                        "player":   {   "position":         (0,-4,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,4,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

for y in range (-s.y/2+3, s.y/2, 2):
    for x in range (-s.x/2+1, s.x/2+1):
        for z in range (-s.z/2+1, s.z/2+1):
            world.addObjectAtPos (KikiStone (), world.decenter (x, y, z))
""",                                 
}

# .................................................................................................................
level_dict["rings"] = {   
                        "scheme":   "default_scheme",
                        "size":     (9,7,9),    
                        "intro":    "rings", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the stones",
                                    ),
                        "player":   {   "position":         (0,-1,0),
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

for y in [-1, 1]:
    x = 3
    world.addObjectPoly (KikiStone, [world.decenter (-x, y, -x), world.decenter(-x, y, x), \
                                     world.decenter (x, y, x), world.decenter(x, y, -x)])

for y in [-3, 3]:
    for x in [-3, -1, 1, 3]:
        world.addObjectPoly (KikiStone, [world.decenter (-x, y, -x), world.decenter(-x, y, x), \
                                         world.decenter (x, y, x), world.decenter(x, y, -x)])

           
""",                                 
}

# .................................................................................................................
level_dict["bridge"] = {   
                        "scheme":   "red_scheme",
                        "size":     (9,9,5),    
                        "intro":    "bridge", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n\n" + \
                                        "place a wire stone\nnext to the exit",
                                    ),
                        "player":   {   "position":         (0,-3,1),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-1,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectAtPos (KikiMotorGear     (KikiFace.NY), KikiPos (s.x/2-1, s.y-1, s.z/2))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.NY), KikiPos (s.x/2-1, s.y-2, s.z/2))
world.addObjectAtPos (KikiGenerator (KikiFace.NY), KikiPos (s.x/2+1, s.y-1, s.z/2))
world.addObjectLine  ("KikiWire (KikiFace.NY, KikiWire.VERTICAL)", KikiPos (s.x/2, s.y-1, 0), KikiPos (s.x/2, s.y-1, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PY, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, 0), KikiPos (s.x/2, 0, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PZ, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, 0), KikiPos (s.x/2, s.y, 0))
world.addObjectLine  ("KikiWire (KikiFace.NZ, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, s.z-1), KikiPos (s.x/2, s.y, s.z-1))

world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2+3, 0, s.z/2))
world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2-3, 0, s.z/2))
world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2+2, 1, s.z/2))
world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2-2, 1, s.z/2))
world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2+1, 2, s.z/2))
world.addObjectAtPos (KikiWireStone (), KikiPos (s.x/2-1, 2, s.z/2))           
""",                                 
}


# .................................................................................................................
level_dict["hidden"] = {   
                        "scheme":   "metal_scheme",
                        "size":     (9,9,9),    
                        "intro":    "hidden", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nactivate the 5 switches\n\n" + \
                                        "use the stones to\nreach the exit",
                                    ),
                        "player":   {   "position":         (0,-3,1),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectAtPos (KikiStone (), KikiPos (0,0,1))
world.addObjectAtPos (KikiStone (), KikiPos (0,1,0))
world.addObjectAtPos (KikiStone (), KikiPos (1,0,1))
world.addObjectAtPos (KikiStone (), KikiPos (1,1,0))
world.addObjectAtPos (KikiStone (), KikiPos (2,0,0))
switch1 = KikiSwitch ()
world.addObjectAtPos (switch1, KikiPos (1,0,0))

world.addObjectAtPos (KikiStone (), KikiPos (s.x-1,0,1))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-1,1,0))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-2,0,1))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-2,1,0))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-3,0,0))
switch2 = KikiSwitch ()
world.addObjectAtPos (switch2, KikiPos (s.x-2,0,0))

world.addObjectAtPos (KikiStone (), KikiPos (0,0,s.z-2))
world.addObjectAtPos (KikiStone (), KikiPos (0,1,s.z-1))
world.addObjectAtPos (KikiStone (), KikiPos (1,0,s.z-2))
world.addObjectAtPos (KikiStone (), KikiPos (1,1,s.z-1))
world.addObjectAtPos (KikiStone (), KikiPos (2,0,s.z-1))
switch3 = KikiSwitch ()
world.addObjectAtPos (switch3, KikiPos (1,0,s.z-1))

world.addObjectAtPos (KikiStone (), KikiPos (s.x-1,0,s.z-2))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-1,1,s.z-1))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-2,0,s.z-2))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-2,1,s.z-1))
world.addObjectAtPos (KikiStone (), KikiPos (s.x-3,0,s.z-1))
switch4 = KikiSwitch ()
world.addObjectAtPos (switch4, KikiPos (s.x-2,0,s.z-1))

world.addObjectPoly (KikiStone, [KikiPos (s.x/2-1,s.y-1,s.z/2-1), KikiPos (s.x/2-1,s.y-1,s.z/2+1), \
                                 KikiPos (s.x/2+1,s.y-1,s.z/2+1), KikiPos (s.x/2+1,s.y-1,s.z/2-1)])
switch5 = KikiSwitch ()                              
world.addObjectAtPos (KikiStone (), KikiPos (s.x/2,s.y-2,s.z/2))
world.addObjectAtPos (switch5, KikiPos (s.x/2,s.y-1,s.z/2))

world.switch_counter = 0

def switched (switch):
    world.switch_counter += switch.isActive() and 1 or -1
    exit = kikiObjectToGate (world.getObjectWithName("exit"))
    exit.setActive (world.switch_counter == 5)

switch1.getEventWithName("switched").addAction (continuous (lambda s=switch1: switched(s)))
switch2.getEventWithName("switched").addAction (continuous (lambda s=switch2: switched(s)))
switch3.getEventWithName("switched").addAction (continuous (lambda s=switch3: switched(s)))
switch4.getEventWithName("switched").addAction (continuous (lambda s=switch4: switched(s)))
switch5.getEventWithName("switched").addAction (continuous (lambda s=switch5: switched(s)))
""",                                 
}

# .................................................................................................................
level_dict["elevate"] = {   
                        "scheme":   "bronze_scheme",
                        "size":     (9,5,7),    
                        "intro":    "elevate", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n\n" + \
                                        "use the bombs\nto elevate the gears\n" + \
                                        "and the generator",
                                    ),
                        "player":   {   "position":         (3,-2,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (2,-2,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectAtPos (KikiMotorGear     (KikiFace.NY), KikiPos (s.x/2-3, s.y-1, s.z/2))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.NY), KikiPos (s.x/2-3, s.y-2, s.z/2))
world.addObjectAtPos (KikiGenerator (KikiFace.NY), KikiPos (s.x/2+2, 1, s.z/2-1))
world.addObjectAtPos (KikiGear (KikiFace.NY), KikiPos (s.x/2+1, 1, s.z/2+1))
world.addObjectAtPos (KikiGear (KikiFace.NY), KikiPos (s.x/2, 1, s.z/2-1))
world.addObjectAtPos (KikiGear (KikiFace.NY), KikiPos (s.x/2-1, 1, s.z/2+1))
world.addObjectAtPos (KikiGear (KikiFace.NY), KikiPos (s.x/2-2, 1, s.z/2-1))

world.addObjectLine  ("KikiWire (KikiFace.NY, KikiWire.VERTICAL)", KikiPos (s.x/2+2, s.y-1, 0), KikiPos (s.x/2+2, s.y-1, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PY, KikiWire.VERTICAL)", KikiPos (s.x/2+2, 0, 0), KikiPos (s.x/2+2, 0, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PZ, KikiWire.VERTICAL)", KikiPos (s.x/2+2, 0, 0), KikiPos (s.x/2+2, s.y, 0))
world.addObjectLine  ("KikiWire (KikiFace.NZ, KikiWire.VERTICAL)", KikiPos (s.x/2+2, 0, s.z-1), KikiPos (s.x/2+2, s.y, s.z-1))

world.addObjectAtPos (KikiBomb (), KikiPos (s.x/2+2, 0, s.z/2-1))
world.addObjectAtPos (KikiBomb (), KikiPos (s.x/2+1, 0, s.z/2+1))
world.addObjectAtPos (KikiBomb (), KikiPos (s.x/2, 0, s.z/2-1))
world.addObjectAtPos (KikiBomb (), KikiPos (s.x/2-1, 0, s.z/2+1))
world.addObjectAtPos (KikiBomb (), KikiPos (s.x/2-2, 0, s.z/2-1))

""",                                 
}

# .................................................................................................................
level_dict["strange"] = {   
                        "scheme":   "default_scheme",
                        "size":     (9,9,9),    
                        "intro":    "strange", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n\n" + \
                                        "place a wire stone\nnext to the exit",
                                    ),
                        "player":   {   "position":         (1,2,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,-2),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()
d = 2

world.addObjectAtPos (KikiBomb(), world.decenter (0, 0, 0))

world.addObjectAtPos (KikiWireStone(), world.decenter ( 1, 0, 0))
world.addObjectAtPos (KikiWireStone(), world.decenter ( 0, 1, 0))
world.addObjectAtPos (KikiWireStone(), world.decenter (-1, 0, 0))
world.addObjectAtPos (KikiWireStone(), world.decenter ( 0, -1, 0))

world.addObjectAtPos (KikiBomb(), KikiPos (1, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x-2, s.y-2, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x-2, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (1, s.y-2, d))

d = s.z-2 

world.addObjectAtPos (KikiBomb(), KikiPos (1, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x-2, s.y-2, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x-2, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (1, s.y-2, d))

world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, s.y/2, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (1, s.y/2, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, s.y-2, d))
world.addObjectAtPos (KikiBomb(), KikiPos (s.x-2, s.y/2, d))

d = 2

world.addObjectAtPos (KikiStone(), KikiPos ( s.x/2-1, 1, d))
world.addObjectAtPos (KikiStone(), KikiPos ( s.x/2+1, 1, d))

world.addObjectAtPos (KikiStone(), KikiPos ( s.x/2-1, s.y-2, d))
world.addObjectAtPos (KikiStone(), KikiPos ( s.x/2+1, s.y-2, d))

world.addObjectAtPos (KikiStone(), KikiPos ( 1, s.y/2-1, d))
world.addObjectAtPos (KikiStone(), KikiPos ( 1, s.y/2+1, d))

world.addObjectAtPos (KikiStone(), KikiPos ( s.x-2, s.y/2-1, d))
world.addObjectAtPos (KikiStone(), KikiPos ( s.x-2, s.y/2+1, d))

world.addObjectAtPos (KikiMotorGear     (KikiFace.NZ), KikiPos (s.x/2+1, s.y/2, s.z-1))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.NZ), KikiPos (s.x/2+1, s.y/2, s.z-2))
world.addObjectAtPos (KikiGenerator (KikiFace.NZ), KikiPos (s.x/2, s.y/2, s.z/2+1))
world.addObjectLine  ("KikiWire (KikiFace.NY, KikiWire.VERTICAL)", KikiPos (s.x/2, s.y-1, 0), KikiPos (s.x/2, s.y-1, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PY, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, 0), KikiPos (s.x/2, 0, s.z))
world.addObjectLine  ("KikiWire (KikiFace.PZ, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, 0), KikiPos (s.x/2, s.y, 0))
world.addObjectLine  ("KikiWire (KikiFace.NZ, KikiWire.VERTICAL)", KikiPos (s.x/2, 0, s.z-1), KikiPos (s.x/2, s.y, s.z-1))

""",
}


# .................................................................................................................
level_dict["chain"] = {   
                        "scheme":   "candy_scheme",
                        "size":     (9,9,5),    
                        "intro":    "chain", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n\n" + \
                                        "place a wire stone\nnext to the exit",
                                    ),
                        "player":   {   "position":         (1,2,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-1,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()
d = s.z/2

world.addObjectAtPos (KikiWall(), KikiPos (0, 0, d))
world.addObjectAtPos (KikiBomb(), KikiPos (0, 1, d))
world.addObjectAtPos (KikiBomb(), KikiPos (1, 0, d))
world.addObjectAtPos (KikiBomb(), KikiPos (0, 7, d))
world.addObjectAtPos (KikiBomb(), KikiPos (5, 7, d))
world.addObjectAtPos (KikiBomb(), KikiPos (1, 3, d))
world.addObjectAtPos (KikiBomb(), KikiPos (5, 3, d))

world.addObjectAtPos (KikiWireStone(), KikiPos (1,5,d))

""",
}

# .................................................................................................................
level_dict["church"] = {   
                        "scheme":   "yellow_scheme",
                        "size":     (5,7,5),    
                        "intro":    "church", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nactivate the exit!\n\n" + \
                                        "to activate the exit,\nfeed it with electricity:\n\n" + \
                                        "connect the generator\nwith the motor\n\n" + \
                                        "place a wire stone\nnext to the exit",
                                    ),
                        "player":   {   "position":         (1,0,0),
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-1,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize()

world.addObjectLine ("KikiWireStone()", KikiPos (0, 0, 0), KikiPos (0, s.y-2, 0))
world.addObjectLine ("KikiWireStone()", KikiPos (s.x-1, 0, 0), KikiPos (s.x-1, s.y-2, 0))
world.addObjectLine ("KikiWireStone()", KikiPos (s.x-1, 0, s.z-1), KikiPos (s.x-1, s.y-2, s.z-1))
world.addObjectLine ("KikiWireStone()", KikiPos (0, 0, s.z-1), KikiPos (0, s.y-2, s.z-1))

world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, s.y-2, s.z/2))
world.addObjectAtPos (KikiGenerator (KikiFace.PY), KikiPos (s.x/2, s.y/2, s.z/2))

world.addObjectAtPos (KikiWireStone(), KikiPos (1,      s.y-2,  1))
world.addObjectAtPos (KikiWireStone(), KikiPos (s.x-2,  s.y-2,  1))
world.addObjectAtPos (KikiWireStone(), KikiPos (1,      s.y-2,  s.z-2))
world.addObjectAtPos (KikiWireStone(), KikiPos (s.x-2,  s.y-2,  s.z-2))
world.addObjectAtPos (KikiWireStone(), KikiPos (s.x/2,  s.y-1,  s.z/2))

world.addObjectAtPos (KikiMotorGear     (KikiFace.PY), KikiPos (s.x/2, 0, 0))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.PY), KikiPos (s.x/2, 1, 0))
""",                                 
}

# .................................................................................................................
# Level design of 'captured' by Niko Bšhm
# .................................................................................................................

level_dict["captured"] = {
                        "scheme":   "default_scheme",
                        "size":     (9,9,9),
                        "intro":    "captured",
                        "help":     (
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nmove the stones",
                                    ),
                        "player":   {   "position":         (0,-3,0),
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

for i in [-2, 2]:
    world.addObjectPoly (KikiStone, [world.decenter (1, 1, i), world.decenter(1, -1, i),
                                        world.decenter (-1, -1, i), world.decenter(-1, 1, i)])
    world.addObjectPoly (KikiStone, [world.decenter (1, i, 1), world.decenter(1, i, -1),\
                                        world.decenter (-1, i, -1), world.decenter(-1, i, 1)])
    world.addObjectPoly (KikiStone, [world.decenter (i, 1, 1), world.decenter(i, 1, -1),\
                                        world.decenter (i, -1, -1), world.decenter(i, -1, 1)])

for i in [-4, -2, 2, 4]:
    world.addObjectAtPos (KikiStone(), world.decenter(i, 0, 0))
    world.addObjectAtPos (KikiStone(), world.decenter(0, i, 0))
    world.addObjectAtPos (KikiStone(), world.decenter(0, 0, i))
""",
}

# .................................................................................................................

level_list = [  "start", "steps", "move", "switch", "electro", # demo
                "gold", "jump", "escape", "gears", # easy
                "elevate", "bombs", "energy", "captured", # medium
                "bridge", "stones", "grid", "rings", "bronze", # difficult
                "hidden", "church", "strange", "columns", # tough
                "mutants" ]
                