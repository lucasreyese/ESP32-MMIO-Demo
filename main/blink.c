#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include <stdio.h>

#define GPIO_OUT_REG (volatile uint32_t *)0x3ff44004
#define GPIO_ENABLE_REG (volatile uint32_t *)0x3ff44020
#define GPIO_FUNC4_OUT_SEL (volatile uint32_t *)0x3ff44140

#define LED_PIN 4
#define LED_MASK (1 << LED_PIN)

#define GPIO_CODE 0x100

// Blinks LED on and off every second.
void app_main(void) {
	/* Enable writing to pin via registers. */
	*GPIO_FUNC4_OUT_SEL = GPIO_CODE; // Set the register corresponding to the pin to be controlled by this function.

	*GPIO_ENABLE_REG |= LED_MASK; // Enable output to the pin.

	while (1) {
		*GPIO_OUT_REG |= LED_MASK;
		printf("LED ON\n");

		vTaskDelay(500 / portTICK_PERIOD_MS); // Delay half a second.

		*GPIO_OUT_REG &= ~LED_MASK;
		printf("LED OFF\n");

		vTaskDelay(500 / portTICK_PERIOD_MS);
	}	
}
