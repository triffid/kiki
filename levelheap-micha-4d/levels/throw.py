# level design by Michael Abel

# .................................................................................................................
def func_throw():
	world.addObjectAtPos( KikiWall(),  world.decenter(-2,0,2))
	world.addObjectAtPos( KikiStone(), world.decenter(0,1,3))
	world.addObjectAtPos( KikiStone(), world.decenter(0,-1,3))
	world.addObjectAtPos( KikiLight(), world.decenter(0,0,3))
	world.addObjectAtPos( KikiLight(), world.decenter(0,0,-3))
	
 
	
level_dict["throw"] = {   
                        "scheme":   "tron_scheme",
                        "size":     (5,7,7),
                        "intro":    "throw",    
                        "help":     ( 
                                        "",
                                    ),
                        "player":   {   "coordinates":     (0,0,0),
                                        "nostatus":         0,
					#"orientation"	:	roty180

				    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,0),
                                            #"coordinates":     (1,1,1), #absolute coord
					    
                                        },
				    ],
			 "create": func_throw,
			}

# .................................................................................................................

