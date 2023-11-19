/*
 * task_button.c
 *
 *  Created on: Nov 12, 2023
 *      Author: thony
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver.h"
#include "task_button.h"
#include "ao_led.h"


TickType_t pressed_start=0;
TickType_t pressed_time;
uint8_t buffer[100];
led_event_t ao_evento; //Notificacion a encolar
ao_led_t ao_led; //es la estructura del objeto activo, contiene una cola y el callback de la funcion



void led_state_callback_(ao_led_t* hao, led_event_t state) //Esta funcion se llama cada vez que se cambia un evento
{
  ao_evento = state;
  ELOG("callback, led:%d", ao_evento);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) //Interrupcion del sw button
{
	if(eboard_gpio_read(EBOARD_GPIO_SW)== false)
	{
		pressed_start= xTaskGetTickCount();
	}
	else
	{
		pressed_time= xTaskGetTickCount()-pressed_start;
		pressed_start=0;
	}
}



void task_button(void* argument) //tarea productora, actualiza los eventos en la cola
{
	ao_evento = inicial;
	ao_led_init(&ao_led, led_state_callback_); //se inicializa el objeto activo, y se pasa la funcion que sera el callback del objeto activo
	while(1)
	{
		ELOG("--------- TASK BUTTON------- \r\n");
		//Productora de eventos
		sprintf((char *)buffer,"Tiempo presionado: %lu\r\n" ,pressed_time);
		ELOG(buffer);
		procces_button(&ao_evento); //evento a enviar, se lo procesa en funcion del tiempo presionado
		//envio de notificacion
		ao_led_send(&ao_led,ao_evento);//se encola el evento
		sprintf((char *)buffer,"Proccess button: %u \r\n",ao_evento);
		ELOG(buffer);
		vTaskDelay(100);
	}


}


void procces_button(led_event_t *evento)
{
	if ( (t_corto <= pressed_time) && (pressed_time < t_largo))
	{
		*evento= corto;

	}
	else if((t_largo <= pressed_time) && (pressed_time < t_trabado))
	{
		*evento= largo;
	}
	else if(pressed_time > t_trabado)
	{
		*evento= trabado;
	}
	else
	{
		*evento= inicial;
	}
}


