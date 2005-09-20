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