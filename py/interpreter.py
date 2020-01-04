
if Controller.isDebugVersion(): print("[interpreter.py]")

import code
import sys

# .................................................................................................................
#                                             INTERPRETER BUFFER
# .................................................................................................................

class KikiPyInterpreter (KikiPyBuffer, code.InteractiveConsole):
    """ kikipy interpreter buffer """

    # .............................................................................................................
    #                                                  INIT
    # .............................................................................................................
    def __init__(self, editor):
        """initializes the interpreter with an editor"""
        KikiPyBuffer.__init__(self, editor)
        code.InteractiveConsole.__init__(self, globals())
        
        self.title_text = "python"
        
        self.cmd_history = [['']]                       # history of interpreter commandos
        self.cmd_ptr     = 0                            # history index pointer
        self.buffer      = []                           # interpreter buffer
        self.filename    = "kikipython"                 # interpreter filename

    # .............................................................................................................
    def activate(self):
        """activates the buffer"""
        KikiPyBuffer.activate(self)
        sys.stdout       = self                         # redirect in and output to self
        sys.stderr       = self

    # .............................................................................................................
    def clear(self):
        """clears the buffer"""
        self.lines = [""]
        KikiPyBuffer.clear(self)
        
    # .............................................................................................................
    #                                                  INTERPRETE
    # .............................................................................................................
    def splitLineAndInterprete(self):
        """pushes current line to the interpreter"""
        self.splitLine()                                    # split line
        self.setCursor(0, self.lines[self.cursor.y+1])      # cursor to start of next line
        self.cmd_ptr = len(self.cmd_history)-1
        
        buf    = self.buffer                               # save the current interpreter buffer
    
        cmd    = self.lines[self.cursor.y-1]
        retval = self.push(cmd)                             # push previous line to interpreter
    
        if retval:                                          # interpreter says OK, but needs more input
            if not self.lines[self.cursor.y-1].isspace():   # if previous line not empty 
                self.indentLine()                               # indent line
        else:                                               # interpreter swallowed command
            if buf[0] and not self.buffer:
                self.cmd_history[self.cmd_ptr] = buf        # insert interpreter buffer
                self.cmd_ptr += 1
                self.cmd_history.append([''])
            elif len(cmd) and not cmd.isspace():             # and it was not an empty line
                self.cmd_history[self.cmd_ptr] = cmd            # insert line
                self.cmd_ptr += 1
                self.cmd_history.append([''])
    
    # .............................................................................................................
    #                                                  HISTORY
    # .............................................................................................................
    def executeHistory (self):
        for line in self.cmd_history[self.cmd_ptr]:
            self.push(line)
        
    # .............................................................................................................
    def history (self, cmd_offset):
        """inserts or replaces a commando from the commando history"""
        numLines = len(self.cmd_history[self.cmd_ptr])
        for i in range(numLines):
            self.eraseLine(self.cursor.y)               # erase the previously displayed commando
            if self.lines:
                self.setCursor(self.cursor.x, self.cursor.y-1)
            
        self.cmd_ptr = minmax(0, len(self.cmd_history)-1, self.cmd_ptr+cmd_offset) # update the history index pointer
        self.lines.extend(self.cmd_history[self.cmd_ptr])
        self.setCursor(len(self.lines[len(self.lines)-1]), len(self.lines)-1)
                            
    # .............................................................................................................
    def write (self, string):
        """writes the interpreter output"""
        if string == "\n":
            return
    
        if not len(self.lines[len(self.lines)-1]):
            del self.lines[len(self.lines)-1]       # delete last line, if empty
        self.lines.extend(string.splitlines())
        self.lines.append("")
        self.setCursor(len(self.lines[len(self.lines)-1]),len(self.lines))
            
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
            if modName == "CTRL":
                self.executeHistory()
                return 1
            self.setCursor(len(self.lines[self.cursor.y]), self.cursor.y)       # jump to end of line
            self.splitLineAndInterprete()                                       # split line and execute
            return 1

        # ................................................... control sequences
        if modName:
            # ..................................................................  META
            if modName == "META":
                if keyName == "k":                                              # META_k
                    self.clear()                                                    # clear buffer
                    return 1
                    
            # ..................................................................  CTRL
            elif modName == "CTRL":
                if keyName == "UP" or keyName == "DOWN":                        # CTRL_UP and CTRL_DOWN
                    dir = (keyName == "UP" and -1 or 1)
                    self.history(dir)
                    return 1
        return 0
        