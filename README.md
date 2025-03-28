# pipd

I wanted to use mostly "regular" stuff to get a pi booting fast headless and running puredata patches. My goal was to run it in ethernet gadget-mode for very fast way to interact on the computer, but also not wait for things like wifi to work (although you can still enable these, if you want.) It should load a few systemd services in the background to make it all run smoothly, and as "normal" as possible.

This expands on some ideas in [pdpi](https://github.com/konsumer/pdpi), and I will be combining these, and calling it all "pipd", going forward.

This will work with pizero(2w) and pi4, which is only needed for "gadget mode" on USB. The C lib/puredata-patches will work on any pi.

You can use the [C lib](drivers/) or [puredata extensions](extensions), or [setup.sh](setup.sh) to build an OS image. Read [SETUP](SETUP.md) for some customization ideas.

## Hardware

Here are the parts I used:

- pizero2w - it has wifi & bluetooth, which I am not really using. It runs faster than pizero1, is still pretty cheap, and does gadget-mode
- [4 knob rotary](https://www.adafruit.com/product/5752) it's i2c (so no extra GPIO is used up) and it has buttons and RGB LEDs.
- 128x64 SSD1306 monochrome OLED. These are surplus from really old phones, easy to find, and are pretty crisp & bright. Some have split colors where the top 16 pixels are yellow, and the bottom are blue. It's still 1 color, but looks like 2. I ended up using plain black/white
- Since I tie up the USB-data port on pizero with gadget-mode, USB audio is not an option. I used [this](https://www.amazon.com/RASPIAUDIO-Audio-Sound-Ultra-Raspberry/dp/B09JK728MB) for better sound, but you can also use something really nice like [pisound](https://blokas.io/pisound/)
- [MCP4725 DAC](https://www.adafruit.com/product/935) - A 12-bit I2C DAC that can be used for analog output. Supports multiple units on the same I2C bus through A0 pin configuration.

I hooked it up like this:

- Connect rotary-encoders board to "expansion port" (i2c) of sound-board, using a Qwiik connector.
- Run another Qwiik connector to the OLED from rotary-board.
- Connect the MCP4725 DAC to the I2C bus. You can connect multiple DACs by setting their A0 pins differently (one to GND, one to VCC).

In [another synth](https://github.com/konsumer/bellasynth) I used:

- [an i2c 8 rotary-encoder thing](https://docs.m5stack.com/en/unit/8Encoder)
- a small HDMI LCD screen (uses regular Linux video stuff.)
- [pisound](https://blokas.io/pisound/) for audio

## ideas

- [classic midi](https://youtu.be/RbdNczYovHQ) this would allow midi devices while gadget-mode is enabled. I could save space by using [TRS plugs](https://midi.org/updated-how-to-make-your-own-3-5mm-mini-stereo-trs-to-midi-5-pin-din-cables) like modern midi equipment does. see also [this](https://gist.github.com/CarloCattano/8c01a6dea6ecbb459acd0b6bcd752ea6)
