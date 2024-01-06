#include "button.h"
#include "lpc17xx.h"

//	#include "../led/led.h" 					/* do not needed anymore, make your project clean */
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */
#include "../game/graphic.h"	
#include "../RIT/RIT.h"


extern CoordinatePosition barrier_position;
extern int barrier_direction;
extern CoordinatePosition player_position1;
extern CoordinatePosition player_position2;
extern int barrier;
extern CoordinatePosition movement_position;

extern int wallsPlayer1;
extern int wallsPlayer2;
extern int player;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	//testing movement
	//move_player(player_position2.x, player_position2.y, 2, 0);
	//move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 0);
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	
	extern int l_cell;
	//CREATE A NEW PLAYER BARRIER
	
	//add a new barrier (center of the board)
	if(barrier == 0){
		
		//player 1
		if(player == 1){
			if(wallsPlayer1 != 0){
				create_barrier();
				barrier = 1;
		
				if(movement_position.x != 0 && movement_position.y != 0){
					//the movement of the player was not confirmed, need to delete the movement intent at the end of the time
					delete_movement(l_cell, movement_position.x, movement_position.y);
				}
				//enable button INT2 to allow rotation
				NVIC_EnableIRQ(EINT2_IRQn);
			}else{
				//No walls available, move the token.
				GUI_Text(45,  6, (uint8_t *)"No walls available.", Red, White);
			}
		}
	
		if(player == 2){
			if(wallsPlayer2 != 0){
				create_barrier();
				barrier = 1;
				
				if(movement_position.x != 0 && movement_position.y != 0){
					//the movement of the player was not confirmed, need to delete the movement intent at the end of the time
					delete_movement(l_cell, movement_position.x, movement_position.y);
				}
				//enable button INT2 to allow rotation
				NVIC_EnableIRQ(EINT2_IRQn);
			}
			else{
				//No walls available, move the token.
				GUI_Text(45,  6, (uint8_t *)"No walls available.", Red, White);
			}
		}
	}
	else if (barrier == 1){
		delete_barrier(barrier_position.x, barrier_position.y, barrier_direction);
		barrier = 0;
		barrier_position.x = 0;
		barrier_position.y = 0;
		//disable button INT2 
		NVIC_DisableIRQ(EINT2_IRQn);
		init_RIT(0x004C4B40);	
		enable_RIT();
	}

	//LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	//ROTATION OF THE BARRIER
	
	rotate_barrier(barrier_position.x, barrier_position.y);
	
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


