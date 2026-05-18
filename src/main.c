#include <stdint.h>
#include <util/delay.h>
#include "drivers/adc/adc.h"
#include "drivers/pwm/pwm.h"
#include "bsp/uno.h"

int main(void)
{
    ADC_Init();
    PWM_Init(UNO_D9, 1000);

    while (1)
    {
        uint16_t lumina = ADC_Read(0);   // LDR pe A0

        if (lumina > 500)
        {
            // MOD ZI - clipire lentă, intensitate slabă
            PWM_SetDutyCycle(UNO_D9, 60);
            _delay_ms(800);

            PWM_SetDutyCycle(UNO_D9, 0);
            _delay_ms(800);
        }
        else
        {
            // MOD NOAPTE - clipire rapidă, intensitate mare
            PWM_SetDutyCycle(UNO_D9, 255);
            _delay_ms(200);

            PWM_SetDutyCycle(UNO_D9, 0);
            _delay_ms(200);
        }
    }

    return 0;
}