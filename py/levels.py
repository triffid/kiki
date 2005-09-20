# -*- coding: utf-8 -*-

if Controller.isDebugVersion(): print "[levels.py]"

level_dict = {}

# .................................................................................................................
def outro (index=0):
    """well hidden outro :-)"""
    outro_text = [  "$scale(1.5)congratulations!\n\n$scale(1)you rescued\nthe nano world!\n\n" +
                "the last dumb mutant bot\nhas been destroyed.\n\nthe maker is functioning again.\n" + 
                "kiki will go now\nand see all his new friends.\n\nyou should maybe\ndo the same?",
                "the maker want's to thank you!\n\n(btw.: you thought\nyou didn't see\nkiki's maker in the game?\n" +
                "you are wrong!\nyou saw him\nall the time,\nbecause kiki\nlives inside him!)\n\n$scale(1.5)the end", 
                "p.s.: the maker of the game\nwants to thank you as well!\n\n(i am sorry\nthat there are not\n" +
                "more levels yet\nand i hope you didn't cheat ;-)\n\ni definitely want your feedback:\n" + 
                "please send me a mail (monsterkodi@gmx.net)\nwith your experiences,\n" +
                "which levels you liked, etc.\n\nthanks in advance and have a nice day,\n\nyours kodi" ]
    
    more_text = index < len(outro_text)-1
    less_text = index > 0
    
    page_text = outro_text[index]
    page_text += "\n\n$scale(0.5)(%d/%d)" % (index+1, len (outro_text))

    page = KikiPageText (page_text, more_text, less_text)
    page.getEventWithName ("hide").addAction (once (display_main_menu))
    
    if more_text:
        page.getEventWithName ("next").addAction (once (lambda i=index+1: outro (i)))
    if less_text:
        page.getEventWithName ("previous").addAction (once (lambda i=index-1: outro (i)))

# .................................................................................................................

level_list = [  "start", "steps", "move", "switch", "electro", # demo
                "gold", "jump", "escape", "gears", # easy
                "elevate", "bombs", "energy", "captured", # medium
                "bridge", "stones", "grid", "rings", "bronze", # difficult
                "hidden", "church", "strange", "columns", # tough
                "mutants" ]
                
for levelName in level_list:
    print "adding " + levelName
    execfile (kikipy_path + os.path.sep + "levels" + os.path.sep + levelName + ".py")