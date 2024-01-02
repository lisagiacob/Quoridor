/*
*		Board implementation
*/

#include "board.h"
#include "graphic.h"

unsigned int board[13][13] = {{0}};
unsigned int player1[1][2] = {{0,6}};
unsigned int player2[1][2] = {{12,6}};
unsigned int wallsPlayer1 = 8;
unsigned int wallsPlayer2 = 8;

void initGame(void){
	board[0][6] = 1;
	board[12][6] = 2;
}

int checkWinner(void){
	int i;
	
	for(i = 0; i < 13; i++){
		if(board[0][i] == 2){
			//player2 wins
			return 2;
		}else if (board[i][12] == 1){
			//player1 wins
			return 1;
		}
	}
	return -1;
}

/*Get the player name and move it sing the direction, if possible
* (direction = 0 -> up; direction = 1 -> dx; direction = 2 -> down; direction = 3 -> sx)
* It returns:
*			0 -> if a wall is already present, the move is out of board
*     1 -> if player 1 won
*     2 -> if player 2 won
*     -1 -> if none wins
*/
int movePlayer(unsigned int player, unsigned int direction){
	unsigned int x,y;
	int wallChecker;
	int oldX, oldY;
	
	if(player == 1){
		x = player1[0][0];
		y = player1[0][1];
	}else if(player == 2){
		x = player2[0][0];
		y = player2[0][1];
	}else{
		return 0;
	}		
	
	switch(direction){
		//Up
		case 0:
			wallChecker = x - 1;
			
			if(board[wallChecker][y] != 3){
				if(wallChecker - 1 < 0){
					//out of board
					return 0;
				}else if(board[wallChecker - 1][y] == 1 || board[wallChecker - 1][y] == 2){
						//jump other player
						wallChecker = wallChecker - 2;
						if(wallChecker - 1 < 0){
							//out of board
							return 0;
						}
						
						if(board[wallChecker][y] != 3){
							x = wallChecker - 1;
						}else{
							return 0;
						}
				}else{
					x = wallChecker - 1;
				}
			}else{
				return 0;
			}
			break;
		//Dx
		case 1:
			wallChecker = y + 1;
			
			if(board[x][wallChecker] != 3){
				if(wallChecker + 1 > 12){
					//out of board
					return 0;
				}else if(board[x][wallChecker + 1] == 1 || board[x][wallChecker + 1] == 2){
						//jump other player
						wallChecker = wallChecker + 2;
						if(wallChecker + 1 > 12){
							//out of board
							return 0;
						}
						
						if(board[x][wallChecker] != 3){
							y = wallChecker + 1;
						}else{
							return 0;
						}
				}else{
					y = wallChecker + 1;
				}
			}else{
				return 0;
			}
			break;
		//Down
		case 2:
			wallChecker = x + 1;
			
			if(board[wallChecker][y] != 3){
				if(wallChecker + 1 > 12){
					//out of board
					return 0;
				}else if(board[wallChecker + 1][y] == 1 || board[wallChecker + 1][y] == 2){
						//jump other player
						wallChecker = wallChecker + 2;
						if(wallChecker + 1 > 12){
							//out of board
							return 0;
						}
						
						if(board[wallChecker][y] != 3){
							x = wallChecker + 1;
						}else{
							return 0;
						}
				}else{
					x = wallChecker + 1;
				}
			}else{
				return 0;
			}
			break;
		//Sx
		case 3:
			wallChecker = y - 1;
			
			if(board[x][wallChecker] != 3){
				if(wallChecker - 1 < 0){
					//out of board
					return 0;
				}else if(board[x][wallChecker - 1] == 1 || board[x][wallChecker - 1] == 2){
						//jump other player
						wallChecker = wallChecker - 2;
						if(wallChecker - 1 < 0){
							//out of board
							return 0;
						}
						
						if(board[x][wallChecker] != 3){
							y = wallChecker - 1;
						}else{
							return 0;
						}
				}else{
					y = wallChecker - 1;
				}
			}else{
				return 0;
			}
			break;
	}
	
	if(player == 1){
		oldX = player1[0][0];
		oldY = player1[0][1];
		board[oldX][oldY] = 0;
		board[x][y] = 1;
		player1[0][0] = x;
		player1[0][1] = y;
	}else if(player == 2){
		oldX = player2[0][0];
		oldY = player2[0][1];
		board[oldX][oldY] = 0;
		board[x][y] = 2;
		player2[0][0] = x;
		player2[0][1] = y;
	}
	
	return checkWinner();
}

/*Get the left end of the wall and its orientation and move it in the x, y positon, if possible
* (if alpha = 0 then horizontal, if alpha = 1 then vertical).
* If confirm_wall is equal to 1, we want to insert the wall.
* It returns:
*			0 -> if another wall is already present in the selected spot or if aplha, x or y are invalid
*     1 -> if the wall has been placed or can be placed (based on confirm_wall)
*     2 -> if the player finished the available walls
*/
int createWall(unsigned int player, int x, int y, int alpha, int confirm_wall){
	int x1, x2, y1, y2;
	
	if(player == 1 && wallsPlayer1 == 0){
			return 2;
		}else if(player == 2 && wallsPlayer2 == 0){
			return 2;
		}
	
	if((x%2 == 0 && y%2 != 0) || (x%2 != 0 && y%2 == 0)){
		if(alpha == 0 && (x >= 1 && x <= 11) && (y >= 0 && y <= 10)){
			y1 = y + 1;
			y2 = y1 + 1;
			if((board[x][y] == 0 || board[x][y1] == 0 || board[x][y2] == 0)){
				if(confirm_wall){
					//save wall
					board[x][y] = 3;
					board[x][y1] = 3;
					board[x][y2] = 3;
				}
			}else{
				//occupied
				return 0;
			}
		}else if(alpha == 1 && (x >= 2 && x <= 12) && (y >= 1 && y <= 11)){
			x1 = x - 1;
			x2 = x1 - 1;
			if((board[x][y] == 0 && board[x1][y] == 0 && board[x2][y] == 0)){
				if(confirm_wall){
					//save wall
					board[x][y] = 3;
					board[x1][y] = 3;
					board[x2][y] = 3;
				}
			}else{
				//occupied
				return 0;
			}
		}else{
			return 0;
		}
		
		if(confirm_wall){
			if(player == 1){
				wallsPlayer1--;
			}else if(player == 2){
				wallsPlayer2--;
			}
		}
	}
	return 1;
}

