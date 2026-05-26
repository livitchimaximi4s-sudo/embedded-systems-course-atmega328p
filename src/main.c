#include "drivers/gpio/gpio.h"
#include "drivers/timer/timer0.h"
#include "drivers/adc/adc.h"

#define GREEN_TIME   5000
#define YELLOW_TIME  2000
#define SPECIAL_TIME 20000

#define LDR_CHANNEL  3
#define LDR_LIMIT    400

#define BUTTON_PORT  GPIO_PORTC
#define BUTTON_PIN   4

void wait_ms(uint32_t ms)
{
    uint32_t start = Millis();
    while ((Millis() - start) < ms);
}

void all_off(void)
{
    // Petre Ispirescu
    GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);

    // Strada Spania
    GPIO_Write(GPIO_PORTD, 5, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 6, GPIO_LOW);
    GPIO_Write(GPIO_PORTD, 7, GPIO_LOW);

    // Calea Bucuresti dreapta
    GPIO_Write(GPIO_PORTB, 0, GPIO_LOW);
    GPIO_Write(GPIO_PORTB, 1, GPIO_LOW);
    GPIO_Write(GPIO_PORTB, 2, GPIO_LOW);

    // Calea Bucuresti stanga
    GPIO_Write(GPIO_PORTC, 0, GPIO_LOW);
    GPIO_Write(GPIO_PORTC, 1, GPIO_LOW);
    GPIO_Write(GPIO_PORTC, 2, GPIO_LOW);
}

void all_red(void)
{
    all_off();

    // Petre Ispirescu rosu
    GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH);

    // Strada Spania rosu
    GPIO_Write(GPIO_PORTD, 5, GPIO_HIGH);

    // Calea Bucuresti dreapta rosu
    GPIO_Write(GPIO_PORTB, 0, GPIO_HIGH);

    // Calea Bucuresti stanga rosu
    GPIO_Write(GPIO_PORTC, 0, GPIO_HIGH);
}

void all_yellow(gpio_state_t state)
{
    all_off();

    // Petre Ispirescu galben
    GPIO_Write(GPIO_PORTD, 3, state);

    // Strada Spania galben
    GPIO_Write(GPIO_PORTD, 6, state);

    // Calea Bucuresti dreapta galben
    GPIO_Write(GPIO_PORTB, 1, state);

    // Calea Bucuresti stanga galben
    GPIO_Write(GPIO_PORTC, 1, state);
}

void repair_mode(void)
{
    uint32_t start = Millis();

    while ((Millis() - start) < SPECIAL_TIME)
    {
        // Petre Ispirescu rosu constant
        GPIO_Write(GPIO_PORTD, 2, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 3, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);

        // Strada Spania rosu constant
        GPIO_Write(GPIO_PORTD, 5, GPIO_HIGH);
        GPIO_Write(GPIO_PORTD, 6, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 7, GPIO_LOW);

        // Calea Bucuresti dreapta galben intermitent
        GPIO_Write(GPIO_PORTB, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 1, GPIO_HIGH);
        GPIO_Write(GPIO_PORTB, 2, GPIO_LOW);

        // Calea Bucuresti stanga galben intermitent
        GPIO_Write(GPIO_PORTC, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 1, GPIO_HIGH);
        GPIO_Write(GPIO_PORTC, 2, GPIO_LOW);

        wait_ms(800);

        GPIO_Write(GPIO_PORTB, 1, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 1, GPIO_LOW);

        wait_ms(800);
    }
}

void night_mode(void)
{
    uint32_t start = Millis();

    while ((Millis() - start) < SPECIAL_TIME)
    {
        all_yellow(GPIO_HIGH);
        wait_ms(200);

        all_yellow(GPIO_LOW);
        wait_ms(200);
    }
}

void check_special_modes(void)
{
    uint16_t lumina = ADC_Read(LDR_CHANNEL);

    if (GPIO_Read(BUTTON_PORT, BUTTON_PIN) == GPIO_HIGH)
    {
        repair_mode();
    }

    if (lumina < LDR_LIMIT)
    {
        night_mode();
    }
}

int main(void)
{
    Timer0_Init();
    ADC_Init();

    // Petre Ispirescu
    GPIO_Init(GPIO_PORTD, 2, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 3, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 4, GPIO_OUTPUT);

    // Strada Spania
    GPIO_Init(GPIO_PORTD, 5, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 6, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTD, 7, GPIO_OUTPUT);

    // Calea Bucuresti dreapta
    GPIO_Init(GPIO_PORTB, 0, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 1, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTB, 2, GPIO_OUTPUT);

    // Calea Bucuresti stanga
    GPIO_Init(GPIO_PORTC, 0, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 1, GPIO_OUTPUT);
    GPIO_Init(GPIO_PORTC, 2, GPIO_OUTPUT);

    // Buton pe A4
    GPIO_Init(BUTTON_PORT, BUTTON_PIN, GPIO_INPUT);

    while (1)
    {
        check_special_modes();

        // faza 1: Petre + Spania verde
        all_red();

        GPIO_Write(GPIO_PORTD, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 4, GPIO_HIGH);

        GPIO_Write(GPIO_PORTD, 5, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 7, GPIO_HIGH);

        wait_ms(GREEN_TIME);

        // galben Petre + Spania
        GPIO_Write(GPIO_PORTD, 4, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 3, GPIO_HIGH);

        GPIO_Write(GPIO_PORTD, 7, GPIO_LOW);
        GPIO_Write(GPIO_PORTD, 6, GPIO_HIGH);

        wait_ms(YELLOW_TIME);

        check_special_modes();

        // faza 2: Bucuresti stanga + dreapta verde
        all_red();

        // Calea Bucuresti dreapta verde
        GPIO_Write(GPIO_PORTB, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 2, GPIO_HIGH);

        // Calea Bucuresti stanga verde
        GPIO_Write(GPIO_PORTC, 0, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 2, GPIO_HIGH);

        wait_ms(GREEN_TIME);

        // Calea Bucuresti dreapta galben
        GPIO_Write(GPIO_PORTB, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTB, 1, GPIO_HIGH);

        // Calea Bucuresti stanga galben
        GPIO_Write(GPIO_PORTC, 2, GPIO_LOW);
        GPIO_Write(GPIO_PORTC, 1, GPIO_HIGH);

        wait_ms(YELLOW_TIME);
    }
}