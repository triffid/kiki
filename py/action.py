
if Controller.isDebugVersion(): print "[action.py]"

# .................................................................................................................
class KikiPyActionObject:
    
    def __init__(self):
        self.action_dict = {}

    def performAction(self, name, time):
        if name in self.action_dict:
            if self.action_dict[name][1]:
                self.action_dict[name][1](time)

    def finishAction(self, name):
        if name in self.action_dict:
            if self.action_dict[name][2]:
                self.action_dict[name][2]()       

    def actionFinished(self, name):
        if name in self.action_dict:
            if self.action_dict[name][3]:
                self.action_dict[name][3]()

    def startTimedAction(self, name, time, finished=0):
        """starts the action with name. time is the duration in milliseconds"""
        if name in self.action_dict:
            action = self.action_dict[name][0]
            action.setDuration(time)
            self.action_dict[name][3] = finished
            Controller.timer_event.addAction(action)
        
    def addAction (self, name, perform_cb, finish_cb, finished_cb = 0, mode = KikiAction.ONCE):
        """registers callables perform_cb(time) and finish_cb() as an action with name and mode"""
        self.action_dict[name] = [KikiPyAction (self, name, 0, mode), perform_cb, finish_cb, finished_cb]

# .................................................................................................................
def continuous(*args):
    default_args = ("continuous kikipy action", 0, KikiAction.CONTINUOUS)
    return apply (KikiPyAction, args + default_args[len(args)-1:])

def once(*args):
    default_args = ("kikipy action", 0, KikiAction.ONCE)
    return apply (KikiPyAction, args + default_args[len(args)-1:])