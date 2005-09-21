
if Controller.isDebugVersion(): print "[levelselection.py]"

world.level_index = 0
world.max_level_index = 0

# .................................................................................................................
#                                           Level Selection
# .................................................................................................................

def levelSelection (level_index=-1, escapeAction=0):

    def startLevel (index):
        world.level_index = 0
        world.setCameraMode (world.CAMERA_BEHIND)
        KikiPyWorld ().create (level_list[index])
    
    def displayLevel (index):
        w = KikiPyWorld ()
        w.preview = true
        world.setCameraMode (world.CAMERA_FOLLOW)
        print "display level %d" % index
        w.create (level_list[index])
        print "level %d displayed" % index
        
    def nextLevel ():
        world.level_index += 1
        if world.level_index > world.max_level_index: 
            world.level_index = 0
        displayLevel (world.level_index)
    
    def previousLevel ():
        world.level_index -= 1
        if world.level_index < 0: 
            world.level_index = world.max_level_index
        displayLevel (world.level_index)
    
    last_level = highscore.getLastFinishedLevel() + 1
    
    print "level selection %d last %d" % (level_index, last_level)
    
    if level_index >= 0:
        world.level_index = level_index
    else:
        world.level_index = last_level
        
    world.max_level_index = last_level
    
    menu = KikiColumnMenu (5, world.level_index)
    if escapeAction:
        menu.getEventWithName ("hide").addAction (escapeAction)
    else:
        menu.setEscapeActive (false)
        
    menu.getEventWithName ("previous").addAction (continuous (previousLevel))
    menu.getEventWithName ("next").addAction (continuous (nextLevel))
    
    menu.getProjection().setViewport (0.0, 0.0, 1.0, 0.4)
    
    for index in range (last_level+1):
        item_text = "%d |%s" % (index+1, level_dict[level_list[index]]["intro"])
        print "item_text"
        menu.addItem (item_text, once (lambda l=index: startLevel(l)))

    displayLevel (world.level_index)

        