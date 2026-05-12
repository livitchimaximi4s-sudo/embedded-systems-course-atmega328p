#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"

#define GREEN_TIME   5000
#define YELLOW_TIME  2000
#define EXTRA_TIME   4000

void wait_ms(uint32_t ms)
{
    uint32_t start = Millis();
    while ((Millis() - start) < ms);
}

void all_red(void)
{
    // Petre Ispirescu
    GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH);
    GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);

    // Strada Spania
    GPIO_Write(GPIO_PORTD, 5, GPIO_HIGH);
    GPIO_Write(GPIO_PORTD, 6, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 7, GPIO_LOW);

    // Calea Bucuresti stanga
    GPIO_Write(GPIO_PORTB, 0, GPIO_HIGH);
    GPIO_Write(GPIO_PORTB, 1, GPIO_LOW);
    GPIO_Write(GPIO_PORTB, 2, GPIO_LOW);

    // Calea Bucuresti dreapta
    GPIO_Write(GPIO_PORTB, 3, GPIO_HIGH);
    GPIO_Write(GPIO_PORTB, 4, GPIO_LOW);
    GPIO_Write(GPIO_PORTB, 5, GPIO_LOW);

    // Viraj spre Spania
    GPIO_Write(GPIO_PORTC, 0, GPIO_HIGH);
    GPIO_Write(GPIO_PORTC, 1, GPIO_LOW);
    GPIO_Write(GPIO_PORTC, 2, GPIO_LOW);
}

int main(void)
{
    Timer0_Init();

    // Petre Ispirescu
    GPIO_Init(GPIO_PORTD, 2, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 3, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 4, GPIO_OUTPUT);

    // Strada Spania
    GPIO_Init(GPIO_PORTD, 5, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 6, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 7, GPIO_OUTPUT);

    // Calea Bucuresti stanga
    GPIO_Init(GPIO_PORTB, 0, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 1, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 2, GPIO_OUTPUT);

    // Calea Bucuresti dreapta
    GPIO_Init(GPIO_PORTB, 3, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 4, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 5, GPIO_OUTPUT);

    // Viraj spre Spania
    GPIO_Init(GPIO_PORTC, 0, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 1, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 2, GPIO_OUTPUT);

    while (1)
    {
        // faza 1: Petre + Spania verde
        all_red();

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_HIGH);

        GPIO_Write(GPIO_PORTD, 5, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 7, GPIO_HIGH);

        wait_ms(GREEN_TIME);

        // galben
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_HIGH);

        GPIO_Write(GPIO_PORTD, 7, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 6, GPIO_HIGH);

        wait_ms(YELLOW_TIME);

        // faza 2: Bucuresti stanga + dreapta verde
        all_red();

        GPIO_Write(GPIO_PORTB, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 2, GPIO_HIGH);

        GPIO_Write(GPIO_PORTB, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 5, GPIO_HIGH);

        wait_ms(GREEN_TIME);

        // faza 3: Bucuresti stanga rosu, dreapta continua
        GPIO_Write(GPIO_PORTB, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 1, GPIO_HIGH);

        wait_ms(YELLOW_TIME);

        GPIO_Write(GPIO_PORTB, 1, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 0, GPIO_HIGH);

        // semafor viraj spre Spania
        GPIO_Write(GPIO_PORTC, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 2, GPIO_HIGH);

        wait_ms(EXTRA_TIME);

        // galben final
        GPIO_Write(GPIO_PORTB, 5, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 4, GPIO_HIGH);

        GPIO_Write(GPIO_PORTC, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 1, GPIO_HIGH);

        wait_ms(YELLOW_TIME);
    }
}