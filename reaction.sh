

PATH="/home/tom/SCREENSHOTS/"

i="$(cd $PATH; ls | dmenu)"

k=echo $i | sed -n "p/^.png/g"
if [ k != "" ]; then
	s="image/png"
fi

j="jpg"

k=echo $i | sed -n "p/^.$j/g"
if [ k != "" ]; then
	s="image/$j"
fi


k=echo $i | sed -n "p/^.jpg/g"
if [ k != "" ]; then
	s="image/$j"
fi


xclip --clip --type $s -i $i 