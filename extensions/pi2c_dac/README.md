# pi2c_dac

A Pure Data external for interfacing with the MCP4725 I2C DAC on the Raspberry Pi.

## Features

- 12-bit DAC resolution (0-4095)
- I2C interface
- Read and write DAC values
- Input range: 0-1 (automatically scaled to 0-4095)
- Support for multiple DACs through A0 pin state configuration

## Requirements

- Raspberry Pi with I2C enabled
- MCP4725 DAC module
- I2C tools installed (`sudo apt-get install i2c-tools`)
- I2C kernel module loaded (`sudo modprobe i2c-dev`)

## Installation

1. Build the external:
   ```bash
   cd extensions/pi2c_dac
   make
   ```

2. Install the external:
   ```bash
   make install
   ```

## Usage

The external provides the following functionality:

- Input: float (0-1) to set DAC value
- Bang: read current DAC value
- Output: current DAC value (0-4095)

### Multiple DACs

The MCP4725 has an A0 pin that determines its I2C address:
- A0 low (0V): I2C address 0x62 (default)
- A0 high (VCC): I2C address 0x63

To use multiple DACs, specify the A0 pin state when creating the object:
- `pi2c_dac` - Uses default address 0x62 (A0 low)
- `pi2c_dac 1` - Uses address 0x63 (A0 high)

## Wiring

Connect the MCP4725 to the Raspberry Pi I2C pins:
- VCC to 3.3V
- GND to GND
- SDA to GPIO2 (Pin 3)
- SCL to GPIO3 (Pin 5)
- A0 to GND (for address 0x62) or VCC (for address 0x63)

## License

This project is licensed under the MIT License - see the LICENSE file for details. 