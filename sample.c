/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "game/board.h"
#include "game/graphic.h" 

#include <stdio.h>
#include <stdbool.h>  // Import the boolean header file 

#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int i = 20;								// variabile che mi gestice il timer dei 20 secondi. globale per poterlo modificare all'interno del joystic
int player = 1;				// valori accettati: 1, 2

int main(void)
{
	
  SystemInit();  	
  BUTTON_init();												// BUTTON Initialization 
	joystick_init();											// Joystick Initialization 
	init_RIT(0x004C4B40);									// RIT Initialization 50 msec   				/* System Initialization (i.e., PLL)  */
	
	//init_RIT(0x004C4B40);								// RIT Initialization 50 msec       	
	//enable_RIT();												// RIT enabled												
	
  LCD_Initialization();
	
  
	//TP_Init();
	//TouchPanel_Calibrate();
	
	//Inizializzo il colore della schermata
	LCD_Clear(White);
	
	init_game();						         
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
