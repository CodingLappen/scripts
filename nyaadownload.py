FILE ="/home/tom/.config/horriblesubslist"

import feedparser
import wget

e=list()
d= open(FILE,"r")
 
for i in d:
	e.append(i)
d.close()
f=list()
for i in e:
	d=feedparser.parse(i)
	for j in d.entries:
		try:
			f.append(j.link)
h=list()
for i in f:
	h.apppend(wget.download(i))

print("List of FILES downloaded:")
for i in h:
	print(i)
