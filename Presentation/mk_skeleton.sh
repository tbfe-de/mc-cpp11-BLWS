#!/bin/bash
# -----------------------------------------------------------------------------
# Create Skeletal "withinfo" Pages from "linkinfo" Pages (fed in here)
# -----------------------------------------------------------------------------
# Note: the easiest way to use this from VIM is to visually the feeding section
# INCLUDING its end marker ("---"), then use the ':!%' command.
#	:!'<,'>%
# The limiters for the visually marked section ("'<" and "'>") are inserted
# automatically and need not be typed-in.

awk '
BEGIN {
	feedthrough = !(linecount = itscount = 0)
	feedthrough = 1
}
$1 == "template:" && $2 == "linkinfo" {
	feedthrough = 0
}
feedthrough == 1 {
	print
	next
}
{
	textline[++linecount] = $0
}
$1 == "graphic:" {
	graphic = $2
}
$0 ~ /^\* [[].*[]][(]#.*[)]$/ {
	itsline[++itscount] = gensub(/^\* [[](.*)[]][(]#(.*)[)]$/, "\\1\7\\2", "g")
}
/^---$/ {
	for (i = 1; i <= linecount; ++i) {
		print textline[i]
	}
	for (i = 1; i <= itscount; ++i) {
		split(itsline[i], tocits, "\7")
		sub(/^[ \t]+/, "", tocits[1])
		sub(/[ \t]+$/, "", tocits[1])
		print "template: withinfo"
		print "graphic: " graphic
		print "section: TBD"
		print "name: " tocits[2]
		print "header: ### " tocits[1]
		print ""
		print ".N["
		print "Siehe Info-Grafik zusammen mit den Ausführungen des Dozenten."
		print "]"
		print ""
		print "---"
	}
	feedthrough = !(linecount = itscount = 0)
}
'
