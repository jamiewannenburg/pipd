#include "dac.h"
#include "I2C.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Test DAC with A0 low (default address)
    printf("Testing DAC with A0 low (0x62)...\n");
    int fd = dac_init(0);  // A0 low
    if (fd < 0) {
        fprintf(stderr, "Failed to initialize DAC\n");
        exit(1);
    }
    
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
    
    dac_close(fd);
    
    // Test DAC with A0 high
    printf("\nTesting DAC with A0 high (0x63)...\n");
    fd = dac_init(1);  // A0 high
    if (fd < 0) {
        printf("No DAC found at address 0x63\n");
    } else {
        printf("Setting DAC to 2048...\n");
        dac_set_value(fd, 2048);
        printf("Current value: %d\n", dac_get_value(fd));
        dac_close(fd);
    }
    
    return 0;
} 