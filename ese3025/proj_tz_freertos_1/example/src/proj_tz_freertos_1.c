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

/* Varation based on "FreeRTOS Blinky example" from NXP ... please see above copyright notice
 *
 * This variation blinks the LEDs in sequence using FreeRTOS
 *
 * author: Takis Zourntos (takis.zourntos@gmail.com)
 *
 */

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

#define		LED_DELAY		2000000UL

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Pu		vOldSchoolDelay(LED_DELAY);
 * blic types/enumerations/variables
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

/* Sets up system hardware */
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
static void vLED_One_Task(void *pvParameters) {
	while (1) {
		// clear LEDs
		vClearLEDs();

		// flash Red LED
		Board_LED_Set(Red, LED_ON);
		//vOldSchoolDelay(LED_DELAY);
		vTaskDelay(10000);
		Board_LED_Set(Red, LED_OFF);

		// flash Green LED
		Board_LED_Set(Green, LED_ON);
		//vOldSchoolDelay(LED_DELAY);
		vTaskDelay(10000);
		Board_LED_Set(Green, LED_OFF);

		// flash Blue LED
		Board_LED_Set(Blue, LED_ON);
		//vOldSchoolDelay(LED_DELAY);
		vTaskDelay(10000);
		Board_LED_Set(Blue, LED_OFF);
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

	prvSetupHardware();

	/* LED1 toggle thread */
	xTaskCreate(vLED_One_Task, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* Start the scheduler */
	vTaskStartScheduler();

	/* Should never arrive here */
	return 1;
}

/**
 * @}
 */
