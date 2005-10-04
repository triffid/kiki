# level design by Michael Abel

# .................................................................................................................

level_dict["julia"] = {   
                        "scheme":   "default_scheme",
                        "size":     (11,11,9),
                        "intro":    "julia",    
                        "help":     ( 
                                        "use the bombs :)",
                                         
                                    ),
                        "player":   {   "coordinates":     (1,1,1),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            #"coordinates":     (5,5,8),
					    "position":		(0,0,0),
                                        },
                                    ],
                        "create":
"""

world.addObjectAtPos (KikiStone(), world.decenter(0,0,0))
world.addObjectAtPos (KikiWall(), world.decenter(0,1,0))
world.addObjectAtPos (KikiWall(), world.decenter(0,-1,0))
world.addObjectAtPos (KikiWall(), world.decenter(1,0,0))
world.addObjectAtPos (KikiWall(), world.decenter(-1,0,0))
world.addObjectAtPos (KikiStone(), world.decenter(1,1,0))
world.addObjectAtPos (KikiStone(), world.decenter(-1,-1,0))
world.addObjectAtPos (KikiStone(), world.decenter(1,-1,0))
world.addObjectAtPos (KikiStone(), world.decenter(-1,1,0))

world.addObjectAtPos (KikiBomb(), world.decenter(0,1,-4))
world.addObjectAtPos (KikiBomb(), world.decenter(0,-1,-4))
world.addObjectAtPos (KikiBomb(), world.decenter(1,0,-4))
world.addObjectAtPos (KikiBomb(), world.decenter(-1,0,-4))

world.addObjectAtPos (KikiBomb(), KikiPos (5,5,2))
world.addObjectAtPos (KikiBomb(), KikiPos (4,0,3))

""",                                 
}
