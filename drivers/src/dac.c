#include "dac.h"
#include "I2C.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// commands
#define DAC_WRITE 0x40

int dac_init(int a0_state) {
    int fd = i2c_open(1);  // Use I2C-1
    if (fd < 0) {
        fprintf(stderr, "Failed to open I2C device\n");
        return -1;
    }
    
    // Set I2C address based on A0 state
    int addr = a0_state ? DAC_ADDR_A0_HIGH : DAC_ADDR;
    if (i2c_set_addr(fd, addr) < 0) {
        fprintf(stderr, "Failed to set DAC address (0x%02X)\n", addr);
        close(fd);
        return -1;
    }
    
    return fd;
}

void dac_set_value(int fd, uint16_t value) {
    // Ensure value is within 12-bit range
    if (value > 4095) value = 4095;
    
    // Prepare DAC data
    uint8_t buf[3];
    buf[0] = DAC_WRITE;  // Write DAC command
    buf[1] = (value >> 4) & 0xFF;  // Upper 8 bits
    buf[2] = (value << 4) & 0xF0;  // Lower 4 bits
    
    // Write to DAC
    if (write(fd, buf, 3) != 3) {
        fprintf(stderr, "Failed to write to DAC\n");
        exit(1);
    }
}

uint16_t dac_get_value(int fd) {
    uint8_t buf[3];
    
    // Read current DAC value
    if (read(fd, buf, 3) != 3) {
        fprintf(stderr, "Failed to read DAC value\n");
        exit(1);
    }
    
    // Convert to 12-bit value
    return ((buf[0] << 4) | (buf[1] >> 4)) & 0xFFF;
}

void dac_close(int fd) {
    if (fd >= 0) {
        close(fd);
    }
} 