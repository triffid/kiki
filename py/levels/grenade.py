# .................................................................................................................
level_dict["grenade"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (9,9,9),    
                        "intro":    "grenade", 
                        "help":     ( 
                                        "$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "to get to the exit,\nuse the bombs\n\n" + \
                                        "tip: use 1-9 keys to\nadjust the game speed",
                                    ),
                        "player":   {   "position":   (0,-4,0),
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
world.addObjectAtPos (KikiBomb(), world.decenter (0,-3,-4))
world.addObjectAtPos (KikiBomb(), world.decenter (0,-3,-3))
""",                                 
}