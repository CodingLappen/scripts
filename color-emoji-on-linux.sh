# create folders if does not exist
mkdir -p ~/.fonts
mkdir -p ~/.config/fontconfig/

# download noto color emoji font from https://www.google.com/get/noto/#emoji-zsye-color
# extract NotoColorEmoji.ttf file into ~/.fonts/

# create font config file
cat << 'EOF' > ~/.config/fontconfig/fonts.conf
<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE fontconfig SYSTEM "fonts.dtd">

<match>
 <test name="family"><string>sans-serif</string></test>
 <edit name="family" mode="prepend" binding="strong">
 <string>Noto Color Emoji</string>
 </edit>
 </match>

<match>
 <test name="family"><string>serif</string></test>
 <edit name="family" mode="prepend" binding="strong">
 <string>Noto Color Emoji</string>
 </edit>
 </match>

<match>
 <test name="family"><string>Apple Color Emoji</string></test>
 <edit name="family" mode="prepend" binding="strong">
 <string>Noto Color Emoji</string>
 </edit>
 </match>
EOF

# build font information cache files
fc-cache -f -v 
