
# .................................................................................................................
#                                                   KikiPyBuffer
# .................................................................................................................
 
class KikiPyBuffer:
    """ kikipy buffer """

    # .............................................................................................................
    #                                             CLASS ATTRIBUTES
    # .............................................................................................................

    copy_buffer = []    
    find_string = ""
    
    # .............................................................................................................
    #                                                  INIT
    # .............................................................................................................

    def __init__ (self, editor):
        """initializes the console with a widget"""
        self.editor      = editor
        self.cursor      = KikiPos()                    # cursor pos
        self.selection   = KikiPos()                    # selection pos
        self.unchanged   = 1                            # flag for indicating unsaved changes
        self.lines       = [""]                         # the text buffer
        self.title_text  = "buffer"
        self.color_line_cache = {}                      # cache for syntax colored lines
        self.undo_buffer = []                           # undo buffer
        self.initialize()                               # initialize the syntax colors 

    # .............................................................................................................
    def initialize (self):
        """initializes the syntax color search patterns and colors"""
        self.syntax_colors = (
            (re.compile(r"\"{3}.*?\"{3}"),                     KColor(0.1,0.5,0.0)),   # doc strings
            (re.compile(r"\"{1}.*?(?<!(?<!\\)\\)\"{1}"),       KColor(0.7,0.0,0.0)),   # strings
            (re.compile(r"#.*$"),                              KColor(0.3,0.3,0.3)),   # comments
            (re.compile(r"\bself\.?|__class__\.?"),            KColor(0.5,0.5,0.0)),   # self, __class__
            (re.compile(r"((?<=def )|(?<=class )).*?((?=\()|(?=:))"), KColor(1.0,1.0,0.0)),   # class and def names   
            (re.compile(r"\bif\b|\belif\b|\belse:|\btry:|\bexcept:?\b|:\s*(#.*)?$"),   KColor(0.4,0.4,0.7)),
            (re.compile(r"\bfor\b|\brange\b|\bin\b|\blambda\b|\bimport\b|\bfrom\b|\bwhile\b"),  KColor(0.1,0.2,1.0)),
            (re.compile(r"(\breturn\b|\bdel\b)"),              KColor(1.0,0.0,0.0)),   # return and del
            (re.compile(r"(\d+(\.\d+)?)|(?<=[><(-+= ])(len|min|max)(?=\ ?\()"), KColor(0.5,0.5,1.0)), # digits,len,min,max       
            (re.compile(r"\band\b|\bor\b|\bnot\b|==|<>|>=|<=|>|<"),  KColor(0.9,0.9,0.0)),         # logic & comparison
            (re.compile(r"\bprint\b"),                         KColor(0.0,1.0,0.0)),   # print
        )
        self.text_color  = KColor(0.8,0.8,0.8)
        self.color_syntax = 1
    
    # .............................................................................................................
    def activate(self):
        """activates the buffer"""
        sys.stdout = KConsole                           # redirect interpreter output to console
        sys.stderr = KConsole
        self.setChanged(not self.unchanged)             # just to update title bar
        self.setCursor(self.cursor.x, self.cursor.y)    # also scrolls the window and resets the selection

    # .............................................................................................................
    def clear(self):
        """resets the cursor"""
        self.setCursor(0, 0)
        
    # .............................................................................................................
    def setChanged (self, changed = 1):
        """displays the changed flag in the title"""
        if changed:
            self.editor.setTitle("*"+self.title_text+"*")
        else:
            self.editor.setTitle(self.title_text)
        self.unchanged = not changed
        
    # .............................................................................................................
    def handleDoubleClick (self):
        """selects to word boundaries to the left and the right of the cursor position"""
        line = self.lines[self.cursor.y]                            # get the current line
        if not len(line):                                           # if line empty
            return                                                      # do nothing
        self.selection.y = self.cursor.y                            # reset the selection 
    
        if self.cursor.x > len(line)-1:                             # if clicked behind line end
            self.setCursor(0, self.cursor.y, 0)                         # select whole line
            self.selection.x = len(line)
            return 
    
        char_pos = max(0, self.cursor.x)
        character = line[char_pos]                                  # get the character at cusor pos
        if self.findMatchingBracketPos():
            console.out("it's a klammer :-)")
            
        word_pattern = re.compile((character == " ") and r"\s+" or r"\w+")
        matches = word_pattern.finditer(line)
        match = 0
        for match in matches:
            if match.span()[0] <= char_pos and match.span()[1] > char_pos: break
        if match:
            self.setCursor(match.span()[0], self.cursor.y, 0)
            self.selection.x = match.span()[1]

    # .............................................................................................................
    #                                                  TEXT EDITING
    # .............................................................................................................

    # .............................................................................................................
    def undo (self, n =1):
        """performs n undo operations"""
        num_ops = len(self.undo_buffer)
        if not num_ops: 
            self.editor.setStatus("no undo")
            return

        type, pos, text = self.undo_buffer[-1]     
        x, y = pos

        self.setCursor(x, y)
        
        if type == "insert":
            self.eraseLine(y, x, x+len(text))
        elif type == "erase":
            self.insertTextAtPos(text, KikiPos(x,y))
        elif type == "del":
            self.lines[y:y] = text
            self.lineChanged(y)
        elif type == "new":
            del self.lines[y:y+len(text)]
            self.lineChanged(y)
        elif type == "split":
            self.joinLine()
        elif type == "join":
            self.splitLine()
        elif type == "multi":
            del self.undo_buffer[num_ops-1]
            self.undo(text)
            
        del self.undo_buffer[num_ops-1:]          # delete undo entries for undo operations

        self.setCursor(x, y)
        
        if n > 1:
            for i in range (1,n): self.undo()

    # .............................................................................................................
    def lineChanged (self, lineIndex, numberChanged=1):
        """invalidates color line cache for all lines below lineIndex and updates the title bar, if first change"""
        if numberChanged:
            for index in range(lineIndex, len(self.lines)-1):
                if index in self.color_line_cache:
                    del self.color_line_cache[index]
            self.editor.updateScrollBar()
        else:
            if lineIndex in self.color_line_cache:
                del self.color_line_cache[lineIndex]
            
        if self.unchanged:
            self.setChanged()
    
    # .............................................................................................................
    def eraseLine (self, lineIndex, start=0, end=-1):
        """erases characters from start to end in line"""
        if start == 0 and end == -1:                                # if default arguments
            self.undo_buffer.append(("del", (0, lineIndex), [self.lines[lineIndex]]))
            del(self.lines[lineIndex])                                  # delete whole line
            self.lineChanged(lineIndex)
            return
        line = self.lines[lineIndex]
        if end == -1: end = len(line)                               # default end=-1 for end of line
        if start < end:
            self.undo_buffer.append(("erase", (start, lineIndex), line[start:end]))
            line = line[:start]+line[end:]
            self.lines[lineIndex] = line
            self.lineChanged(lineIndex)
    
    # .............................................................................................................
    def splitLineAndIndent (self):
        """splits the line at cursor pos, indents cleverly"""
        self.splitLine()                                            # split line
        self.setCursor(0, self.cursor.y+1)                          # set cursor to start of next line
        self.indentLine()                                           # indent line
        
    # .............................................................................................................
    def indentLine (self):
        """indents current line. indent depends on characters and trailing ':' on previous line"""
        start  = 0
        indent = re.search(r":\s*(#.*)?$", self.lines[self.cursor.y-1]) and 4 or 0
    
        match = re.search(r"\S", self.lines[self.cursor.y-1])         # get match for first non space character
        if match:                                                   # if non space found
            start = match.start()                                       # indent next line to same level
        self.insertTextAtPos("".ljust(start+indent), KikiPos(0, self.cursor.y))
        self.setCursor(start+indent, self.cursor.y)
    
    # .............................................................................................................
    def splitLine (self):
        """splits the current line at cursor position"""
        self.undo_buffer.append(("split", (self.cursor.x, self.cursor.y), 0))
        line = self.lines[self.cursor.y]
        self.lines[self.cursor.y] = line[:self.cursor.x]
        self.lines.insert(self.cursor.y+1, line[self.cursor.x:])
        self.lineChanged(self.cursor.y)
    
    # .............................................................................................................    
    def joinLine (self):
        """joins the current line with the next line"""        
        self.undo_buffer.append(("join", (self.cursor.x, self.cursor.y), 0))
        line = self.lines[self.cursor.y]+self.lines[self.cursor.y+1]
        self.lines[self.cursor.y] = line
        del(self.lines[self.cursor.y+1])
        self.lineChanged(self.cursor.y)
            
    # .............................................................................................................
    def insertText (self, text):
        """insert text at cursor position"""
        if text:
            self.undo_buffer.append(("insert", (self.cursor.x, self.cursor.y), text))
            line = self.lines[self.cursor.y];
            line = line[0:self.cursor.x]+text+line[self.cursor.x:]
            self.lines[self.cursor.y] = line
            self.lineChanged(self.cursor.y, 0)
    
    # .............................................................................................................
    def insertTextAtPos (self, text, pos):
        """insert text at position pos"""
        if text:
            self.undo_buffer.append(("insert", (pos.x, pos.y), text))
            self.lines[pos.y] = self.lines[pos.y][0:pos.x]+text+self.lines[pos.y][pos.x:]
            self.lineChanged(pos.y, 0)
    
    # .............................................................................................................
    def delSelection (self):
        """erase selected characters"""
        if self.selectionEmpty():                                       # nothing to delete
            return
        start, start_line, end, end_line = self.selectionRect()         # sort selection
        if start_line == end_line:                                      # single line selection
            self.eraseLine(start_line, start, end)
            self.cursor.x = self.selection.x = start
            self.lineChanged(self.cursor.y, 0)
            return
        else:                                                           # multi line selection
            undo_ops = len(self.undo_buffer)
            self.eraseLine(end_line, end=end)                               # erase last line
            self.undo_buffer.append(("del", (0, start_line+1), self.lines[start_line+1:end_line])) # fill undo buffer
            del self.lines[start_line+1:end_line]                           # erase lines between last and first
            self.eraseLine(start_line, start)                               # erase first line
            self.cursor.y = self.selection.y = start_line
            self.cursor.x = self.selection.x = start
            if start or end:
                self.joinLine()
            else:
                self.lineChanged(self.cursor.y)
            self.undo_buffer.append(("multi", (self.cursor.x, self.cursor.y), len(self.undo_buffer) - undo_ops))
    
    # .............................................................................................................    
    def cut (self):
        """cut selected characters"""
        if self.selectionEmpty(): return                               # nothing to delete -> return        
        self.__class__.copy_buffer = self.selectionText()
        self.delSelection()     
    
    # .............................................................................................................
    def copy (self):
        """copy selected characters"""
        self.__class__.copy_buffer = self.selectionText()
    
    # .............................................................................................................
    def paste (self):
        """paste selected characters"""
        undo_ops = len(self.undo_buffer)
        self.delSelection()
        if len(self.__class__.copy_buffer) == 1:
            self.insertText(self.__class__.copy_buffer[0])
            self.setCursor(self.cursor.x + len(self.__class__.copy_buffer[0]), self.cursor.y)
        elif len(self.__class__.copy_buffer) > 1:
            self.splitLine()
            self.insertText(self.__class__.copy_buffer[0])
            self.undo_buffer.append(("new", (0, self.cursor.y+1), self.__class__.copy_buffer[1:]))
            self.lines[self.cursor.y+1:self.cursor.y+1] = self.__class__.copy_buffer[1:]
            self.lineChanged(self.cursor.y)
        self.undo_buffer.append(("multi", (self.cursor.x, self.cursor.y), len(self.undo_buffer) - undo_ops))

    # .............................................................................................................
    #                                                  FIND
    # .............................................................................................................
    def findAndGotoText (self, text):
        """searches for the next occurence of text and if found, selects it"""
        self.__class__.find_string = text
        result = self.findTextFromPos(text, self.cursor + KikiPos(1,0))
        if result:
            self.setCursor(result.x, result.y)
            self.selection = self.cursor + KikiPos(len(text), 0) 
        else:
            self.editor.setStatus("not found")
    
    # .............................................................................................................
    def findTextFromPos (self, text, pos):
        """searches for the next occurence of text and returns it's position or None, if nothing found"""
        lineIndex = pos.y
        result    = self.lines[lineIndex].find(text, pos.x)
        
        while result == -1 and lineIndex+1 < len(self.lines):
            lineIndex += 1
            result = self.lines[lineIndex].find(text)
            
        if result <> -1: return KikiPos(result,lineIndex)
        
        lineIndex = -1
        while result == -1 and lineIndex+1 < pos.y:
            lineIndex += 1
            result = self.lines[lineIndex].find(text)
            
        if result <> -1: return KikiPos(result,lineIndex)
        return None
        
    # .............................................................................................................
    def findMatchingBracketPos (self):
        """searches the matching bracket for the bracket below the cursor"""
        bdict = {"(": (")", 1), "{": ("}", 1), "[": ("]", 1), ")": ("(", -1), "}": ("{", -1), "]": ("[", -1)}
        c = self.lines[self.cursor.y][self.cursor.x]
        if c in bdict:
            console.out("is in bdict")
        if self.lines[self.cursor.y][self.cursor.x] in ("{", "(", "["):
            console.out("klammer vorwaerts")
        elif self.lines[self.cursor.y][self.cursor.x] in ("}", ")", "]"):
            console.out("klammer rueckwaerts")
        else:
            return 0
        return (0,0)

    # .............................................................................................................
    #                                                  CURSOR
    # .............................................................................................................
    
    # .............................................................................................................
    def setCursor (self, x=0, y=0, resetSelection=1):
        """sets the cursor position to the next valid pos near (x, y)"""
        new_y  = minmax(0, len(self.lines)-1, y)                               # get a valid line number
        new_x  = minmax(0, len(self.lines[new_y]), x)                          # get a valid column number
        self.cursor = KikiPos(new_x, new_y)
        self.editor.scrollToCursor ()
        if resetSelection:
            self.selection = KikiPos(self.cursor)
        
    # .............................................................................................................
    def advanceCursor (self, x, resetSelection=1):
        """moves the cursor position advanced by x characters"""
        new_x = self.cursor.x+x
        if new_x < 0 and self.cursor.y > 0: 
            self.cursor.y -= 1
            new_x  = len(self.lines[self.cursor.y]);  
        elif new_x > len(self.lines[self.cursor.y]) and self.cursor.y < len(self.lines)-1:
            new_x  = 0
            self.cursor.y += 1
            
        self.cursor.x = minmax(0, len(self.lines[self.cursor.y]), new_x)
        self.editor.scrollToCursor ()
        if resetSelection:
            self.selection = KikiPos(self.cursor)
                
    # .............................................................................................................
    #                                               SELECTION
    # .............................................................................................................
    
    # .............................................................................................................
    def selectionEmpty (self):
        """returns true if nothing selected"""
        return self.selection.x == self.cursor.x and self.selection.y == self.cursor.y
    
    # .............................................................................................................
    def selectionRect (self):
        """returns the sorted start and end position of the selection as four values
            the end position lies always below the start position (or to the right if on same line) 
        """
        cy = self.cursor.y;
        cx = self.cursor.x; 
        sy = min(len(self.lines)-1, self.selection.y)
        sx = min(self.selection.x, len(self.lines[sy]))
        return (cy < sy or (cy == sy and cx <= sx)) and (cx, cy, sx, sy) or (sx, sy, cx, cy)
    
    # .............................................................................................................
    def selectionText (self):
        """returns the selection as a list of strings"""
        start, start_line, end, end_line = self.selectionRect()
        if start_line == end_line:                              # single line selection
            return [self.lines[start_line][start:end]]              # return list with selected text
        else:                                                   # multi line selection
            copy_lines = [self.lines[start_line][start:]]           # insert last part of first line
            copy_lines[1:1] = self.lines[start_line+1:end_line]     # insert lines between
            copy_lines.append(self.lines[end_line][:end])           # append first part of last line
            return copy_lines                                       # return the list
    
    # .............................................................................................................
    #                                             KEYBOARD INPUT
    # .............................................................................................................
    def handleKeyModChar (self, keyName, modName, character):
        """handles a key press"""

        # ................................................... simple character
        if len(keyName) == 1 and not modName:
            self.delSelection()
            self.insertText(keyName)
            self.cursor.x += 1
            self.selection.x += 1
            return 1
                
        if not modName or modName == "SHIFT":
            reset_selection = not modName
            # ................................................... backspace
            if keyName == "BACKSPACE":
                if self.selectionEmpty():                           # if selection empty
        
                    prev_tab_pos = 0                                    # calculate previous tab position
                    if self.cursor.x % 4:                               
                        prev_tab_pos = (self.cursor.x/4)*4
                    else:
                        prev_tab_pos = self.cursor.x - 4
                        
                    if prev_tab_pos < 0:                                # if tabpos at start of line
                        if self.cursor.y > 0:                               # if not in first line
                            self.setCursor(len(self.lines[self.cursor.y-1]), self.cursor.y-1)
                            self.joinLine()                                     # join this with previous line
                        return 1                                                # return
                    
                    self.selection.x = self.cursor.x-1                  # select previous character
                    if self.lines[self.cursor.y][self.selection.x] == " ":  # if previous character is space
                        while self.selection.x > prev_tab_pos and \
                                self.lines[self.cursor.y][self.selection.x-1] == " ": 
                            self.selection.x -= 1                               # select to previous tabpos
                    
                self.delSelection()                                 # delete the selection            
                return 1
            # ................................................... delete
            if keyName == "DELETE":
                if self.selectionEmpty():
                    self.selection.x = self.cursor.x + 1
                    if self.selection.x > len(self.lines[self.cursor.y]):
                        if self.cursor.y < len(self.lines)-1:      # join this with next line
                            self.joinLine()
                            self.selection = KikiPos(self.cursor)
                        else:
                            self.selection = KikiPos(self.cursor)  # end of file, reset selection
                        return 1
                        
                self.delSelection()
                return 1
            # ................................................... cursor keys
            if keyName == "UP" or keyName == "DOWN":                                # UP and DOWN
                dir = (keyName == "UP" and -1 or 1)
                self.setCursor(self.cursor.x, self.cursor.y + dir, reset_selection)
                return 1
                                    
            if keyName == "LEFT" or keyName == "RIGHT":                             # LEFT and RIGHT
                self.advanceCursor(keyName == "LEFT" and -1 or 1, reset_selection)
                return 1
            # ................................................... home end page up & down
            if keyName == "END":                                                    # END
                self.setCursor(0, len(self.lines), reset_selection)
                return 1
            if keyName == "HOME":                                                   # HOME
                self.setCursor(0, 0, reset_selection)
                return 1
            if keyName == "PAGEUP":                                                 # PAGEUP
                self.setCursor( self.cursor.x, \
                                self.cursor.y - self.editor.view_rows + 1, \
                                reset_selection)
                return 1
            if keyName == "PAGEDOWN":                                               # PAGEDOWN
                self.setCursor( self.cursor.x, \
                                self.cursor.y + self.editor.view_rows - 1, 
                                reset_selection)
                return 1
        # ................................................... control sequences
        else:
            # ..................................................................  CTRL
            if modName.find("CTRL") <> -1:
                reset_selection = (modName.find("SHIFT") == -1)
                if keyName == "a":                                              # CTRL_a
                    self.setCursor(0, self.cursor.y, reset_selection)               # cursor to start of line
                    return 1
                elif keyName == "e":                                            # CTRL_e
                    self.setCursor(len(self.lines[self.cursor.y]),self.cursor.y,reset_selection)# cursor to end of line
                    return 1
                elif keyName == "k":                                            # CTRL_k -> delete (to end of) line
                    self.selection = KikiPos(self.cursor)                           # reset selection
                    if not len(self.lines[self.cursor.y]):                          # if line empty
                        self.eraseLine(self.cursor.y)                                   # delete line
                    else:                                                           # else
                        self.selection.x = len(self.lines[self.cursor.y])               # select to end of line
                        self.delSelection()                                             # delete selection
                    return 1
                elif keyName == "s":                                            # CTRL_s
                    self.color_syntax = not self.color_syntax                      # toggle syntax coloring
                    return 1
                return 0
            # ..................................................................  META
            elif modName == "META":                                             # META
                if keyName == "c":                                              # META_c
                    self.copy()                                                     # copy
                    return 1
                elif keyName == "v":                                            # META_v
                    self.paste()                                                    # paste
                    return 1
                elif keyName == "z":                                            # META_z
                    self.undo()                                                     # undo
                    return 1
                elif keyName == "x":                                            # META_x
                    self.cut()                                                      # cut
                    return 1
                elif keyName == "f" or keyName == "g":                          # META_f and META_g
                    if keyName == "g" and self.__class__.find_string:               # META_g
                        self.findAndGotoText(self.__class__.find_string)                # repeat last find
                    elif self.selectionEmpty() or self.selection.y <> self.cursor.y:# if nothing selected
                        self.editor.requestUserInput("find")                            # request search string
                    else:                                                           # else
                        self.findAndGotoText(self.selectionText()[0])                   # search selected string
                    return 1
                elif keyName == "l":                                            # META_l
                    self.editor.requestUserInput("goto")                             # goto line
                    return 1
                elif keyName == "a":                                            # META_a
                    self.cursor = KikiPos()                                         # set cursor to [0,0]
                    self.selection.y = len(self.lines)-1                            # set selection to end ...
                    self.selection.x = len(self.lines[self.selection.y])            # of last line
                    return 1
                return 0
            elif modName == "SHIFT+META":
                if keyName == "z":
                    self.undo_buffer = []
                    return 1
                return 0
            else:
                return 0                                                      # don't handle undefined mods
                
        # ................................................... insert text
        
        self.delSelection() # always cut the selection before entering new text
        
        # ................................................... map and insert character
    
        if keyName == "TAB":
            chars = "".ljust(4 - self.cursor.x % 4)
        elif not modName and keyName == "BACKSLASH":
            chars = '\\'
        elif not modName and keyName == "QUOTE":
            chars = '\''
        elif character and 32 <= ord(character) <= 126:
            chars = character                  # simply use the character
        else:
            return 0
    
        self.insertText(chars)
        self.cursor.x += len(chars)
        self.selection.x += len(chars)
        
        return 1
        