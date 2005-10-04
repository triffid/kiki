

# .................................................................................................................

level_dict["juliette"] = {   
                        "scheme":   "default_scheme",
                        "size":     (11,11,11),
                        "intro":    "juliette",    
                        "help":     ( 
                                        "be a nano",
                                        "terrorist",
                                        "There is more than\none solution" 
                                    ),
                        "player":   {   "coordinates":     (1,1,1),
				 	"orientation": rotz90,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
					    "position":		(0,0,2),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiWall(), world.decenter(0,0,1))

world.addObjectAtPos (KikiBomb(), world.decenter(0,0,-5))

world.addObjectAtPos (KikiBomb(), world.decenter(0,0,-3))

world.addObjectAtPos (KikiBomb(), world.decenter(0,5,-2))
world.addObjectAtPos (KikiBomb(), world.decenter(0,5,-3))
world.addObjectAtPos (KikiBomb(), world.decenter(0,5,-1))

world.addObjectAtPos (KikiBomb(), world.decenter(5,0,-2))
world.addObjectAtPos (KikiBomb(), world.decenter(5,0,-3))
world.addObjectAtPos (KikiBomb(), world.decenter(5,0,-1))

""",                                 
}