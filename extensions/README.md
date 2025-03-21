This is 3 externals for puredata, for use with i2c devices & pi:

- [4 knob rotary-encoder thing](https://www.adafruit.com/product/5752) it's i2c (so no extra GPIO is used up) and it has buttons and RGB LEDs.
- [8 knob rotary-encoder thing](https://docs.m5stack.com/en/unit/8Encoder) it's also i2c and it has buttons and RGB LEDs, and has a toggle switch.
- 128x64 SSD1306 monochrome OLED. These are surplus from really old phones, easy to find, and are pretty crisp & bright & cheap.
- MCP4725 DAC

You can download from [here](https://github.com/konsumer/pipd/releases) and put in your puredata-path on a pi.

You can read more about each:

- [pi2c_4encoder](pi2c_4encoder)
- [pi2c_8encoder](pi2c_8encoder)
- [pi2c_oled](pi2c_oled)
- [pi2c_dac](pi2c_dac)

## setup

Make sure to add this to your `/boot/firmware/config.txt`:

```
# dtparam=i2c_arm=on,i2c_arm_baudrate=50000
# dtparam=i2c_arm=on,i2c_arm_baudrate=100000
# dtparam=i2c_arm=on,i2c_arm_baudrate=400000
dtparam=i2c_arm=on,i2c_arm_baudrate=1000000
```

## building

You will need these things, if you want to build it, yourself:

```
sudo apt install libi2c-dev build-essential puredata-dev
```
