# level design by Michael Abel

# .................................................................................................................
def func_empty():
	for i in range (2):
		world.addObjectAtPos (KikiLight	(), KikiPos (1,1,i))
		
 
	
level_dict["empty"] = {   
                        "scheme":   "tron_scheme",
                        "size":     (10,10,10),
                        "intro":    "empty",    
                        "help":     ( 
                                        "",
                                        "",
                                        "" 
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
			 "create": func_empty,
			}

# .................................................................................................................

