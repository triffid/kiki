# .................................................................................................................
level_dict["bombs"] = {   
                        "scheme":   "red_scheme",
                        "size":     (9,9,9),    
                        "intro":    "bombs", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the bombs",
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
world.addObjectAtPos (KikiBomb(), world.decenter (-3,-2,0))
""",                                 
}