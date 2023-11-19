/*
 * task_button.h
 *
 *  Created on: Nov 12, 2023
 *      Author: thony
 */

#ifndef TASK_INC_TASK_BUTTON_H_
#define TASK_INC_TASK_BUTTON_H_

#include "hal.h"


#define t_corto    100
#define t_largo    2000
#define t_trabado  8000


typedef enum
{
	inicial,
	corto,
	largo,
	trabado,
}led_event_t; //tipo de dato del evento del objeto activo


void task_button(void* argument);
void procces_button(led_event_t *ao_evento);



#endif /* TASK_INC_TASK_BUTTON_H_ */
