#!/bin/sh

wallpaper=$1
feh --bg-fill $wallpaper
while true; do
	feh --bg-fill $wallpaper
sleep 10s
done &
