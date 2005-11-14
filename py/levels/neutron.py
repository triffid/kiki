# level design by Michael Abel

# .................................................................................................................
def func_neutron():
	neutron_scheme["KikiStone"]     =   {   "base":         (0.0, 0.5, 0.5, 0.5),      }

	world.addObjectAtPos (KikiStone(), world.decenter (0,0,-5))
	world.addObjectAtPos (KikiStone(), world.decenter (0,0,+5))
	world.addObjectAtPos (KikiStone(), world.decenter (+5,0,0))
	world.addObjectAtPos (KikiStone(), world.decenter (-5,0,0))
	world.addObjectAtPos (KikiStone(), world.decenter (0,+5,0))
	world.addObjectAtPos (KikiStone(), world.decenter (0,-5,0))

	
level_dict["neutron"] = {   
                        "scheme":   "neutron_scheme",
                        "size":     (11,11,11),
                        "intro":    "neutron",    
                        "help":     ( 
                        				"$scale(1.5)mission:\nget to the exit!\n\n" + \
                                        "it looks simpler than it is",
                                    ),
                        "player":   {   "position":     (0,-1,0),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,0),                                        
									    },
				    ],
			 "create": func_neutron,
			}

# .................................................................................................................
