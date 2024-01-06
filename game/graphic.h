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
void draw_player( uint16_t x, uint16_t y, unsigned int player);
void confirm_barrier(void);
void delete_barrier(uint16_t x, uint16_t y, unsigned int direction);
int limited_move(int jump, int x, int y);

void show_movement(uint16_t x, uint16_t y, int move_direction);
void confirm_player_movement(int move_direction);
void delete_movement(unsigned int l, uint16_t x, uint16_t y);
