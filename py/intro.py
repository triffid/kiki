
if Controller.isDebugVersion(): print "[intro.py]"

# .................................................................................................................
#                                             Intro Screen
# .................................................................................................................

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
    about_menu.addItem ("$no_item$scale(0.7)" + Controller.getLocalizedString ("version") + " 1.0.0")
    about_menu.addItem ("$no_item")

    about_menu.addItem ("$no_item" + Controller.getLocalizedString ("programmed by") + ": |kodi")
    about_menu.addItem ("$no_item |monsterkodi@users.sourceforge.net")
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
    #m.addItem (Controller.getLocalizedString ("demo"), once (display_demo))
    m.addItem (Controller.getLocalizedString ("about"), once (display_about))
    m.addItem (Controller.getLocalizedString ("quit"), once (Controller.quit))

    w = KikiPyWorld ()
    w.preview = true
    world.setCameraMode (world.CAMERA_FOLLOW)
    world.getProjection().setPosition (KVector (0,0,0))
    w.create (level_list[min (highscore.getLastFinishedLevel()+1, len (level_list)-1)])
                                                     
display_main_menu ()

