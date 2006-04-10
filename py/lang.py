# -*- encoding: utf-8 -*-

if Controller.isDebugVersion(): print "[lang.py]"

Controller.language = "english"

lang_list = [  "dutch", "english", "euskara", "francaise", "german",  "portuguese", "spanish", "swedish", ]
lang = {}
for langName in lang_list:
    execfile (kikipy_path + os.path.sep + "lang" + os.path.sep + langName + ".py")

def getLocalizedString(text):
  if lang[Controller.language].has_key(text):
    return lang[Controller.language][text]
  else:
    return text
  
Controller.getLocalizedString = getLocalizedString

del getLocalizedString
