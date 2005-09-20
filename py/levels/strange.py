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
