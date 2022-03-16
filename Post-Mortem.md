*Archived from http://www.idevgames.com/postmortems/kiki-the-nanobot*

# Kiki the Nanobot

Posted on December 21st, 2002 by Thorsten Kohnhorst  
Postmortems : C++, OpenGL, Python, scripting, SDL, Sokoban, SWIG, uDevGames


# What Went Right
## The Idea

Three months is still a very short time, so I knew I had to come up with a very simple idea and stick to it in order to finish before the deadline. Sokoban came to my mind, which I really love. I decided to create a game with rules of similar simplicity but as many possibilities for complex and mind-challenging puzzles. Since it was clear from the beginning that the game would be 3-dimensional, the decision to implement a user interaction scheme similar to Kula-World was quite obvious.

When discussing this plan with my friend Rolf, we came up with several ideas for different game items and mechanics. Most of them were just copies or simple alterations of ideas we knew from other games. But there was one exception: the idea of an unusual physics with a subjective gravity, a gravity that has no fixed orientation in space, but one that is bound to the player and changes with its orientation. Letting the game take place in the nano world was a good solution for explaining the altered physics. But it could also be used as an excuse for simple graphics and other glitches that might appear. Altogether I was very happy that I quickly found a simple but appealing idea with some originality in it. Highly motivated, I began to evaluate which tools I would use.

## The Tools

I knew I wanted to reuse some of the code I wrote for my previous project, mainly some basic vector, matrix, quaternion, and projection utilities. I also wanted to avoid long compile times and do some rapid prototyping in Python. After evaluating some systems to bridge between C++ and Python, I chose SWIG, which I can highly recommend. I’ve never written a program with sound output before, so I tried the SDL_mixer library, because I already appreciated the well-done SDL framework. There was no need to look for other solutions, since the sound system I hacked together in a few hours worked perfectly for me and I felt no reason to touch it again, despite its probably quite naive implementation. Compliments and thanks to the author for this very nice library.

The shareware program Amadeus II was my choice for simple sound editing tasks. After trying some free modelers, I found that Wings3d is the best solution for me because of its stability and ease of use. I feel that the time I spent with these evaluations (approximately a week) was worth it, since I found a couple of free but very good libraries and tools that enabled me to be quite productive.

## Planning

Since I was the only person on this project, I felt no need for a formalized design and project plan. Nevertheless, I knew I had to focus on a small set of predefined features and estimate the time needed for their implementation. The rough project plan I sketched has been a good approximation. Despite some unforeseeable problems, I managed to finish the game in time and without any stress. When looking back, I think that defining the scope and features of the game beforehand has been of even more importance. The first playable version of the game was finished quite fast and I have very often been tempted to add more features. With a few exceptions, the feature list prevented me from doing this and enabled me to concentrate on improvements instead.
Scripting

If somebody would ask me: “What is the one best thing you have learned by doing this project?” I would surely answer: “Discovering the power of scripting in general and the coupling of C++ and Python especially.” The time I saved by being able to test the various aspects of the program and change its parameters in real time, without having to recompile it, was simply invaluable. Thanks to SWIG, I could easily export almost all the C++ classes and methods to the python interpreter running inside the game. This not only eliminated the need for implementing a level editor, but also helped a lot in many different situations. The last time I programmed in Python was years ago. I am amazed at how mature this language and the accompanying libraries (modules) became in the meantime. Many compliments go to the people who developed it!

# What Went Wrong

## Design

The player movement turned out to be much more complicated than planned. But instead of redesigning the whole mechanism to fit the unforeseen needs in an early stage, I hacked around the initial structure and soon got quite a mess. This introduced some runtime bugs which were very hard to find (or still unsolved), mainly because I have problems understanding my own code now. But the worst thing is that the whole system virtually isn’t extensible anymore. If I had changed the design early enough, possible additions like moving sideways or jumping backwards would have been much easier to integrate. I honestly think this is the only thing that really went wrong. But let me try to summarize some things that have been ‘sub-optimal.’
Shadows

As mentioned above, I lost my focus sometimes and implemented features that hadn’t been planned. This wasn’t a problem as long as they improved the game, but on one occasion it was a real waste of time, since I didn’t use any of the code I created for days. This was when I tried to implement shadows. After I got the first version of the shadow system working, I realized that shadows were absolutely not fitting into the overall design of the game. Instead of adding some ‘realism’ to the world, they just made it look confusingly complex. Additionally, a proper implementation would have been very time consuming since I didn’t anticipate the clash with the quite heavily used transparency.

## Lighting

When I compiled and ran the game the first time on Jaguar, the lighting was broken. This has been very annoying, since the optical appeal of the game completely depends on the lighting instead of texturing. After some days of debugging I came to the conclusion that there must be a bug in the OpenGL implementation of the new Jaguar release and asked for help in Apple’s OpenGL mailing list. After getting no immediate reply, I obsessively tried to find a workaround myself. Eventually I found one, but the frustrating process of finding it almost drained all my motivation. Looking back, I should have asked for help earlier while anticipating some time for its arrival, since a nice person sent me another workaround later.

# Conclusion

I learned a lot while making this game. I surely will continue to use the C++/SWIG/Python combination in future projects but I will probably drop the inclusion of the frameworks inside the application bundle. I will also try to improve my design capabilities and refactor more mercilessly in the future. Asking for feedback in the iDevGames forum has been a good idea and I hope to exchange more experiences on the web and in mailing lists. I am planning to port the game to Linux and Windows with my friend Znek in the next months and I will certainly take part in the next competition, if I have time then. There is already an idea for the next game growing in my head. I had a lot of fun developing the game and taking part in the competition. I am quite proud of the work I have done and it makes me happy that some people like the game as well and provided me with valuable feedback. I would like to thank the organizers, participants, and sponsors of the uDevGames Contest, the people playing, voting and providing feedback for the games, and the many people programming, documenting and maintaining Open Source programs and libraries.

* Genre: 3d puzzle
* Developer: Thorsten Kohnhorst
* Url: http://kiki.sourceforge.net/
* Team size: 1
* Released date: November 15, 2002
* Project length: 3 months
* Development hardware: Cube 450MHz G4 and iBook 500MHz G3
* Critical applications: Apple’s Development Tools, Python, SDL, Wings3d, SWIG
