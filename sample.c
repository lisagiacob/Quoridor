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
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"


#include <stdio.h>
#include <stdbool.h>  // Import the boolean header file 
#include <string.h>
#include "button_EXINT/button.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "led/led.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

void scacchieraInit(void);

bool vittoria = 0;				// variabile globale che si setta ogni volta che si fa una mossa <- stta nel joystic
int i = 20;								// variabile che mi gestice il timer dei 20 secondi. globale per poterlo modificare all'interno del joystic
int giocatore = 1;				// valori accettati: 1, 2

int main(void)
{	
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
	BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/
	//enable_RIT();													/* RIT enabled												*/
	
  LCD_Initialization();
	
  
	TP_Init();
	//TouchPanel_Calibrate();
	
	LCD_Clear(Red);
	
	//init_timer(0, 0x1312D0 ); 						/* 50ms * 25MHz = 1.25*10^6 = 0x1312D0 */
	//init_timer(0, 0x6108 ); 						  /* 1ms * 25MHz = 25*10^3 = 0x6108 */
	//init_timer(0, 0x4E2 ); 						    /* 500us * 25MHz = 1.25*10^3 = 0x4E2 */
	//init_timer(0, 0xC8 ); 						    /* 8us * 25MHz = 200 ~= 0xC8 */
	//enable_timer(0);
	
	
	//Inizializzo il colore della schermata
	//LCD_Clear(White);
	
	//Disegno la scacchiera
	//scacchieraInit();
	
	//iniziano i rettangoli funzionali:
	//LCD_DrawLine( 0, 245, 240, 245 , Black );		// -> lo schermo è largo 240
	
	
	while(!vittoria){
		init_timer(0, 0x17D7840);											// 1s 
		enable_timer(0);
	}
	//Finito il tempo (20 secondi) Si esegue l'irqHandler di time0 <- qua metto il passggio all'altro giocatore
	
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
