# level design by Michael Abel
# .................................................................................................................
level_dict["borg"] = {   
                        "scheme":   "default_scheme",
                        "size":     (9,9,9),
                        "intro":    "borg",    
                        "help":     ( 
                                        "Belive me,",
                                        "they are ",
					"CRAZY!"
                                        
                                    ),
                        "player":   {   "coordinates":     (0,0,0),
                                        "nostatus":         0,
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
world.addObjectAtPos (KikiLight	(), KikiPos (7,7,7))

for i in range(150): 
	    world.setObjectRandom (KikiMutant() )
""",                                 
}