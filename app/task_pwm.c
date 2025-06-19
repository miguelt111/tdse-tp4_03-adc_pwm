/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : task_pwm.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include <stdlib.h>
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"

/********************** macros and definitions *******************************/

#define STEP (2048)
#define PERIOD (65535)

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/
void setPWM(TIM_HandleTypeDef timer,
            uint32_t channel,
            uint16_t period,
            uint16_t pulse);

/********************** internal data definition *****************************/
const char *p_task_pwm 		= "Task PWM";

/********************** external data declaration *****************************/
extern TIM_HandleTypeDef htim3;


/********************** external functions definition ************************/
void task_pwm_init(void *parameters)
{
	//shared_data_type *shared_data = (shared_data_type *) parameters;

	//shared_data->pwm_active = 0;
	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_pwm_init), "Task PWM");
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); 
}

void task_pwm_update(void *parameters)
{

	static uint16_t period=PERIOD;
	// static int16_t step = STEP;

	shared_data_type *shared_data = (shared_data_type *) parameters;

	if ( shared_data->adc_end_of_conversion ) {
		shared_data->adc_end_of_conversion = false;
		uint16_t pwm_value = shared_data->adc_value; 
		shared_data->pwm_active = pwm_value;
		setPWM(htim3, TIM_CHANNEL_1, period, pwm_value);
		/*
		if ( step>0 ) {
			if ( period-step<=shared_data->pwm_active ) {
				step = step * -1;
			}
		}
		else {
			if ( abs(step)>=shared_data->pwm_active ) {
				step = step * -1;
			}
		}
		shared_data->pwm_active = shared_data->pwm_active + step;
		*/
	}
}


void setPWM(TIM_HandleTypeDef timer, uint32_t channel,
            uint16_t period, uint16_t pulse){
	/*
	HAL_TIM_PWM_Stop(&timer, channel);
	TIM_OC_InitTypeDef sConfigOC;
	timer.Init.Period = period;
	HAL_TIM_PWM_Init(&timer);

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = pulse;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&timer, &sConfigOC, channel);
	HAL_TIM_PWM_Start(&timer,channel);
	*/
	__HAL_TIM_SET_COMPARE(&timer, channel, pulse);
}


/********************** end of file ******************************************/
