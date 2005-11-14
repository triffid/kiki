
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
    def levelUserMoves (self, level_name):
        """reads users number of moves for level level_name from highscore file"""
        if not self.has_section (level_name):
            self.add_section (level_name)
        if self.has_option(level_name, getpass.getuser()):    
            min_moves = int (self.get (level_name, getpass.getuser()))
            return min_moves
        else:
          return 0

    # ................................................................ minmoves for level
    def levelParMoves (self, level_name):
        """reads par number of moves for level level_name from highscore file"""
        if not self.has_section (level_name):
            self.add_section (level_name)
        if self.has_option(level_name, "moves"):
            par_moves = int (self.get (level_name, "moves"))
            return par_moves
        else:
          self.set (level_name, "moves", "1000")
          return 1000
                        
    # ................................................................ finish level
    def levelFinished (self, level_name, moves):
        """writes data for finished level to highscore file"""
        
        level_num = level_list.index(level_name)
                
        if not self.has_section (level_name):
            self.add_section (level_name)
            
        if self.has_option(level_name, getpass.getuser()): # level already solved
            old_moves = int (self.get (level_name, getpass.getuser()))
            if moves < old_moves:
                self.set (level_name, getpass.getuser(), str (int (moves)))
        else: # first time solved
            self.set (level_name, getpass.getuser(), str (int (moves)))
            available_level_num = self.getLastAvailableLevel()
            self.set ("main", "last_level", level_list[min(available_level_num+2, len(level_list)-1)])
            
        self.set ("main", "current_level", level_list[min(level_num+1, len(level_list)-1)])
        
        self.save ()

    # ................................................................ get last level
    def getLastAvailableLevel (self):
        """returns the index of last available level in level_list"""
        last_level = str(self.get("main", "last_level"))
        if last_level in level_list:
            return level_list.index(str(last_level))
        else:
            return -1

    # ................................................................ get last level
    def getLastLevel (self):
        """returns the index of last played level in level_list"""
        last_level = str(self.get("main", "current_level"))
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
