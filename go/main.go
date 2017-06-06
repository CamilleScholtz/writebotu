package main

import (
	"gobot.io/x/gobot"
	"gobot.io/x/gobot/drivers/gpio"
	"gobot.io/x/gobot/platforms/firmata"
)

var (
	tty = firmata.NewAdaptor("/dev/ttyACM0")

	p0 = gpio.NewDirectPinDriver(tty, "42")
	p1 = gpio.NewDirectPinDriver(tty, "44")
	p2 = gpio.NewDirectPinDriver(tty, "46")
	p3 = gpio.NewDirectPinDriver(tty, "48")
)

func work() {
	step(p0, p1, p2, p3, 1000)
}

func main() {
	robot := gobot.NewRobot("writebotu",
		[]gobot.Connection{tty},
		[]gobot.Device{p0, p1, p2, p3},
		work,
	)

	robot.Start()
}
