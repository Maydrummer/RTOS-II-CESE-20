/*
 * task_button.h
 *
 *  Created on: Nov 12, 2023
 *      Author: thony
 */

#ifndef TASK_INC_TASK_BUTTON_H_
#define TASK_INC_TASK_BUTTON_H_


#define t_corto    100
#define t_largo    2000
#define t_trabado  8000

typedef enum
{
	inicial,
	corto,
	largo,
	trabado,

}led_event_t;

extern QueueHandle_t QueueBtnStatus;


void task_button(void* argument);




#endif /* TASK_INC_TASK_BUTTON_H_ */
