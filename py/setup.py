
if Controller.isDebugVersion(): print("[setup.py]")

# .................................................................................................................
#                                               KEY SETUP MENU
# .................................................................................................................

def quickKeySetup (item_index = 0, escapeAction=0):
    
    menu = KikiMenu (item_index)    
    
    action_names = ["$no_itemkeyboard setup", "$no_item", 
                    "move forward", 
                    "move backward", 
                    "turn left", 
                    "turn right", "$no_item", 
                    "jump", 
                    "push", 
                    "shoot", "$no_item", 
                    "change view", 
                    "look up", 
                    "look down"]
                    
    player = Controller.player
    
    def changeKey (action_index):

        tmp_menu = KikiMenu (action_index)
        
        for item_index in range (len (action_names)):
            action_name = action_names[item_index]
            if action_name.find ("$no_item") >= 0:
                tmp_menu.addItem (Controller.getLocalizedString (action_name))
            else:
                action_key = ""
                if action_index != item_index:
                    action_key = player.getKeyForAction (action_name)
                    
                tmp_menu.addItem (Controller.getLocalizedString (action_name) + ": |" + action_key)
            
        tmp_menu.addItem ("$no_item")
        tmp_menu.addItem ("$no_item$scale(0.75)" + Controller.getLocalizedString ("press the new key"))        

        hideTmpMenu = lambda m=tmp_menu: Controller.timer_event.addAction (m.getActionWithName("delete"))

        keyset_event = player.getEventWithName ("keyset")
        keyset_event.removeAllActions()
        keyset_event.addAction (once (lambda i=action_index, t=hideTmpMenu, a=escapeAction: \
                                                            (t() or 1) and quickKeySetup (i, a)))

        player.recordKeyForAction (action_names[action_index])

    undefined_keys = false
    for action_index in range (len (action_names)):
        action_name = action_names[action_index]
        if action_name.find ("$no_item") >= 0:
            menu.addItem (Controller.getLocalizedString (action_name))
        else:
            action_key = player.getKeyForAction (action_name)
            if not action_key:
                undefined_keys = true
            menu.addItem (Controller.getLocalizedString (action_name) + ": |" + action_key, once (lambda i=action_index: changeKey(i)))
        
    menu.addItem ("$no_item")
    
    if undefined_keys:
        menu.addItem ("$no_item$scale(0.75)" + Controller.getLocalizedString("action without key") + "!")
        menu.setEscapeActive (false)
    else:
        if escapeAction:
            menu.addItem ("$scale(0.75)" + Controller.getLocalizedString("back to setup"), once (escapeAction))
        else:
            menu.addItem ("$scale(0.75)" + Controller.getLocalizedString("back to setup"), once (quickSetup))
        
    if escapeAction:
        menu.getEventWithName ("hide").addAction (once (escapeAction))

# .................................................................................................................
#                                               SETUP MENU
# .................................................................................................................

def quickSetup (itemIndex = 0, escapeAction=0):
    
    menu = KikiMenu (itemIndex)
    
    def setupOption (option):

        if callable (option):
            option_func = option
        else:
            if option == "language":
                itemIndex = 2
                langIndex = lang_list.index(Controller.language) + 1
                if langIndex >= len(lang_list): langIndex = 0
                option_func = lambda: config.apply ("game", "language", lang_list[langIndex])
            elif option == "mute":
                itemIndex = 3
                option_func = lambda: config.apply ("sound", "mute", not Controller.sound.isMute())
            elif option == "volume":
                itemIndex = 4
                volume = sound.getSoundVolume() / (128/9) + 1
                if volume > 10: volume = 1
                option_func = lambda: config.apply ("sound", "volume", volume)   
            elif option == "fullscreen":
                itemIndex = 5
                option_func = lambda: config.apply ("display", "fullscreen", not Controller.getFullscreen())
            elif option == "fov":
                itemIndex = 6
                fov = int (Controller.world.getProjection().getFov()) + 10
                if fov > 120: fov = 60
                option_func = lambda: config.apply ("display", "fov", fov)
            elif option == "gamma":
                itemIndex = 7
                gamma = Controller.getGamma() + 1
                if gamma > 10: gamma = 0
                option_func = lambda: config.apply ("display", "gamma", gamma)
            elif option == "speed":
                itemIndex = 8
                speed = Controller.getSpeed() + 1
                if speed > 10: speed = 1
                option_func = lambda: config.apply ("game", "speed", speed)
            
        menu_func = lambda i=itemIndex: quickSetup (i, escapeAction)

        return once (lambda f=option_func, m=menu_func: (f() or true) and m())

    menu.addItem ("$no_item" + Controller.getLocalizedString ("setup"))
    menu.addItem ("$no_item")

    menu.addItem (Controller.getLocalizedString ("language") + ": |" + Controller.language, setupOption ("language"), True)
    menu.addItem (Controller.getLocalizedString ("sound") + ": |" + (sound.isMute() and Controller.getLocalizedString ("off") or Controller.getLocalizedString ("on")), setupOption ("mute"), True)
    menu.addItem (Controller.getLocalizedString ("volume") + ": |%d" % (int (sound.getSoundVolume()/(128/9)),), setupOption ("volume"), True)
    menu.addItem (Controller.getLocalizedString ("fullscreen") + ": |" + (Controller.getFullscreen() and Controller.getLocalizedString ("on") or Controller.getLocalizedString ("off")), setupOption ("fullscreen"), True)
    menu.addItem (Controller.getLocalizedString ("fov") + ": |%d" % (int (Controller.world.getProjection().getFov()),), setupOption ("fov"), True)
    menu.addItem ("gamma: |%d" % (int (Controller.getGamma()),), setupOption ("gamma"), True)
    menu.addItem (Controller.getLocalizedString ("speed") + ": |%d" % (Controller.getSpeed(),), setupOption ("speed"), True)

    if escapeAction:
        menu.getEventWithName ("hide").addAction (once (escapeAction))
        saveAction = once (lambda: (config.save() or 1) and escapeAction())
    else:
        saveAction = once (config.save)

    menu.addItem ("$no_item")
    menu.addItem (Controller.getLocalizedString ("keyboard setup"), once (lambda: quickKeySetup (0, lambda a=escapeAction: quickSetup (0, a))))
    menu.addItem (Controller.getLocalizedString ("save"), saveAction)
