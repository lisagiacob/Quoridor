/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../game/board.h"
#include "../game/graphic.h"
#include "../game/move.h"
#include "../GLCD/GLCD.h" 
#include "../RIT/RIT.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern int i;
extern int player, barrier;
extern int t;

extern CoordinatePosition start_round;
extern CoordinatePosition player1_coordinate;
extern CoordinatePosition player2_coordinate;

extern CoordinatePosition movement_position;
extern CoordinatePosition barrier_position;
extern int barrier_direction;

void TIMER0_IRQHandler (void)
{

}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	char str[2];
	extern int distance_cell_tot;
	extern int l_cell;
	distance_cell_tot = 69;
														/* RIT enabled												*/
	
		if(checkWinner() == -1){			//finchè non c'è ancora un vincitore
			if(t != player){
				NVIC_DisableIRQ(EINT2_IRQn);
				init_RIT(0x004C4B40);	
				enable_RIT();
				i = 20;
				t = player;
				barrier = 0;
				
				
				GUI_Text(45,  6, (uint8_t *)"   								     ", White, White);
				
				if(movement_position.x != 0 && movement_position.y != 0){
					//the movement of the player was not confirmed, need to delete the movement intent at the end of the time
					delete_movement(l_cell, movement_position.x, movement_position.y);
				}
				
				//delete barrier not confirmed before the ened of the time
				delete_barrier(barrier_position.x, barrier_position.y, barrier_direction);
				barrier = 0;
				barrier_position.x = 0;
				barrier_position.y = 0;
				
				GUI_Text(35,  225, (uint8_t *)"                      ", Black, White);
				if(player == 1 ) GUI_Text(35,  225, (uint8_t *)"Player 1, your turn!", Blue, White);
				else if(player == 2) GUI_Text(35,  225, (uint8_t *)"Player 2, your turn!", Green, White);
				
				if(player == 1){
					start_round.x = player1_coordinate.x;
					start_round.y = player1_coordinate.y;
				}
				if(player == 2){
					start_round.x = player2_coordinate.x;
					start_round.y = player2_coordinate.y;
				}
			}
			if(i > -1){
					if(i==9) GUI_Text(20+distance_cell_tot+20,  270, (uint8_t *) "  ", Black, White);
					sprintf(str, "%i", i);
					GUI_Text(20+distance_cell_tot+20,  270, (uint8_t *) str, Black, White);
					i--;
			}
			else {
				i = 20;
				if(player == 1){
					saveMove(0,0,1,player1_coordinate.x, player1_coordinate.y);
					player = 2;
				}
				else if(player == 2){
					saveMove(1,0,1,player2_coordinate.x, player2_coordinate.y);
					player = 1;
				}
			}
			enable_timer(1);
		}

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
