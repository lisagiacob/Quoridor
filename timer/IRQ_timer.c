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
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

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

void TIMER0_IRQHandler (void)
{
	static int clear = 0;
	char time_in_char[5] = "";
	
  if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.y < 280){
			TP_DrawPoint(display.x,display.y);
			GUI_Text(200, 0, (uint8_t *) "     ", Blue, Blue);
			clear = 0;
		}
		else{			
			if(display.y <= 0x13E){			
				clear++;
				if(clear%20 == 0){
					sprintf(time_in_char,"%4d",clear/20);
					GUI_Text(200, 0, (uint8_t *) time_in_char, White, Blue);
					if(clear == 200){	/* 1 seconds = 200 times * 500 us*/
						LCD_Clear(Blue);
						GUI_Text(0, 280, (uint8_t *) " touch here : 1 sec to clear ", Blue, White);			
						clear = 0;
					}
				}
			}
		}
	}
	else{
		//do nothing if touch returns values out of bounds
	}
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
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
	distance_cell_tot = 69;
	
		if(checkWinner() == -1){			//finch� non c'� ancora un vincitore
			if(t != player){
				i = 20;
				t = player;
				barrier = 0;
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
				if(player == 1) player = 2;
				else if(player == 2) player = 1; 
			}
			enable_timer(1);
		}

  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
