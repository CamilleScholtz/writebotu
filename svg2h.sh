#!/bin/sh

# Convert svg to coordinates.
svg2gcode -F -w 190 svg.svg svg.h.tmp

# Convert to Drawer calls.
grep 'G01' svg.h.tmp | sed -e 's/G01 X/\td.Goto(/g' \
	-e 's/ [Yy]/, /g' \
	-e 's/ Z.*/);/g' \
	-e '1 i\#include "drawer.h"\n\nvoid Svg(Drawer &d) {' \
	-e "\$a}" >svg.h

# Remove temp file.
rm svg.h.tmp
