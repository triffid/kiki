
if Controller.isDebugVersion(): print "[file.py]"

# .................................................................................................................
#                                                      KikiPyFile
# .................................................................................................................

class KikiPyFile (KikiPyBuffer):
    """ kikipy file buffer """

    # .............................................................................................................
    #                                                     INIT
    # .............................................................................................................

    def __init__(self, editor, filename =""):
       """create a new file object"""
       KikiPyBuffer.__init__(self, editor)
       self.file_path = filename

    # .............................................................................................................
    #                                                 FILE HANDLING
    # .............................................................................................................

    def openFile (self, file_path):
        """loads and displays a python file"""
        try:
            file = open (file_path, "r")
            self.file_path = file_path
        except:
            try: 
                file = open (file_path + ".py", "r")
                self.file_path = file_path + ".py"
            except:
                print "[*** Error ***] unable to open file", file_path
                self.editor.setStatus("file error")
                return 0
    
        self.lines = replaceTabs(file.read(), 8).splitlines()
        if not len(self.lines): self.lines.append("")   # need at least an empty line

        file.close()
        self.title_text = self.file_path
        self.setChanged(0)
        self.setCursor(KikiPos())
        self.color_line_cache = {}
        return 1

    # .............................................................................................................
    def sameFile (self, file_path):
        """returns true, if file_path is the same as buffer file (with or without .py suffix)"""
        if not os.path.exists(file_path):
            file_path = file_path + ".py"
        if not os.path.exists(file_path): return 0
        return os.path.samefile(self.file_path, file_path)

    # .............................................................................................................
    def saveFile (self):
        """saves the buffer content under the current file path"""
        return self.saveFileAs(self.file_path)

    # .............................................................................................................
    def saveFileAs (self, file_path):
        """saves the python file as file_path"""
        # ................................................................. backup
        if os.path.exists(file_path):                           # if file exists ...
            dir, file = os.path.split(file_path)
            import tempfile
            backup =  tempfile.mktemp(file)
            
            import shutil
            shutil.copyfile (file_path, backup)                      # ... copy it to the tmp directory
      
        try:
            file = open (file_path, "w")
        except:
            print "[*** Error ***] unable to open file for writing ", file_path
            self.editor.setStatus("file error")
            return 0
        
        file.write("\n".join(self.lines))
        file.close()

        dir, file = os.path.split(file_path)
        
        import shutil
        shutil.copyfile(file_path, os.path.expanduser("~/Projects/kiki/py/") + file) # copy to project

        self.file_path  = file_path
        self.title_text = self.file_path
        self.setChanged(0)
        
    # .............................................................................................................
    def executeFile (self):
        """execute the loaded file in the interpreter"""
        self.saveFile()
        try:
            self.editor.widget.getPythonWindow().executeFile(self.file_path)
        except:
            console.show()
        else:
            self.editor.hide()                                              # hide python widget
            console.hide()                                                  # and console

    # .............................................................................................................
    #                                                 REGION EDITING
    # .............................................................................................................
    
    def indentRegion (self):
        """indents the selected lines"""
        start, start_line, end, end_line = self.selectionRect()     # sort selection
        for lineIndex in range (start_line, end_line):              # iterate over selected lines
            self.insertTextAtPos("    ", KikiPos(0,lineIndex))          # insert four spaces at the start of line
    
    # .............................................................................................................    
    def outdentRegion (self):
        """outdents the selected lines"""
        start, start_line, end, end_line = self.selectionRect()     # sort selection
        minStart = 1000
        noSpacePat = re.compile(r"\S")                              # compile pattern for non space search
        for lineIndex in range (start_line, end_line):              # find minimum length of leading spaces
            match = noSpacePat.search(self.lines[lineIndex])            # get match for first non space character
            if match:
                minStart = min(match.start(), minStart)
    
        minStart = min(4, minStart)                                 # delete maximum is four
        if minStart:                                                # minimum leading spaces found
            for lineIndex in range (start_line, end_line):              # iterate over selected lines
                self.eraseLine(lineIndex, 0, minStart)                  # delete leading characters
    
    # .............................................................................................................
    def commentRegion (self):
        """comments the selected lines by inserting '###' at start"""
        start, start_line, end, end_line = self.selectionRect()     # sort selection
        for lineIndex in range (start_line, end_line):               # iterate over selected lines
            self.insertTextAtPos("###", KikiPos(0,lineIndex))          # insert '###' at the start of line        
    
    # .............................................................................................................
    def uncommentRegion (self):
        """uncomments the selected lines by deleting leading '###'"""
        start, start_line, end, end_line = self.selectionRect()     # sort selection
        for lineIndex in range(start_line, end_line):               # iterate over selected lines
            if self.lines[lineIndex][:3] == "###":                      # if line starts with '###'
                self.eraseLine(lineIndex, 0, 3)                             # remove first three characters  
    

    # .............................................................................................................
    #                                                  KEYBOARD INPUT
    # .............................................................................................................
    def handleKeyModChar (self, keyName, modName, character):
        """handles a key press"""

        # ................................................... buffer handles key first
        if KikiPyBuffer.handleKeyModChar(self, keyName, modName, character):
            return 1
            
        # ................................................... return
        if keyName == "RETURN" or keyName == "KPENTER":
            self.splitLineAndIndent()                           # split line and indent
            return 1

        # ................................................... control sequences
        if modName:
            # ..................................................................  META
            if modName == "META":
                if keyName == "h":                                              # META_h
                    self.commentRegion()                                            # comment region
                    return 1
                elif keyName == "RIGHTBRACKET":                                 # META_]
                    self.indentRegion()                                             # indent region
                    return 1
                elif keyName == "LEFTBRACKET":                                  # META_[
                    self.outdentRegion()                                            # outdent region
                    return 1
                elif keyName == "r":                                            # META_r
                    self.executeFile()                                          # save and execute file
                    return 1
                elif keyName == "s":                                            # META_s
                    self.saveFile()                                                 # save file
                    return 1
                elif keyName == "u":                                            # META_u
                    self.openFile(self.file_path)                                  # revert to saved file
                    return 1
            elif modName == "SHIFT+META":
                if keyName == "h":                                              # SHIFT+META_h
                    self.uncommentRegion()                                          # uncomment region
                    return 1

        return 0

                    