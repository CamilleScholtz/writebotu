#!/bin/sh

# Convert svg to coordinates.
svg2gcode -F -w 190 $@ svg.h.tmp

# Convert to Drawer `moveto()` calls.
grep 'G01' svg.h.tmp | sed -e 's/G01 X/\td.moveto(/g' \
	-e 's/ [Yy]/, /g' \
	-e 's/ Z.*/);/g' \
	-e '1 i\#include "drawer.h"\n\nvoid svg(Drawer &d) {' \
	-e "\$a}" >svg.h

# Remove temp file.
rm svg.h.tmp
