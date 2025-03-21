#include "dac.h"
#include "I2C.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd = i2c_open();
    if (fd < 0) {
        fprintf(stderr, "Failed to open I2C device\n");
        exit(1);
    }
    
    // Test DAC with A0 low (default address)
    printf("Testing DAC with A0 low (0x62)...\n");
    dac_setup(fd);
    
    // Test setting values
    printf("Setting DAC to 0...\n");
    dac_set_value(fd, 0);
    printf("Current value: %d\n", dac_get_value(fd));
    
    printf("Setting DAC to 2048...\n");
    dac_set_value(fd, 2048);
    printf("Current value: %d\n", dac_get_value(fd));
    
    printf("Setting DAC to 4095...\n");
    dac_set_value(fd, 4095);
    printf("Current value: %d\n", dac_get_value(fd));
    
    // Test DAC with A0 high
    printf("\nTesting DAC with A0 high (0x63)...\n");
    if (i2c_set_addr(fd, DAC_ADDR_A0_HIGH) < 0) {
        printf("No DAC found at address 0x63\n");
    } else {
        dac_setup(fd);
        
        printf("Setting DAC to 2048...\n");
        dac_set_value(fd, 2048);
        printf("Current value: %d\n", dac_get_value(fd));
    }
    
    close(fd);
    return 0;
} 