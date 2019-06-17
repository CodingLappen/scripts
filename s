#!/bin/bash
if [ "$1" != "" ] 
then  h=$(echo "$1" | sed 's/\\/\\\\/g' | sed 's/\ /\\\ /g' | sed 's/\./\\\./g') #take important stuff
fi 
if [ "$h" = "" ] 
 then h="." # take everything
fi
echo -e $( find -maxdepth 1 -type f -not -name 't_*'| sed -n -e "s/\.\///" -e "/.*$h/p" | sed -e ':a' -e 'N' -e '$!ba' -e 's/\n/\\n/g') | dmenu -i -l 5
