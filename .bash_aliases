#!/bin/bash


export EDITOR="ne"

alias e='$(echo -e "ne\nvim\nnano\ngedit" | fzy)'
alias ree='~/.bash_aliases'
alias cdf='. change_directory_fast'
alias cac='cisco -s </home/tom/cisco_login'
alias cad='cisco disconnect'
alias dl='cd /home/tom/Downloads'
alias home='cd ~'
alias cast='cisco status | sed -n -e "/Disconnected.*/p" -e "/Connected.*/p" -e "/Reconnecting.*/p" | sed -n "1p"'
alias file='file'
alias src='cd ~/.scripts && ls'
alias svn='cd /home/tom/svn/root && ls && ls $(find -type d -maxdepth 1  |fzy)'
alias update='sudo apt update && sudo apt upgrade'


alias t-start='sudo service transmission-daemon start'
alias t-stop='sudo service transmission-daemon stop'
alias t-reload='sudo service transmission-daemon reload'
alias t-list='transmission-remote -n 'transmission:transmission' -l'
alias t-basicstats='transmission-remote -n 'transmission:transmission' -st'
alias t-fullstats='transmission-remote -n 'transmission:transmission' -si'