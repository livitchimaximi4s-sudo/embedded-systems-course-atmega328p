#include <stdint.h>
#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"

void delay_ms(uint32_t ms)
{
    uint32_t start = Millis();

    while (Millis() - start < ms)
    {
    }
}

int main(void)
{
    Timer0_Init();

    GPIO_Init(GPIO_PORTD, 2, GPIO_OUTPUT); // rosu D2
    GPIO_Init(GPIO_PORTD, 3, GPIO_OUTPUT); // galben D3
    GPIO_Init(GPIO_PORTD, 4, GPIO_OUTPUT); // verde D4

    while (1)
    {
        GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        delay_ms(2000);

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        delay_ms(1000);

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_HIGH);
        delay_ms(2000);
    }

    return 0;
}#include <stdint.h>
#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"

void delay_ms(uint32_t ms)
{
    uint32_t start = Millis();

    while (Millis() - start < ms)
    {
    }
}

int main(void)
{
    Timer0_Init();

    GPIO_Init(GPIO_PORTD, 2, GPIO_OUTPUT); // rosu D2
    GPIO_Init(GPIO_PORTD, 3, GPIO_OUTPUT); // galben D3
    GPIO_Init(GPIO_PORTD, 4, GPIO_OUTPUT); // verde D4

    while (1)
    {
        GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        delay_ms(2000);

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        delay_ms(1000);

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_HIGH);
        delay_ms(2000);
    }

    return 0;
}