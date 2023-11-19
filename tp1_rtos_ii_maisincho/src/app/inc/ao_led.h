/*
 * ao_led.h
 *
 *  Created on: Nov 19, 2023
 *      Author: thony
 */

#ifndef APP_INC_AO_LED_H_
#define APP_INC_AO_LED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "task_button.h" //Debido a que el evento productor envia su tipo de dato definido en task_button.h


// ao_led_t es el objeto activo, contiene la cola y callback, que es creado con el sinonimo de datos ao_led_callback
// el cual es el puntero de una funcion que no retorna nada y recibe como argumento el objeto activo y el estado del evento
typedef struct ao_led_s ao_led_t;
typedef void (*ao_led_callbak_t)(ao_led_t *hao,led_event_t state);


struct ao_led_s
{
	QueueHandle_t hqueue;
    ao_led_callbak_t callback;
};




bool ao_led_send(ao_led_t* hao, led_event_t ao_event);

void ao_led_init(ao_led_t* hao, ao_led_callbak_t callback);

void proccess_ao_evento(led_event_t *evento_t);



#endif /* APP_INC_AO_LED_H_ */
