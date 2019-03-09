/*
===============================================================================
 Name        : proj_tz_hello_2.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

void My_Delay_Func(const uint32_t delay_val); // prototype for our delay function

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set all LEDs to the state of "Off" ... NXP has it flipped, declare new local On and Off states
    bool On_l = false;
    bool Off_l = true;
    Board_LED_Set(Red, Off_l);
    Board_LED_Set(Green, Off_l);
    Board_LED_Set(Blue, Off_l);

    // Turn on/off Red LED
//    Board_LED_Set(Red, On_l);
//    // Turn on/off Green LED
//    Board_LED_Set(Green, On_l);
//    // Turn on Blue LED
//    Board_LED_Set(Blue, On_l);


#endif
#endif

    // TODO: insert code here

    // Enter an infinite loop
    while (1) {
        Board_LED_Set(Red, On_l);
        My_Delay_Func(4e6);
        Board_LED_Set(Red, Off_l);
        Board_LED_Set(Green, On_l);
        My_Delay_Func(4e6);
        Board_LED_Set(Green, Off_l);
        Board_LED_Set(Blue, On_l);
        My_Delay_Func(4e6);
        Board_LED_Set(Blue, Off_l);
    }
    return 1;
}


// a generic delay function
void My_Delay_Func(const uint32_t delay_val) {

    // Force the counter to be placed into memory
	volatile static uint32_t j = 0;

	// actual delay loop
	for (j=0;j<delay_val;j++);
}
