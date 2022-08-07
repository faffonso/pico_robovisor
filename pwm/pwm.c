#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
 
#define PICO_MOTOR_R_PWM 13
#define PICO_MOTOR_R_BRK 12
#define PICO_MOTOR_L_PWM 20
#define PICO_MOTOR_L_BRK 21

int main() {
    
    stdio_init_all();

    /**
     * @brief Setar uma função a um GPIO
     * @param GPIO Pino físico do GPIO
     * @param GPIO_FUNC Macro referente a função do pino
     */
    gpio_set_function(PICO_MOTOR_R_PWM, GPIO_FUNC_PWM);
    gpio_set_function(PICO_MOTOR_L_PWM, GPIO_FUNC_PWM);
 
    // Econtrar qual PWM slice está conectado na GPIO
    uint slice_num_r = pwm_gpio_to_slice_num(PICO_MOTOR_R_PWM);
    uint slice_num_l = pwm_gpio_to_slice_num(PICO_MOTOR_L_PWM);
 
    // Set período de ciclos (0 - 3)
    pwm_set_wrap(slice_num_r, 3);

    /* Envio do sinal de output PWM */
    // Set channel A output high for one cycle before dropping
    // PWM_CHAN_A = 0 (pwm.h)
    pwm_set_chan_level(slice_num_r, PWM_CHAN_A, 1);

    // Set initial B output high for three cycles before dropping
    // PWM_CHAN_A = 1 (pwm.h)
    pwm_set_chan_level(slice_num_r, PWM_CHAN_B, 3);
    
    // Ligar o PWM
    pwm_set_enabled(slice_num_r, true);
}