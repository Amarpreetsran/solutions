/*
 * @brief FreeRTOS Blinky example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

/* Variation based on "FreeRTOS Blinky example" from NXP ... please see above copyright notice
 *
 * This variation defines three distict tasks (using a single TaskFunction), in conjunction with
 * an "old-school" delay (to prevent preemptions during the delay) and dynamically changing task
 * priorities in order to get the LEDs to blink in sequence: red (on/off), green (on/off), blue (on/off)
 *
 * This version also uses some interesting pointer techniques to pass parameters to the Task Function.
 * See the declaration and expressions at the very top of the main().
 *
 * author: Takis Zourntos (takis.zourntos@gmail.com)
 *
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdlib.h>
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define	LED_DELAY	2000000UL

static 	xTaskHandle RedLEDTaskHandle = NULL;
static 	xTaskHandle GreenLEDTaskHandle = NULL;
static 	xTaskHandle BlueLEDTaskHandle = NULL;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* turn off all LEDs */
static void vClearLEDs(void)
{
	Board_LED_Set(Red, LED_OFF);
	Board_LED_Set(Green, LED_OFF);
	Board_LED_Set(Blue, LED_OFF);
}

/* sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	/* clear all LEDs */
	vClearLEDs();
}

/* old-school delay */
static void vOldSchoolDelay(const uint32_t delay_val)
{
	uint32_t j = 0;

	for (j = 0;j < delay_val;j++);
}

/* LED1 toggle thread */
static void vBlinkLED(void *pvParameters) {
	RGB_LED_t LED_colour = *((RGB_LED_t*) pvParameters); // re-access LED colour value

	while (1) {
		// flash LED
		Board_LED_Set(LED_colour, LED_ON);
		vOldSchoolDelay(LED_DELAY);
		Board_LED_Set(LED_colour, LED_OFF);
		vOldSchoolDelay(LED_DELAY);

		if (LED_colour == Red) {
			taskENTER_CRITICAL();
			vTaskPrioritySet(GreenLEDTaskHandle, tskIDLE_PRIORITY + 2UL);
			vTaskPrioritySet(BlueLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			vTaskPrioritySet(RedLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			taskEXIT_CRITICAL();

		} else if (LED_colour == Green) {
			taskENTER_CRITICAL();
			vTaskPrioritySet(BlueLEDTaskHandle, tskIDLE_PRIORITY + 2UL);
			vTaskPrioritySet(RedLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			vTaskPrioritySet(GreenLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			taskEXIT_CRITICAL();

		}  else if (LED_colour == Blue) {
			taskENTER_CRITICAL();
			vTaskPrioritySet(RedLEDTaskHandle, tskIDLE_PRIORITY + 2UL);
			vTaskPrioritySet(GreenLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			vTaskPrioritySet(BlueLEDTaskHandle, tskIDLE_PRIORITY + 1UL);
			taskEXIT_CRITICAL();
		}


	}
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	main routine for FreeRTOS blinky example
 * @return	Nothing, function should not exit
 */


int main(void)
{
	// set up main RGB variables (need a void pointer for Task function API call)
	RGB_LED_t* 	RGBforTask[3]; // initialize the pointers by allocating actual memory of the correct amount

	for (RGB_LED_t k = Red; k <= Blue; k++) {
		RGBforTask[k] = malloc(sizeof(RGB_LED_t));  // initialize the memory locations to hold what we want
		*RGBforTask[k] = k;
	}

	// initialize the hardware
	prvSetupHardware();

	// Red LED Task
	xTaskCreate(vBlinkLED,(signed char *)"Red LED Task",configMINIMAL_STACK_SIZE,(void *) RGBforTask[Red],(tskIDLE_PRIORITY + 2UL),&RedLEDTaskHandle);

	// Green LED Task
	xTaskCreate(vBlinkLED,(signed char *)"Green LED Task",configMINIMAL_STACK_SIZE,(void *) RGBforTask[Green],(tskIDLE_PRIORITY + 1UL),&GreenLEDTaskHandle);

	// Blue LED Task
	xTaskCreate(vBlinkLED,(signed char *)"Blue LED Task",configMINIMAL_STACK_SIZE,(void *) RGBforTask[Blue],(tskIDLE_PRIORITY + 1UL),&BlueLEDTaskHandle);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
