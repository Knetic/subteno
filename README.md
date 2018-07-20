subteno
====

ESP8266 project that aims to continually ensure a given set of machines are powered on, by spamming them with Wake-On-LAN packets.

Why?
====

For people who run servers from their home, power surges or faulty hardware can cause frequent outages. Servers don't usually automatically come back from a failed state, and their owners are not always around to restart them. And, usually, they don't want to have to think about it.

This project is meant to be a low-cost low-effort solution to mitigate downtime in those cases.

How do I use it?
====

This project uses [Platformio](https://platformio.org/), for an [ESP8266](http://docs.platformio.org/en/latest/platforms/espressif8266.html). The author bought his [on Amazon](https://www.amazon.com/HiLetgo-Internet-Development-Wireless-Micropython/dp/B010N1SPRK/ref=sr_1_1_sspa?ie=UTF8&qid=1532080207&sr=8-1-spons&keywords=esp8266&psc=1).

* Clone the project
* substitute your own SSID/password/MAC in `globals.cpp`
* plug in your 8266 via USB
* build/upload the project with the below snippet

```
sudo platformio run --target upload
```

Once done, the ESP8266 will be flashed with all the software required to run without a laptop. Just plug it into a power source and let it go.

The builtin LED is used to give some basic feedback for the board's status:
* Solid light means that the board is initializing, and is not yet working. It prints on serial (baud 9600) the stages it is going through
* Two flashes are given once the board is done initializing
* No light means nothing is happening
* A single flash indicates a WOL packet has been sent (this happens every 10s)

The device also exposes a basic webserver on port 80 that can give simple information about the status. Hitting the `/status` endpoint on the device will inform you of the device's configured MAC, IP, and last broadcast time (in [millis since boot](https://www.arduino.cc/reference/en/language/functions/time/millis/)).
Currently there is no way to use the webserver to configure values, but the author intends to add that later.

How do I wire this?
====

There's no components other than the esp8266 - it's a purely software project.

Other projects used
====

* [wol.c](https://github.com/scratch-org/wol.c/)- for copy/pasted code to translate an ASCII hex MAC address to a proper 48-bit representation. There was no license for the project, so I took the code verbatim.