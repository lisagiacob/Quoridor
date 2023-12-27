#include "../GLCD/GLCD.h" 

typedef struct {
    int x;
    int y;

}CoordinatePosition;

void init_game(void);

void create_barrier(void);
void confirm_barrier(void);
void move_player(uint16_t x, uint16_t y, unsigned int player, unsigned int move_direction);
void move_barrier(uint16_t x, uint16_t y, unsigned int angle_barrier, unsigned int move_direction);
void rotate_barrier(uint16_t x, uint16_t y);



