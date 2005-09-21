
if Controller.isDebugVersion(): print "[highscore.py]"

# .................................................................................................................
#                                               KIKI HIGHSCORE
# .................................................................................................................
class KikiHighscore (ConfigParser):
    """kiki highscore"""
    
    # ................................................................ init
    def __init__ (self):
        """initialization"""
        ConfigParser.__init__ (self)
        
        self.readfp (open(kikipy_path + "kiki.hsc"))
        
        try:
            if os.uname()[0] == "Darwin":
                self.highscore_file_path = os.path.expanduser ("~/Library/Preferences/kiki.hsc")
            else:
                self.highscore_file_path = os.path.expanduser ("~/.kiki.hsc")
        except:
            self.highscore_file_path = os.path.expanduser ("~/.kiki.hsc")

        try:
            self.read (self.highscore_file_path)
        except:
            print ("creating " + self.highscore_file_path)
            
        self.save ()

    # ................................................................ minmoves for level
    def levelMinMoves (self, level_name):
        """reads minimal number of moves for level level_num from highscore file"""
        print "levelMinMoves %s" % level_name
        min_moves = int (self.get (level_name, "moves"))
        print str((min_moves, level_name))
        return min_moves
                        
    # ................................................................ finish level
    def levelFinished (self, level_name, moves):
        """writes data for finished level to highscore file"""
        
        level_num = level_list.index(level_name)
        
        saved_level_num = self.getLastFinishedLevel()
        
        if saved_level_num < level_num and level_num < len(level_list)-1:
            self.set ("main", "last_level", level_name)
        
        if not self.has_section (level_name):
            self.add_section (level_name)
        
        if self.has_option(level_name, "moves"):    
            min_moves = int (self.get (level_name, "moves"))
            if moves < min_moves:
                self.set (level_name, "moves", str (int (moves)))
        else:
            self.set (level_name, "moves", str (int (moves)))
            
        if self.has_option(level_name, getpass.getuser()):
            old_moves = int (self.get (level_name, getpass.getuser()))
            if moves < old_moves:
                self.set (level_name, getpass.getuser(), str (int (moves)))
        else:
            self.set (level_name, getpass.getuser(), str (int (moves)))
        
        self.save ()

    # ................................................................ get last level
    def getLastFinishedLevel (self):
        """returns the index of last finished level in level_list"""
        last_level = str(self.get("main", "last_level"))
        if last_level in level_list:
            return level_list.index(str(last_level))
        else:
            return -1

    # ................................................................ save
    def save (self):
        """save the highscore"""
        try:
            highscore_file = file (self.highscore_file_path, "w+")
            self.write (highscore_file)
            highscore_file.close()
        except:
            console.printError ("unable to write highscore to " + self.highscore_file_path)

# .................................................................................................................

highscore = KikiHighscore ()
