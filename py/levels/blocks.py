# level design by Michael Abel

# .................................................................................................................
def func_blocks():
	
	world.addObjectAtPos (KikiWall()			, KikiPos (1,1,2))
	world.addObjectAtPos (KikiWall()			, KikiPos (4,2,2))
	world.addObjectAtPos (KikiWall()			, KikiPos (7,2,2))
	world.addObjectAtPos (KikiStone()			, KikiPos (10,2,2))
	world.addObjectAtPos (KikiStone(None, True)		, KikiPos (13,2,2))
	world.addObjectAtPos (KikiStone(None, True)		, KikiPos (15,4,2))
	
	world.addObjectAtPos (KikiStone(KColor(0,1,0,0.8), True)	, KikiPos (13,7,2))
	world.addObjectAtPos (KikiStone(KColor(1,0,0,0.8), True)	, KikiPos (10,7,2))
	world.addObjectAtPos (KikiStone(KColor(0,0,1,0.8), True)	, KikiPos (7,7,2))
	world.addObjectAtPos (KikiStone(KColor(0.5,0.5,0,0.8))		, KikiPos (4,7,2))
	
	
	world.addObjectLine (KikiWall, KikiPos (0,0,2), KikiPos(7,0,2) )
	

	
 
	
level_dict["blocks"] = {   
                        "scheme":   "default_scheme",
                        "size":     (18,12,5),
                        "intro":    "blocks",    
                        "help":     (   "As you might know: you can grab\n"
					"most stones by pressing forward\n"
					"while jumping or falling down\n"
					"next to them.",
					"The stone with the slits is a\n"
                                        "special stone, that means that\n"
					"you can't grab it while jumping\n"
					"or falling", 
					"The color of a stone doesn't matter.", 
                                    ),
                        "player":   {   "coordinates":     (1,6,2),
                                        "nostatus":         0,
				    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "coordinates":     (7,9,2),
					    
                                        },
				    ],
			 "create": func_blocks,
			}

# .................................................................................................................

