#include "m_pd.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../drivers/src/dac.h"

static t_class *pi2c_dac_class;

typedef struct _pi2c_dac {
    t_object x_obj;
    int dac_fd;
    t_outlet *outlet;
} t_pi2c_dac;

static void pi2c_dac_bang(t_pi2c_dac *x) {
    // Read current DAC value using driver
    uint16_t value = dac_get_value(x->dac_fd);
    outlet_float(x->outlet, value);
}

static void pi2c_dac_float(t_pi2c_dac *x, t_float f) {
    // Convert float to 12-bit value (0-4095)
    int value = (int)(f * 4095.0f);
    if (value < 0) value = 0;
    if (value > 4095) value = 4095;
    
    // Set DAC value using driver
    dac_set_value(x->dac_fd, value);
}

static void *pi2c_dac_new(t_symbol *s, int argc, t_atom *argv) {
    t_pi2c_dac *x = (t_pi2c_dac *)pd_new(pi2c_dac_class);
    
    // Default A0 state is low (0)
    int a0_state = 0;
    
    // Check for A0 argument
    if (argc > 0 && argv[0].a_type == A_FLOAT) {
        a0_state = (int)argv[0].a_w.w_float;
    }
    
    // Initialize DAC using driver
    x->dac_fd = dac_init(a0_state);
    if (x->dac_fd < 0) {
        pd_error(x, "Failed to initialize DAC");
        return NULL;
    }
    
    // Create outlet
    x->outlet = outlet_new(&x->x_obj, &s_float);
    
    return (void *)x;
}

static void pi2c_dac_free(t_pi2c_dac *x) {
    if (x->dac_fd >= 0) {
        dac_close(x->dac_fd);
    }
    outlet_free(x->outlet);
}

void pi2c_dac_setup(void) {
    pi2c_dac_class = class_new(gensym("pi2c_dac"),
        (t_newmethod)pi2c_dac_new,
        (t_method)pi2c_dac_free,
        sizeof(t_pi2c_dac),
        CLASS_DEFAULT,
        A_GIMME, 0);  // Allow for optional arguments
    
    class_addbang(pi2c_dac_class, (t_method)pi2c_dac_bang);
    class_addfloat(pi2c_dac_class, (t_method)pi2c_dac_float);
} 