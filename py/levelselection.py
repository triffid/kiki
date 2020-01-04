
if Controller.isDebugVersion(): print("[levelselection.py]")

world.max_level_index = 0

# .................................................................................................................
#                                           Level Selection
# .................................................................................................................

def levelSelection (level_index=-1, escapeAction=0):

    def startLevel ():
        world.setCameraMode (world.CAMERA_BEHIND)
        KikiPyWorld ().create (level_list[menu.getCurrentIndex()])
    
    def displayLevel (index):
        w = KikiPyWorld ()
        w.preview = true
        world.setCameraMode (world.CAMERA_FOLLOW)
        w.create (level_list[index])
        
    def levelChanged ():
        displayLevel (menu.getCurrentIndex())
    
    # ............................................................................................................    
    
    last_level = highscore.getLastAvailableLevel()
    current_level = (level_index >= 0) and level_index or last_level 
        
    world.max_level_index = last_level
    
    menu = KikiScrollMenu (5, 3, current_level)
    menu.circular = False
    
    if escapeAction:
        menu.getEventWithName ("hide").addAction (escapeAction)
    else:
        menu.setEscapeActive (false)

    menu.getEventWithName ("changed").addAction (continuous (levelChanged))
    
    menu.getProjection().setViewport (0.0, 0.0, 1.0, 0.4)
    
    for index in range (last_level+1):
        level_name = level_dict[level_list[index]]["intro"]
        user_moves = highscore.levelUserMoves (level_name)
        par_moves  = highscore.levelParMoves (level_name)
        result = user_moves and str(par_moves-user_moves) or "new"
        item_text = "%d |%s|%s    " % (index+1, level_name, result)
        menu.addItem (item_text, once (startLevel))

    displayLevel (current_level)
    menu.show()

