/*
 * ao_led.c
 *
 *  Created on: Nov 19, 2023
 *      Author: thony
 */
#include "ao_led.h"
#include "driver.h"


#define QUEUE_LENGTH_            (5)
#define QUEUE_ITEM_SIZE_         (sizeof(led_event_t))



static void task_(void* argument)  //el argumento de la funcion es la estructura del objeto activo
{
  ao_led_t* hao = (ao_led_t*)argument; //aca lo desempaqueta en hao
  while(true)
  {
	ELOG("--------- TASK ACTIVE OBJECT------- \r\n");
    led_event_t event; //mensaje a encolar
    if(pdPASS == xQueueReceive(hao->hqueue, &event, portMAX_DELAY)) //No queda bloqueado esperando un evento
    {
    	// procesar evento con maquina de estado
      ELOG("ao, led:%d", event);
      proccess_ao_evento(&event);
      hao->callback(hao, event);
    }
  }
}


bool ao_led_send(ao_led_t* hao,led_event_t ao_event)
{
	led_event_t event;
	event = ao_event;
	return (pdPASS == xQueueSend(hao->hqueue, (void*)&event, 0));
}

void ao_led_init(ao_led_t* hao, ao_led_callbak_t callback)
{
  eboard_led_red(false);
  eboard_led_green(false);

  hao->callback = callback; // recibe el puntero de la funcion

  hao->hqueue = xQueueCreate(QUEUE_LENGTH_, QUEUE_ITEM_SIZE_); //se crea la cola
  while(NULL == hao->hqueue)
  {
    // error
  }

  BaseType_t status;
  status = xTaskCreate(task_, "task_ao_led", 128, (void* const)hao, tskIDLE_PRIORITY, NULL); //se crea tarea y se envia un puntero tipo cualquiera con hao
  while (pdPASS != status)
  {
    // error
  }
}


//Proceso de evento
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
