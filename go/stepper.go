package main

import (
	"time"

	"gobot.io/x/gobot"
	"gobot.io/x/gobot/drivers/gpio"
)

func step(p0, p1, p2, p3 *gpio.DirectPinDriver,
	interval time.Duration) {
	var i int

	gobot.Every(interval*time.Millisecond, func() {
		switch i {
		case 0:
			p0.PwmWrite(255)
			p1.PwmWrite(0)
			p2.PwmWrite(255)
			p3.PwmWrite(0)
		case 1:
			p0.PwmWrite(0)
			p1.PwmWrite(255)
			p2.PwmWrite(255)
			p3.PwmWrite(0)
		case 2:
			p0.PwmWrite(0)
			p1.PwmWrite(255)
			p2.PwmWrite(0)
			p3.PwmWrite(255)
		case 3:
			p0.PwmWrite(255)
			p1.PwmWrite(0)
			p2.PwmWrite(0)
			p3.PwmWrite(255)
		}

		if i < 3 {
			i++
		} else {
			i = 0
		}
	})
}
