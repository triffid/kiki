
if Controller.isDebugVersion(): print "[intro.py]"

# .................................................................................................................
#                                             Intro Screen
# .................................................................................................................

intro_dict = {}

# .................................................................................................................
intro_dict["intro01"] = {   
                        "scheme":   "default_scheme",
                        "size":     (7,7,11),    
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         1,
                                    },
                        "exits":    [
                                        {
                                            "world":       lambda: loadIntroWorld("intro02"),
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,0,3),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiWall(), world.decenter (0,0,-2))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,-4))
world.addObjectAtPos (KikiWall(), world.decenter (0,0,1))

# Controller.player.startRecorder (os.path.expanduser("~/Projects/kiki/py/intro01.rec"))
KikiPlayback.start(kikipy_path + "intro01.rec")
""",                                 
}

# .................................................................................................................
intro_dict["intro02"] = {   
                        "scheme":   "blue_scheme",
                        "size":     (7,7,13),    
                        "player":   {   "coordinates":     (3,0,6),
                                        "nostatus":         1,
                                    },
                        "exits":    [
                                        {
                                            "world":       lambda: loadIntroWorld("intro03"),
                                            "name":         "exit",
                                            "active":       1,
                                            "position":     (0,1,3),
                                        },
                                    ],
                        "create":
"""
world.addObjectAtPos (KikiWall(), world.decenter (0,0,3))
world.addObjectAtPos (KikiWall(), world.decenter (0,-1,1))
world.addObjectAtPos (KikiWall(), world.decenter (0,-2,-1))
world.addObjectAtPos (KikiWall(), world.decenter (0,-3,-3))

# Controller.player.startRecorder (os.path.expanduser("~/Projects/kiki/py/intro02.rec"))
KikiPlayback.start (kikipy_path + "intro02.rec")
""",                                 
}

# .................................................................................................................
intro_dict["intro03"] = {   
                        "scheme":   "red_scheme",
                        "size":     (7,7,7),    
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         1,
                                    },
                        "exits":    [
                                        {
                                            "world":       lambda: loadIntroWorld("intro04"),
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2+1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2+1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2-1, s.y/2,   0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2+1, s.y/2,   0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2-1, 0))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2+1, 0))

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2,   s.y/2,   1))

exit_switch = KikiSwitch()
exit_switch.getEventWithName ("switched").addAction (continuous (lambda : world.toggle("exit")))
world.addObjectAtPos (exit_switch, KikiPos (s.x/2,  s.y/2, 0))

# Controller.player.startRecorder (os.path.expanduser("~/Projects/kiki/py/intro03.rec"))
KikiPlayback.start (kikipy_path + "intro03.rec")
""",                                 
}

# .................................................................................................................
intro_dict["intro04"] = {   
                        "scheme":   "yellow_scheme",
                        "size":     (7,7,7),    
                        "player":   {   "coordinates":     (3,0,3),
                                        "nostatus":         1,
                                    },
                        "exits":    [
                                        {
                                            "world":       lambda: loadIntroWorld("intro05"),
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,-1,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()
h = 0
# bomb and stones

world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y/2, s.z/2))
world.addObjectAtPos (KikiStone(), KikiPos (s.x/2, s.y-2, s.z/2))

world.addObjectAtPos (KikiBomb(), KikiPos (s.x/2, 1, s.z/2))

# stone frames for switches

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h-1, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h+1, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  h, s.z/2))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  h, s.z/2))

world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h+1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h,  1))
world.addObjectAtPos (KikiWall(), world.decenter (s.x/2, h, -1))

world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h-1, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 0,  h+1, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter ( 1,  h, -s.z/2+1))
world.addObjectAtPos (KikiWall(), world.decenter (-1,  h, -s.z/2+1))

world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h-1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h+1, 0))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h,  1))
world.addObjectAtPos (KikiWall(), world.decenter (-s.x/2+1, h, -1))

# switches

world.switch_counter = 0

def switched (switch):
    world.switch_counter += switch.isActive() and 1 or -1
    exit = kikiObjectToGate(world.getObjectWithName("exit"))
    exit.setActive(world.switch_counter == 4)

switch1 = KikiSwitch()
switch1.getEventWithName("switched").addAction (continuous (lambda s=switch1: switched(s)))
switch2 = KikiSwitch()
switch2.getEventWithName("switched").addAction (continuous (lambda s=switch2: switched(s)))
switch3 = KikiSwitch()
switch3.getEventWithName("switched").addAction (continuous (lambda s=switch3: switched(s)))
switch4 = KikiSwitch()
switch4.getEventWithName("switched").addAction (continuous (lambda s=switch4: switched(s)))

world.addObjectAtPos (switch1, world.decenter (-s.x/2+1, 0, 0))
world.addObjectAtPos (switch2, world.decenter ( s.x/2, 0, 0))
world.addObjectAtPos (switch3, world.decenter (0, 0, -s.z/2+1))
world.addObjectAtPos (switch4, world.decenter (0, 0,  s.z/2))

# Controller.player.startRecorder (os.path.expanduser("~/Projects/kiki/py/intro04.rec"))
KikiPlayback.start (kikipy_path + "intro04.rec")
""",                                 
}

# .................................................................................................................
intro_dict["intro05"] = {   
                        "scheme":   "metal_scheme",
                        "size":     (9,7,9),    
                        "player":   {   "position":         (4,0,4),
                                        "nostatus":         1,
                                    },
                        "exits":    [
                                        {
                                            "world":       lambda: loadIntroWorld("intro01"),
                                            "name":         "exit",
                                            "active":       0,
                                            "position":     (0,0,0),
                                        },
                                    ],
                        "create":
"""
s = world.getSize ()
d = 2

world.addObjectLine ( KikiWireStone, world.decenter (-d, s.y/2, 0), world.decenter (-d, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter ( d, s.y/2, 0), world.decenter ( d, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter ( d, 0, 0), world.decenter ( 0, 0, 0))
world.addObjectLine ( KikiWireStone, world.decenter (-d, 0, 0), world.decenter ( 0, 0, 0))

world.addObjectAtPos ( KikiGear (KikiFace.PY), KikiPos (s.x/2-1, 0, s.z/2-1))

world.addObjectAtPos (KikiGenerator (KikiFace.PY), KikiPos (s.x/2+1, 0, s.z/2+1))
world.addObjectAtPos (KikiMotorCylinder (KikiFace.PY), KikiPos (s.x/2, 1, s.z/2))
world.addObjectAtPos (KikiMotorGear (KikiFace.PY), KikiPos (s.x/2, 0, s.z/2))

# floor wire square
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2-d), KikiPos (s.x/2+d, 0, s.z/2-d))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x/2-d+1, 0, s.z/2+d), KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2-d, 0, s.z/2-d+1), KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectLine ("KikiWire (KikiFace.PY, 5)",  KikiPos (s.x/2+d, 0, s.z/2-d+1), KikiPos (s.x/2+d, 0, s.z/2+d))
# corners of wire square
world.addObjectAtPos (KikiWire (KikiFace.PY, 6),  KikiPos (s.x/2-d, 0, s.z/2-d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 3),  KikiPos (s.x/2-d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 9),  KikiPos (s.x/2+d, 0, s.z/2+d))
world.addObjectAtPos (KikiWire (KikiFace.PY, 12), KikiPos (s.x/2+d, 0, s.z/2-d))

world.addObjectLine ("KikiWire (KikiFace.PX, 5)",  KikiPos (    0, 0, s.z/2), KikiPos (    0, s.y, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NX, 5)",  KikiPos (s.x-1, 0, s.z/2), KikiPos (s.x-1, s.y, s.z/2))

world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (0, s.y-1, s.z/2), KikiPos (s.x/2-d, s.y-1, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.NY, 10)", KikiPos (s.x-d, s.y-1, s.z/2), KikiPos (s.x, s.y-1, s.z/2))

world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (0, 0, s.z/2), KikiPos (s.x/2-d, 0, s.z/2))
world.addObjectLine ("KikiWire (KikiFace.PY, 10)", KikiPos (s.x-d, 0, s.z/2), KikiPos (s.x, 0, s.z/2))

world.addObjectAtPos (KikiWire (KikiFace.PY, 13),  KikiPos (s.x/2-d, 0, s.z/2))
world.addObjectAtPos (KikiWire (KikiFace.PY, 7),  KikiPos (s.x/2+d, 0, s.z/2))

# Controller.player.startRecorder (os.path.expanduser("~/Projects/kiki/py/intro05.rec"))
KikiPlayback.start (kikipy_path + "intro05.rec")
""",                                 
}

# .................................................................................................................

def createIntroWorld (name):

    w = KikiPyWorld ()
    w.preview = true
    world.setCameraMode (world.CAMERA_FOLLOW)
    world.getProjection().setPosition (KVector (0,0,0))
    w.create (intro_dict[name])

# .................................................................................................................

def loadIntroWorld (name):
    
    if name != world.name:
        world.name = name
        Controller.timer_event.addAction (once (lambda n=name: createIntroWorld (n)))

# .................................................................................................................

def stop_demo ():
    KikiPlayback.stop()
    display_main_menu ()

# .................................................................................................................

def display_demo ():
    
    m = KikiMenu (2)

    m.addItem ("$no_itemkiki " + Controller.getLocalizedString("demo"))
    m.addItem ("$no_item")
    m.addItem (Controller.getLocalizedString("back"), once (stop_demo))
    
    m.getEventWithName ("hide").addAction (once (stop_demo))
    m.getProjection().setViewport (0.0, 0.0, 1.0, 0.4)
    
    world.name = "intro00"
    loadIntroWorld ("intro01")

# .................................................................................................................

def display_story (index=0):
    
    story = [ 	Controller.getLocalizedString ("STORY_PAGE_1"), 
                Controller.getLocalizedString ("STORY_PAGE_2"),
                Controller.getLocalizedString ("STORY_PAGE_3")] 

    more_text = index < len(story)-1
    less_text = index > 0
    
    story_text = story[index]
    story_text += "\n\n$scale(0.5)(%d/%d)" % (index+1, len (story))

    page = KikiPageText (story_text, more_text, less_text)
    page.getEventWithName ("hide").addAction (once (display_main_menu))
    
    if more_text:
        page.getEventWithName ("next").addAction (once (lambda i=index+1: display_story (i)))
    if less_text:
        page.getEventWithName ("previous").addAction (once (lambda i=index-1: display_story (i)))

# .................................................................................................................

def display_about ():
    
    about_menu = KikiMenu ()
    about_menu.getEventWithName ("hide").addAction (once (display_main_menu))
    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("kiki the nano bot"))
    about_menu.addItem ("$no_item$scale(0.7)" + Controller.getLocalizedString ("version") + " 0.9.0")
    about_menu.addItem ("$no_item")

    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("programmed by") + ": |kodi")
    about_menu.addItem ("$no_item |monsterkodi@gmx.net")
    about_menu.addItem ("$no_item")

    about_menu.addItem ("$no_item music theme by: |N(S)N - NOISE IS SILENCE IS NOISE")
    about_menu.addItem ("$no_item |WWW.N2S1.COM")
    about_menu.addItem ("$no_item")
    
    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("sounds from") + ": |www.iDevGames.com")
    about_menu.addItem ("$no_item")

    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("thanks to") + ": |www.mulle-kybernetik.com")
    about_menu.addItem ("$no_item |www.innot.org")
    about_menu.addItem ("$no_item")

    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("visit") + ": |www.iDevGames.com")
    about_menu.addItem ("$no_item |" + Controller.getLocalizedString ("for more games"))
    about_menu.addItem ("$no_item")

    about_menu.addItem (Controller.getLocalizedString ("main menu"), once (display_main_menu)) 

# .................................................................................................................

def display_main_menu ():
    
    m = KikiMenu (2)
    
    m.getProjection().setViewport (0.0, 0.0, 1.0, 0.4)
    m.setEscapeActive (Controller.isDebugVersion())
    
    main_menu_action = once (display_main_menu)
    
    m.addItem ("$no_item$scale(2)" + Controller.getLocalizedString ("kiki the nano bot"))
    m.addItem ("$no_item")
    m.addItem (Controller.getLocalizedString ("new game"), once (lambda: KikiPyWorld().create (level_list[0])))
    m.addItem (Controller.getLocalizedString ("load level"), once (lambda a=main_menu_action: levelSelection (-1, a)))
    m.addItem (Controller.getLocalizedString ("setup"), once (lambda: quickSetup (0, display_main_menu)))
    m.addItem (Controller.getLocalizedString ("story"), once (display_story))
    m.addItem (Controller.getLocalizedString ("demo"), once (display_demo))
    m.addItem (Controller.getLocalizedString ("about"), once (display_about))
    m.addItem (Controller.getLocalizedString ("quit"), once (Controller.quit))

    w = KikiPyWorld ()
    w.preview = true
    world.setCameraMode (world.CAMERA_FOLLOW)
    world.getProjection().setPosition (KVector (0,0,0))
    w.create (level_list[min (highscore.getLastFinishedLevel()+1, len (level_list)-1)])
                                                     
display_main_menu ()

