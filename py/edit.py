
if Controller.isDebugVersion(): print("[edit.py]")


execfile (kikipy_path + "buffer.py")
execfile (kikipy_path + "interpreter.py")
execfile (kikipy_path + "file.py")

# .................................................................................................................
#                                                   PythonConsole
# .................................................................................................................
 
class PythonConsole:
    """ kiki python console """

    # .............................................................................................................
    #                                                  INIT
    # .............................................................................................................
    def __init__(self, widget):
        """initializes the console with a widget"""
        self.widget      = widget
        self.view_rows   = widget.getTextRows()         # number of visible rows
        self.view_cols   = widget.getTextCols()         # number of visible columns
        self.offset      = 0                            # horizontal text offset
        self.line_offset = 0                            # vertical text offset
        self.inputMode   = ""                           # mode for user input requests
        self.buffer      = KikiPyInterpreter(self)      # currently displayed buffer
        self.buffers     = [self.buffer]                # list of loaded buffers
        self.viewBuffer(0)
    
    # .............................................................................................................
    def setSize (self, cols, rows):
        """callback from widget, if it's size changed""" 
        self.view_rows = rows
        self.view_cols = cols

    # .............................................................................................................
    def viewBuffer (self, index):
        """displays the file with index"""
        index = minmax(0, len(self.buffers)-1, index)
        self.buffer = self.buffers[index]
        self.buffer.activate()

    # .............................................................................................................
    def clearBuffer (self):
        """clears the buffer, if interpreter, resets cursor pos otherwise"""
        self.buffer.clear()

    # .............................................................................................................
    def closeBuffer (self):
        """closes the current buffer"""
        if self.buffer == self.buffers[0]:                      # current buffer is interpreter 
            self.viewBuffer(1)                                      # view next buffer
            return
        if not self.buffer.unchanged:                           # current buffer contains changes
            self.setStatus("!unsaved!")                             # warn
            return                                                  
        buffer_index = self.buffers.index(self.buffer)
        del self.buffers[buffer_index]                          # delete current buffer
        self.viewBuffer(buffer_index)                               # view next buffer

    # .............................................................................................................
    def openFile (self, file_path):
        """loads and displays a python file"""
        for buffer in self.buffers:
            if isinstance(buffer, KikiPyFile) and buffer.sameFile(file_path):
                self.viewBuffer(self.buffers.index(buffer))
                return
        file_buffer = KikiPyFile(self)
        if file_buffer.openFile(file_path):
            self.buffers.append(file_buffer)
            self.buffer = file_buffer
            self.viewBuffer(len(self.buffers)-1)
        else:
            del  file_buffer
        
    # .............................................................................................................
    #                                                  DISPLAY
    # .............................................................................................................
    
    def displayText (self):
        """display the text of current file or interpreter"""
        self.updateCursor ()
        pos = KikiPos()
        display_pos = KikiPos(-self.offset, 0)
        self.buffer.text_color.glColor()
    
        for lineIndex in range(self.line_offset, min(self.line_offset + self.view_rows, len(self.buffer.lines))):
            
            line = self.buffer.lines[lineIndex]
            if self.buffer.color_syntax:
                if lineIndex in self.buffer.color_line_cache:
                    matches = self.buffer.color_line_cache[lineIndex]
                else:
                    matches = []
            
                    for patternIndex in range(len(self.buffer.syntax_colors)):
                        matches.extend([(mo.span(), patternIndex) for mo in \
                                self.buffer.syntax_colors[patternIndex][0].finditer(line)])
                                
                    matches.sort(lambda a, b: a[0][0]-b[0][0] or b[0][1]-a[0][1])
                
                    self.buffer.color_line_cache[lineIndex] = matches
                            
                for match in matches:
                    if match[0][0] > pos.x:                         # match start > pos 
                        self.buffer.text_color.glColor()                # display default text
                        self.widget.displayStringAtPos(line[pos.x:match[0][0]], display_pos)
                        pos.x = match[0][0]
                        display_pos.x = pos.x-self.offset
                    if match[0][0] == pos.x:                        # match start == pos
                        self.buffer.syntax_colors[match[1]][1].glColor()       # display match
                        self.widget.displayStringAtPos(line[pos.x:match[0][1]], display_pos)
                        pos.x = match[0][1]
                        display_pos.x = pos.x-self.offset
        
                if pos.x < len(line):
                    self.buffer.text_color.glColor()
                self.widget.displayStringAtPos(line[pos.x:], display_pos)
            else:
                self.widget.displayStringAtPos(line[self.offset:], pos)
                
            pos.x  = 0
            display_pos.x = -self.offset
            pos.y += 1
            display_pos.y += 1
    
    # .............................................................................................................
    def updateCursor (self):
        """maps and sets the cursor and selection positions to window coordinates"""
        offsetPos = KikiPos(self.offset, self.line_offset)
        self.widget.cursorPos    = self.buffer.cursor - offsetPos
        self.widget.selectionPos = self.buffer.selection - offsetPos
    
    # .............................................................................................................
    def updateScrollBar (self):
        """notifies the python window about text changes for scrollbar updates"""
        kiki.Controller.python.setScrollBarUnits(self.line_offset, len(self.buffer.lines))
    
    # .............................................................................................................
    def setStatus (self, text):
        """displays text in the status line"""
        self.widget.getPythonWindow().setStatus(text)
    
    def setTitle (self, text):
        """displays text in the title line"""
        self.widget.getPythonWindow().setTitle(str(text))
        
    def setInput (self, text):
        """displays text in the input line"""
        self.widget.getPythonWindow().setInput(text)
    
    def hide (self):
        self.widget.getPythonWindow().setVisibility(0)
         
    # .............................................................................................................
    #                                                  SCROLLING
    # .............................................................................................................
    
    # .............................................................................................................
    def scrollToCursor (self):
        """scrolls to the cursor position"""
        if self.buffer.cursor.y < self.line_offset:                                   # cursor is above top line
            self.line_offset = max(0, self.buffer.cursor.y)
            self.updateScrollBar()
        elif self.buffer.cursor.y > self.line_offset + self.view_rows - 1:            # cursor is below bottom line 
            self.line_offset = min(len(self.buffer.lines) - self.view_rows + 1, \
                                    self.buffer.cursor.y - self.view_rows + 1)
            self.updateScrollBar()
            
        if self.buffer.cursor.x < self.offset:                                         # cursor is to the left
            self.offset = max(0, self.buffer.cursor.x)
        elif self.buffer.cursor.x > self.offset + self.view_cols - 1:                  # cursor is to the right  
            self.offset = min(len(self.buffer.lines[self.buffer.cursor.y]) - self.view_cols + 1, \
                                    self.buffer.cursor.x - self.view_cols + 1)
    
    def scrollRelative (self, value):
        """scrolls to relative text position value (should be in range [0,1])"""
        self.line_offset = int(max(0, value * (len(self.buffer.lines) - self.view_rows)))
    
    # .............................................................................................................
    def scrollRelY (self, y):
        self.line_offset = minmax(0, max(len(self.buffer.lines) - self.view_rows, 0), self.line_offset+y)
        self.buffer.setCursor(self.buffer.cursor.x, \
                                minmax(self.line_offset, self.line_offset+self.view_rows, self.buffer.cursor.y))
    
    # .............................................................................................................
    def scrollLineDown (self):
        self.scrollRelY(+1)
    
    # .............................................................................................................
    def scrollLineUp (self):
        self.scrollRelY(-1)
    
    # .............................................................................................................
    def scrollPageUp (self):
        self.scrollRelY(-self.view_rows);
    
    # .............................................................................................................
    def scrollPageDown (self):
        self.scrollRelY(self.view_rows);
    
    # .............................................................................................................
    def scrollToTop (self):
        self.scrollRelY(-self.line_offset);
    
    # .............................................................................................................
    def scrollToBottom (self):
        self.scrollRelY(len(self.buffer.lines));
            
    # .............................................................................................................
    #                                                  MOUSE INPUT
    # .............................................................................................................
    
    def picked (self, pos):
        """starts editing and sets the cursor at picked position"""
        newPos = self.convertFromWindowPos(pos)
        self.buffer.setCursor(newPos.x, newPos.y)

    # .............................................................................................................
    def doubleClicked (self):
        """selects to word boundaries to the left and the right of the cursor position"""
        self.buffer.handleDoubleClick()

    # .............................................................................................................
    def mouseMoved (self, pos):
        """updates the selection (and scrolls the widget, if neccessary (not implemented yet))"""    
        self.buffer.selection = self.convertFromWindowPos(pos)

    # .............................................................................................................
    def convertFromWindowPos (self, wpos):
        """returns the position wpos in window coordinates as a KikiPos in text coordiates"""
        return KikiPos(wpos[0] + self.offset, wpos[1] + self.line_offset)
    
    # .............................................................................................................
    #                                                          USER INPUT
    # .............................................................................................................
    def requestUserInput (self, mode):
        """paste selected characters"""
        self.input_mode = mode
        kiki.Controller.python.requestUserInput(mode)
    
    # .............................................................................................................
    def userInput (self, input):
        """handles the user input in from the input line"""
        if self.input_mode == "find":
            self.buffer.findAndGotoText (input)
        elif self.input_mode == "open":
            self.openFile(input)     
        elif self.input_mode == "goto":
            self.buffer.setCursor(0, int(input)-1)
    
    # .............................................................................................................
    #                                                  KEYBOARD INPUT
    # .............................................................................................................

    def handleKey (self, key, character):
        """handles a key press"""
        
        # ................................................... extract mod- and key name
        modName = ""
        keyName = key
        if key.find("_") != -1:
            modName = key.split("_")[0]
            keyName = key.split("_")[1]

        # ................................................... ignore modifier keys
        if key == "SHIFT" or key == "CTRL" or key == "META" or key == "ALT": 
            return 1
            
        # ................................................... forward key to buffer
        if self.buffer.handleKeyModChar(keyName, modName, character):
            return 1

        # ................................................... control sequences
        if modName:
            # ..................................................................  META
            if modName == "META":                                             
                if keyName == "i":                                              # META_i
                    self.viewBuffer(0)                                              # go to interpreter
                    return 1
                elif keyName == "o":                                            # META_o
                    self.requestUserInput("open")                                   # open file
                    return 1
                elif keyName == "SPACE":                                        # META_SPACE
                    prev_index = self.buffers.index(self.buffer)-1
                    if prev_index < 0:
                        prev_index = len(self.buffers)-1
                    self.viewBuffer(prev_index)                                # previous buffer
                    return 1
            elif modName == "SHIFT+META":
                if keyName == "w":
                    self.closeBuffer()
                    return 1

# ................................................................................. setup python console

pythonConsole = PythonConsole(kiki.Controller.python.getPythonWidget())

kiki.Controller.python.setPosition((0,0))
kiki.Controller.python.setSize((1024,695))
