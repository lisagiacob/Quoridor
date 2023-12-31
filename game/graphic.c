/*
*		Graphic part implementation
*/


#include "../timer/timer.h"
#include "lpc17xx.h"
#include "graphic.h"
#include "board.h"
#include <stdio.h>

extern int wallsPlayer1;
extern int wallsPlayer2;

/*

*		Customize game
*/
uint16_t color_player1 = Blue;
uint16_t color_player2 = Green;
uint16_t color_barrier = Magenta;
uint16_t color_barrier_conf = Red;
	
char label[3][50] = {"P1Wall","0s","P2Wall"};
char values_barrier[3][50] = {"8","","8"};




/*
*		Variables
*/
int border_dx;
int leng_orizz;
int leng_vert;
int distance_cell_tot;

int x_init;
int y_init;

int l_cell;
int dist_cell;
int inner_borderCell;
int len_barrier;
int offset_barrier = 3;

int step_player = 0;
int step_barrier = 0;

int x_point;
int y_point;
int t;

//Initial player coordinate
CoordinatePosition player1_coordinate;
CoordinatePosition player2_coordinate;

//Initial barrier coordinate
CoordinatePosition barrier_coordinate;


//player position
CoordinatePosition player_position1;
CoordinatePosition player_position2;
//barrier position
CoordinatePosition barrier_init_position;
CoordinatePosition barrier_position;


//global
	//barrier_direction = 0 --> horizontal
	//barrier_direction = 1 --> vertical
 unsigned int barrier_direction;
 extern int player;
 
 
 


/***********************************************************************************
*
*		PLAYER
*		
*		player = 1 --> giocatore 1
*		player = 2 --> giocatore 2
*
***********************************************************************************/

void end_game(int winner){
	LCD_Clear(White);
	GUI_Text(25,  150, winner == 1 ? (uint8_t *)" Player 1 won the game! " : (uint8_t *)" Player 2 won the game! ", Black, White);
}

void draw_player( uint16_t x, uint16_t y, unsigned int player){
	int k;
		for(k = 0; k < 6; k++){     
			LCD_DrawLine(x+1, y+k+7, x+l_cell-1, y+k+7, player==1 ? color_player1 : color_player2);
		}
}

void delete_player( uint16_t x, uint16_t y, unsigned int player){
	int k;
		for(k = 0; k < 6; k++){     
			LCD_DrawLine(x+1, y+k+7, x+l_cell-1, y+k+7, White);
		}
}


/*
*
*		up player --> player = 1
*		down player --> player = 2
*
*		move_direction = 0 -> up;
*   move_direction = 1 -> dx; 
*		move_direction = 2 -> down;
*		move_direction = 3 -> sx
*
*/
void move_player(uint16_t x, uint16_t y, unsigned int player, unsigned int move_direction){
	int game_status;
	
	delete_player(x, y, player);
	
		switch(move_direction){
			case 0:
				//up
			if(player == 2){
				if(player2_coordinate.x == 0){
					//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					
					if(game_status != 0){
						if(((player_position2.y - step_player) == player_position1.y) &&  (player_position2.x == player_position1.x)) { 
							y = y - 2*step_player;
							player_position2.y = y;
							player2_coordinate.x = player2_coordinate.x - 4;
						}else{
							y = y - step_player;
							player_position2.y = y;
							player2_coordinate.x = player2_coordinate.x - 2;
						}
					}
				
				}
			}else{
				if(player1_coordinate.x == 0){
					//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if(((player_position1.y - step_player) == player_position2.y) &&  (player_position2.x == player_position1.x)) {
					if(game_status != 0){
						y = y - 2*step_player;
						player_position1.y = y;
						player1_coordinate.x = player1_coordinate.x - 4;	
					}
				}else{
					y = y - step_player;
						player_position1.y = y;
						player1_coordinate.x = player1_coordinate.x - 2;
				}					
				}
			}
				break;			
			case 1:
				//dx
			if(player == 2){
				if(player2_coordinate.y == 12){
					//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if((player_position2.y == player_position1.y) &&  ((player_position2.x + step_player)  == player_position1.x)) { 
						if(game_status != 0){
							x = x + 2*step_player;
							player_position2.x = x;
							player2_coordinate.y = player2_coordinate.y + 4;
						}
					}else{
							x = x + step_player;
							player_position2.x = x;
							player2_coordinate.y = player2_coordinate.y + 2;
					}
				}
			}else{
				if(player1_coordinate.y == 12){
					//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if((player_position2.y == player_position1.y) &&  ((player_position1.x + step_player)  == player_position2.x)) {
						if(game_status != 0){
							x = x + 2*step_player;
							player_position1.x = x;
							player1_coordinate.y = player1_coordinate.y + 4;
						}
					}else{
						x = x + step_player;
						player_position1.x = x;
						player1_coordinate.y = player1_coordinate.y + 2;
					}
				}
			}		
				break;
			case 2:
				//down
			if(player == 2){
				if(player2_coordinate.x == 12){
					//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if(((player_position2.y + step_player) == player_position1.y) &&  (player_position2.x  == player_position1.x)) {
						if(game_status != 0){
							y = y + 2*step_player;
							player_position2.y = y;
							player2_coordinate.x = player2_coordinate.x + 4;
						}
					}else{
						y = y + step_player;
						player_position2.y = y;
						player2_coordinate.x = player2_coordinate.x + 2;	
					}						
				}
			}else{
				if(player1_coordinate.x == 12){
				//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if(((player_position1.y + step_player) == player_position2.y) &&  (player_position2.x  == player_position1.x)) {
						if(game_status != 0){
							y = y + 2*step_player;
							player_position1.y = y;
							player1_coordinate.x = player1_coordinate.x + 4;
						}
					}else{
						y = y + step_player;
						player_position1.y = y;
						player1_coordinate.x = player1_coordinate.x + 2;
					}
				}
			}
				break;
			case 3:
				//sx
			if(player == 2){
				if(player2_coordinate.y == 0){
				//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if((player_position2.y == player_position1.y) &&  ((player_position2.x - step_player)  == player_position1.x)) { 
						if(game_status != 0){
							x = x - 2*step_player;
							player_position2.x = x;
							player2_coordinate.y = player2_coordinate.y - 4;						
						}
					}else{
						x = x - step_player;
						player_position2.x = x;
						player2_coordinate.y = player2_coordinate.y - 2;
					}
				}
			}else{
				if(player1_coordinate.y == 0){
				//ERROR: out of border
				}else{
					game_status = movePlayer(player, move_direction);
					if((player_position2.y == player_position1.y) &&  ((player_position1.x - step_player)  == player_position2.x)) {
						if(game_status != 0){
							x = x - 2*step_player;
							player_position1.x = x;
							player1_coordinate.y = player1_coordinate.y - 4;		
						}
					}else{
						x = x - step_player;
						player_position1.x = x;
						player1_coordinate.y = player1_coordinate.y - 2;
					}
				}
			}
				break;
			}
		
			
			//if permitted = 1 the player has a new position, if permitted = 0 the player is drawn in the same old position 
			draw_player(x, y, player);
			
			
			//victory
			if(game_status == 1 || game_status == 2){
				end_game(game_status);
			}
			
}





/***********************************************************************************
*
*		BOARD
*
************************************************************************************/
void draw_cell(unsigned int l, uint16_t x, uint16_t y){
	
	LCD_DrawLine(x, y, x+l, y, Black);
	LCD_DrawLine(x, y+l, x+l, y+l, Black);
	LCD_DrawLine(x, y, x, y+l, Black);
	LCD_DrawLine(x+l, y, x+l, y+l, Black);
	
}

void create_board(void){
	int z;
	int j;
	int x_pos;
	int y_pos;
	x_pos = 0;
	y_pos = 0;
	
	for(z = 0; z < 7; z++){
		
		for(j = 0; j < 7; j++){    
		
			draw_cell(l_cell, x_init + x_pos, y_init + y_pos);
			x_pos = x_pos + l_cell + dist_cell;
			
		}
		
	y_pos = y_pos + l_cell + dist_cell;
	x_pos = 0;
	
	}
	
	return;
}


/**********************************************************************************
*
*		BARRIER
*
*		direction = 0 --> horizontal
*		direction = 1 --> vertical
*
***********************************************************************************/



void draw_barrier(uint16_t x, uint16_t y, unsigned int direction, uint16_t color){
	
	if(direction == 0){
		
		LCD_DrawLine(x, y, x + len_barrier, y, color);
		LCD_DrawLine(x, y + 1, x + len_barrier, y + 1, color);
		
	}else{
		
		LCD_DrawLine(x, y, x, y - len_barrier, color);
		LCD_DrawLine(x + 1, y, x + 1, y - len_barrier, color);
		
	}
}

void delete_barrier(uint16_t x, uint16_t y, unsigned int direction){
	
	if(direction == 0){
		
		LCD_DrawLine(x, y, x + len_barrier, y, White);
		LCD_DrawLine(x, y + 1, x + len_barrier, y + 1, White);
		
	}else{
		
		LCD_DrawLine(x, y, x, y - len_barrier, White);
		LCD_DrawLine(x + 1, y, x + 1, y - len_barrier, White);
		
	}
}

/*
*
*		angle_barrier = 0 --> horizontal
*		angle_barrier = 1 --> vertical
*
*		move_direction = 0 --> down
*		move_direction = 1 --> up
*		move_direction = 2 --> right
*		move_direction = 3 --> left
*
*/

void move_barrier(uint16_t x, uint16_t y, unsigned int angle_barrier, unsigned int move_direction){

	int permitted;
	delete_barrier(x, y, angle_barrier); 
	
		switch(move_direction){
			case 0:
				permitted = createWall(player, barrier_coordinate.x + 2, barrier_coordinate.y, angle_barrier, 0);
				if(permitted){
					barrier_coordinate.x = barrier_coordinate.x + 2;
					y = y + step_barrier; 
				}
				break;
							
			case 1:
				permitted = createWall(player, barrier_coordinate.x - 2, barrier_coordinate.y, angle_barrier, 0);
				if(permitted == 1){
					barrier_coordinate.x = barrier_coordinate.x - 2;
					y = y - step_barrier;
				}
							
				break;
			case 2:
				permitted = createWall(player, barrier_coordinate.x, barrier_coordinate.y + 2, angle_barrier, 0);
				if(permitted == 1){
					barrier_coordinate.y = barrier_coordinate.y + 2;
					x = x + step_barrier;
				}
							
				break;
			case 3:
				permitted = createWall(player, barrier_coordinate.x, barrier_coordinate.y - 2, angle_barrier, 0);
				if(permitted == 1){
					barrier_coordinate.y = barrier_coordinate.y - 2;
					x = x - step_barrier;
				}
				break;
		}
		
		barrier_position.x = x;
		barrier_position.y = y;
		draw_barrier(x, y, angle_barrier, color_barrier);
}


void rotate_barrier(uint16_t x, uint16_t y){
	
	if(barrier_direction == 1){
		//from vertical to horizontal
		delete_barrier(x, y, barrier_direction); 
		
		//coordinate del centro 
		y = y - (len_barrier/2);
		
		//semi barrier right
		LCD_DrawLine(x, y, x + (len_barrier/2), y, color_barrier);
		LCD_DrawLine(x, y + 1, x + (len_barrier/2), y + 1, color_barrier);
		
		//semi barrier left
		LCD_DrawLine(x, y, x - (len_barrier/2), y, color_barrier);
		LCD_DrawLine(x, y + 1, x - (len_barrier/2), y + 1,color_barrier);
		
		//new position
		x = x - (len_barrier/2);
		barrier_position.x = x;
		barrier_position.y = y;
		barrier_direction = 0;
		
		barrier_coordinate.x = barrier_coordinate.x - 1;
		barrier_coordinate.y = barrier_coordinate.y - 1;
	
	}else{
		//from horizontal to vertical
		delete_barrier(x,y,0);
		
		//coordinate del centro 
		x = x + (len_barrier/2);
		
		//semi barrier up
		LCD_DrawLine(x, y, x, y - (len_barrier/2), color_barrier);
		LCD_DrawLine(x + 1, y, x + 1, y - (len_barrier/2), color_barrier);
		
		//semi barrier down
		LCD_DrawLine(x, y, x, y + (len_barrier/2), color_barrier);
		LCD_DrawLine(x + 1, y, x + 1, y + (len_barrier/2), color_barrier);
		
		//new position
		y = y + (len_barrier/2);
		barrier_position.x = x;
		barrier_position.y = y;
		barrier_direction = 1;
		
		barrier_coordinate.x = barrier_coordinate.x + 1;
		barrier_coordinate.y = barrier_coordinate.y + 1;
		
	}
}


void update_barrier(void){
	
		char str[2];
	
		sprintf(str, "%i", player == 1 ? wallsPlayer1 : wallsPlayer2);
		GUI_Text(player == 1 ? 115 : 190, 280, (uint8_t *) str, Black, White);
	
}


//this function is called when select button of the joystick is pressed --> the position of the barrier is confirmed
void confirm_barrier(void){
	int permitted;
	permitted = createWall(player, barrier_coordinate.x, barrier_coordinate.y, barrier_direction, 1);
	
	if(permitted == 1){
		
		//change color of the barrier
		draw_barrier(barrier_position.x, barrier_position.y, barrier_direction, color_barrier_conf);
		
		//update number of remaining barriers of the actual player
		update_barrier();
		
		//disable button 2
		NVIC_DisableIRQ(EINT0_IRQn);     
		
	}
}


//Initial barrier
void create_barrier(void){
	int x;
	int y;
	barrier_direction = 0; // starts horizontal
	x = x_init + 3*l_cell + 3*dist_cell;
	y = y_init + 3*l_cell + 2*dist_cell + offset_barrier;
	
		LCD_DrawLine(x, y, x + len_barrier, y, color_barrier);
		LCD_DrawLine(x, y + 1, x + len_barrier, y + 1, color_barrier);
	
	barrier_position.x = x;
	barrier_position.y = y;
	
}

/***********************************************************************************
*
*		BOTTOM GRAPHIC PART 
*
************************************************************************************/


void bottom_info_bar(void){
	int i;

	distance_cell_tot = 0;
	border_dx = 17;
	leng_orizz = 55;
	leng_vert = 45;
	
	LCD_DrawLine(0, 245, 400, 245, Black);
	
	for(i = 0; i < 3; i++){
		
		if(i == 1){
			//Value of remaining Timer
			GUI_Text(20+distance_cell_tot+20,  270, (uint8_t *) label[i], Black, White);
			
			t = player;
/*			while(checkWinner() == -1){			//finchè non c'è ancora un vincitore
				if(t != player){
					i = 20;
					t = player;
				}
				init_timer(1, 0x17D7840);											// 1s 
				enable_timer(1);
			}*/
				init_timer(1, 0x17D7840);											// 1s 
				enable_timer(1);
			//Finito il tempo (20 secondi) Si esegue l'irqHandler di time1 <- qua metto il passggio all'altro player

			
		}else{
			
			//LABEL 1 and LABEL 2
			GUI_Text(20+distance_cell_tot, 260, (uint8_t *) label[i], Black, White);
			//Value of remaining barriers of player 1 and player 2
			if(i != 3){
				//values_barrier
				GUI_Text(20+distance_cell_tot+20, 280, (uint8_t *) values_barrier[i], Black, White);
			}
			
		}
		
	LCD_DrawLine(border_dx+distance_cell_tot, 255, border_dx+distance_cell_tot+leng_orizz, 255, Black); 											/*horizontal up*/
	LCD_DrawLine(border_dx+distance_cell_tot, 255, border_dx+distance_cell_tot, 255+leng_vert, Black); 											/*vertical sx*/
	LCD_DrawLine(border_dx+distance_cell_tot, 300, border_dx+distance_cell_tot+leng_orizz, 300, Black); 											/*horizontal down*/
	LCD_DrawLine(border_dx+distance_cell_tot+leng_orizz, 255, border_dx+distance_cell_tot+leng_orizz, 255+leng_vert, Black); 						/*vertical dx*/
		distance_cell_tot = distance_cell_tot + 75;
		
	}
	
	return;
}





void init_game(void){
	
	x_init = 30;
	y_init = 30;
	l_cell = 20;
	dist_cell = 7;
	inner_borderCell = 7;
	len_barrier = dist_cell + l_cell*2;
	step_player = l_cell + dist_cell;
	step_barrier = l_cell + dist_cell;
	
	//INIT GRAPHIC 
	create_board();
	
	//init player 1
	player_position1.x = x_init + l_cell*3 + 3*dist_cell;
	player_position1.y = y_init;
	draw_player(player_position1.x, player_position1.y, 1);
	
	//init player 2
	player_position2.x = x_init + l_cell*3 + 3*dist_cell;
	player_position2.y = y_init + l_cell*6 + 6*dist_cell;
	draw_player(player_position2.x, player_position2.y, 2);
	
	player1_coordinate.x = 0;
	player1_coordinate.y = 6;
	
	player2_coordinate.x = 12;
	player2_coordinate.y = 6;
	
	barrier_coordinate.x = 5;
	barrier_coordinate.y = 6;
	
	//turn of the game
	player = 2;
	
	bottom_info_bar();
	
	//matrix init
	initGame();
	
	//testing
	/*move_player(player_position1.x, player_position1.y, 1, 2);
	move_player(player_position1.x, player_position1.y, 1, 2);
	move_player(player_position1.x, player_position1.y, 1, 2);*/
		
	return;
}




