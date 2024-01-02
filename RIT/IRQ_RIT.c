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
#include "../game/graphic.h"

extern int player;		//quale player sta giocando
extern int barrier;		//se == 1 siamo passati alla mod barrier
//player position
extern CoordinatePosition player_position1;
extern CoordinatePosition player_position2;
//barrier position
extern CoordinatePosition barrier_position;
extern CoordinatePosition barrier_coordinate;
extern unsigned int barrier_direction;
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
	int x, y;
	
	if(player == 1){
		x = player_position1.x;
		y = player_position1.y;
	}else{
		x = player_position2.x;
		y = player_position2.y;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		//Joystic select
		select ++;
		switch(select){
			case 1:
				if(player == 1) player = 2;
				else if(player == 2) player = 1;
				if(barrier == 1)confirm_barrier();
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
				if(barrier == 0)	move_player(x, y, player, 2);
				else move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 0);
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
					if(barrier == 0) move_player(x, y, player, 3);
				  else move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 3);
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
				if(barrier == 0) move_player(x, y, player, 1);
				else move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 2);
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
				if(barrier == 0) move_player(x, y, player, 0);
				else move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 1);
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
