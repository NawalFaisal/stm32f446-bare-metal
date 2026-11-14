#include "gpio.h"
#include "rcc.h"

/* ---- pin map ----------------------------------------------------------
 * LED      PA5   D13  (also the onboard LD2)
 * Key 1    PA10  D2
 * Key 2    PA8   D7
 * Key 3    PA9   D8
 * Key 4    PA7   D11
 * Key 5    PA6   D12
 *
 * Each key is wired pin -> button -> GND. The internal pull-up holds the
 * pin HIGH when the button is open, so a press reads LOW.
 * -------------------------------------------------------------------- */

#define LED_PIN   5U
#define NUM_KEYS  5U

static const uint8_t key_pins[NUM_KEYS] = { 10U, 8U, 9U, 7U, 6U };

int main(void)
{
    /* GPIOA clock on */
    init_RCC_AHB1LPENR(RCC, 0);

    /* LED is the only output */
    gpio_init(GPIOA, LED_PIN, GPIO_MODE_OUTPUT);

    /* every key: input with the pull-up enabled */
    for (uint8_t i = 0U; i < NUM_KEYS; i++) {
        gpio_init(GPIOA, key_pins[i], GPIO_MODE_INPUT);
        gpio_set_pull(GPIOA, key_pins[i], GPIO_PULLUP);
    }

    while (1) {
        /* one bit per key: bit i is set while key i is held down */
        uint32_t pressed = 0U;

        for (uint8_t i = 0U; i < NUM_KEYS; i++) {
            if (gpio_read(GPIOA, key_pins[i]) == GPIO_LOW) {
                pressed |= (1U << i);
            }
        }

        /* for now: LED on while any key is held */
        if (pressed != 0U) {
            gpio_set(GPIOA, LED_PIN);
        } else {
            gpio_reset(GPIOA, LED_PIN);
        }
    }
}