


short_dat() {
	date +"📅 %d/%m/%y"
}

dat() {
	date +"Today is %a the %e of %b of The year %Y"
}

tim() {
	date +"🕒 %H:%M"
}

battery() {
	acpi -b | sed -e "s/Full/⚡️/g" -e "s/Unknown/🚨️/g" -e "s/Discharging/🌩️/g" -e "s/Battery/🔋/g" -e "s@\n@ @g" | xargs echo  # xargs echo replaces the line break
}

while true; do
xsetroot -name "$(battery)  $(short_dat) $(tim) "
	if [-f ~/.fehbg ]; then
		./fehbg
	fi
sleep 10s
done

