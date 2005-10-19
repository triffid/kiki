# level design by Michael Abel

# .................................................................................................................
def func_mini():
	
	world.addObjectAtPos( KikiWall(), KikiPos(1,1,0))
	world.addObjectAtPos( KikiWall(), KikiPos(3,1,0))
	world.addObjectAtPos( KikiWall(), KikiPos(1,3,0))
	world.addObjectAtPos( KikiWall(), KikiPos(3,3,0))
	
	world.addObjectAtPos( KikiWall(), KikiPos(1,1,6))
	world.addObjectAtPos( KikiWall(), KikiPos(3,1,6))
	world.addObjectAtPos( KikiWall(), KikiPos(1,3,6))
	world.addObjectAtPos( KikiWall(), KikiPos(3,3,6))

	world.addObjectAtPos( KikiStone(), KikiPos(1,1,1))
	world.addObjectAtPos( KikiStone(), KikiPos(3,1,1))
	world.addObjectAtPos( KikiStone(), KikiPos(1,3,1))
	world.addObjectAtPos( KikiStone(), KikiPos(3,3,1))
	
	
	
	world.addObjectAtPos(  KikiStone(), KikiPos(2,4,0))
	
 
	
level_dict["mini"] = {   
                        "scheme":   "tron_scheme",
                        "size":     (5,5,7),
                        "intro":    "mini",    
                        "help":     ( 
                                        "",
                                        "",
                                        "" 
                                    ),
                        "player":   {   "coordinates":     (2,4,4),
                                        "nostatus":         0,
					"orientation"	:	rotx90

				    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,1),
                                            #"coordinates":     (1,1,1), #absolute coord
					    
                                        },
				    ],
			 "create": func_mini,
			}

# .................................................................................................................

