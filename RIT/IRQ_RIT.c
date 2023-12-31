/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../game/board.h"

extern int player;
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void RIT_IRQHandler (void)
{			
	static int select=0;
	static int left = 0;
	static int right = 0;
	static int up = 0;
	static int down = 0;
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		//Joystic select
		select ++;
		switch(select){
			case 1:
				break;
			default:
				break;
		}
	}
	else{
		select = 0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
			//Joystic select
			down ++;
		switch(down){
			case 1:
				movePlayer(player, 2);
				break;
			default:
				break;
		}
	}
	else{
		down = 0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
			//Joystic left
			left ++;
			switch(left){
				case 1:
					movePlayer(player, 3);
					break;
				default:
					break;
			}
	}
	else{
		left = 0;
	}
	
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
			//Joystic right
			right ++;
		switch(right){
			case 1:
				movePlayer(player, 1);
				break;
			default:
				break;
		}
	}
	else{
		right = 0;
	}
	
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
		//Joystic up
		up ++;
		switch(up){
			case 1:
				movePlayer(player, 0);
				break;
			default:
				break;
		}
	}
	else{
		up = 0;
	}
		
		
/*
	static int down=0;	
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		static uint8_t position=0;
		reset_RIT();
		switch(down){
			case 1:
				if( position == 7){
					position = 0;
				}
				break;
			default:
				break;
		}
	}
	else {	// button released
		down=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 // disable Button interrupts			
		LPC_PINCON->PINSEL4    |= (1 << 22);     // External interrupt 0 pin selection 
	}*/
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;

}
/******************************************************************************
**                            End Of File
******************************************************************************/
