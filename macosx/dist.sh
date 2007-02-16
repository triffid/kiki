#!/bin/sh

# dist [version] will produce kiki-[version].dmg from files in dist folder

rm -rf release/kiki-$1.dmg
hdiutil create -format UDZO -uid 99 -gid 99 -volname kiki -srcfolder build/Release release/kiki-$1.dmg
hdiutil eject /Volumes/kiki
open release/kiki-$1.dmg
