#!/bin/sh
echo "creating html package ..."
tar cvzf /tmp/kiki-html.tgz *.html */*.html
echo "uploading package to kiki.sourceforge.net"
scp /tmp/kiki-html.tgz monsterkodi@kiki.sourceforge.net:/home/groups/k/ki/kiki/htdocs/
echo "finished ... suggesting ..."
echo "       ssh kiki.sourceforge.net"
echo "       cd htdocs && tar xvzf kiki-html.tgz"
