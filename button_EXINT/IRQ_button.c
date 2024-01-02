#include "button.h"
#include "lpc17xx.h"

//	#include "../led/led.h" 					/* do not needed anymore, make your project clean */
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */
#include "../game/graphic.h"	


extern CoordinatePosition barrier_position;
extern int barrier_direction;
extern CoordinatePosition player_position1;
extern CoordinatePosition player_position2;
extern int barrier;


void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	//testing movement
	//move_player(player_position2.x, player_position2.y, 2, 0);
	//move_barrier(barrier_position.x, barrier_position.y, barrier_direction, 0);
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	//CREATE A NEW PLAYER BARRIER
	
	//add a new barrier (center of the board)
	if(barrier == 0){
		create_barrier();
		barrier = 1;
		//enable button INT2 to allow rotation
		NVIC_EnableIRQ(EINT2_IRQn);
	}
	else if (barrier == 1){
		delete_barrier(barrier_position.x, barrier_position.y, barrier_direction);
		barrier = 0;
		barrier_position.x = 0;
		barrier_position.y = 0;
		//disable button INT2 
		NVIC_DisableIRQ(EINT2_IRQn);
	}

	//LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	//ROTATION OF THE BARRIER
	
	rotate_barrier(barrier_position.x, barrier_position.y);
	
		//move_player(player_position2.x, player_position2.y, 2, 1);
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


