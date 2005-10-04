
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
                                        "No joke\nit is solvable:)"
                                        
                                    ),
                        "player":   {   "position":     (0,-1,0),
                                        "nostatus":         0,
                                    },
                        "exits":    [
                                        {
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,0),
                                            #"coordinates":     (1,1,1), #absolute coord
                                        },
				    ],
			 "create": func_neutron,
			}

# .................................................................................................................
