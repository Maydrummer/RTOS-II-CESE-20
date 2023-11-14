/*
 * task_led.c
 *
 *  Created on: Nov 13, 2023
 *      Author: thony
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver.h"
#include "task_led.h"
#include "task_button.h"

led_event_t ao_evento;
BaseType_t rv;
const TickType_t xDelay10000ms = pdMS_TO_TICKS(10000UL); //xTicksToWait de la cola
uint8_t buffer2[100];
void proccess_ao_evento(led_event_t *evento_t);

void task_led(void* argument)
{
	while(1)
	{
		ELOG("--------- TASK LED------- \r\n");
		rv = xQueueReceive(QueueBtnStatus, &ao_evento, xDelay10000ms);
		//Revisar que el mensaje se halla encolado correctamente.
		configASSERT(&rv != NULL);
		sprintf((char *)buffer2,"Proccess button led: %u \r\n",ao_evento);
		ELOG(buffer2);
		proccess_ao_evento(&ao_evento);
		vTaskDelay(100);
	}
}

void proccess_ao_evento(led_event_t *evento_t)
{
	switch (*evento_t) {
		case inicial:
			eboard_led_green(false);
			eboard_led_red(false);

			break;
		case corto:
			eboard_led_green(!eboard_gpio_read(EBOARD_GPIO_LEDG));
			eboard_led_red(false);
			break;
		case largo:
			eboard_led_red(!eboard_gpio_read(EBOARD_GPIO_LEDR));
			eboard_led_green(false);
			break;
		case trabado:
			eboard_led_green(true);
			eboard_led_red(true);
			break;
		default:
			eboard_led_green(false);
			eboard_led_red(false);
			break;
	}
}
