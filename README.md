subteno
====

ESP8266 project that aims to continually ensure a given set of machines are powered on, by spamming them with Wake-On-LAN packets.

Why?
====

For people who run servers from their home, power surges or faulty hardware can cause frequent outages. Servers don't usually automatically come back from a failed state, and their owners are not always around to restart them. And, usually, they don't want to have to think about it.

This project is meant to be a low-cost low-effort solution to mitigate downtime in those cases.

How do I build it?
====

This project uses [Platformio](https://platformio.org/), for an [ESP8266](http://docs.platformio.org/en/latest/platforms/espressif8266.html). The author bought his on Amazon.

Once cloned, and the board plugged in via USB, simply do the following;

```
sudo platformio run --target upload; sudo platformio run --target monitor
```

How do I use it?
====

Clone the project, substitute your own SSID/password/MAC in `globals.cpp`, plug in your 8266, build/upload the project, and from that moment on your 8266 will keep your server online.

Where's the Fritz?
====

Fritz diagrams are used to express how components and microcontrollers ought to be wired together. In this case, there's no components other than the esp8266 - it's a purely software project.

Other projects used
====

[wol.c](https://github.com/scratch-org/wol.c/): for copy/pasted code to translate an ASCII hex MAC address to a proper 48-bit representation. There was no license for the project, so I took the code verbatim.