writebotu - Pronounced with a Japanese accent. A small Arduino writing
bot, written in pure AVR cpp (so no `arduino.h`). Written for my first
years finals project (IPASS).

## INSTALLATION

Install the AVR toolchain and arduino-mk, I created CRUX ports for all
these tools: https://github.com/onodera-punpun/crux-ports-arduino


## USAGE

Generate `svg.h`, a file containing the coordinates our pen should
move to by running `./svg2h.sh path/to/image.svg`. Afterwards run
`make && sudo make upload`.


## AUTHORS

Camille Scholtz

Millis library by Zak Kemble: https://github.com/zkemble/millis


## REFERENCES

AVR:
* https://balau82.wordpress.com/2011/03/29/programming-arduino-uno-in-pure-c/

V-plotter:
* https://www.marginallyclever.com/2012/02/drawbot-overview/
* http://www.instructables.com/id/CNC-HANGING-PLOTTER/
* http://www.homofaciens.de/technics-machines-v-plotter_en.htm
