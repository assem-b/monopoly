#ifndef _monopoly_h
#define _monopoly_h
#include <stdio.h>

#define NB_SPACES 39

typedef struct DICE {
    int sum;
    int first;
    int second;
    int row;
} DICE;

typedef struct PLAYER {
    char name[15];
    int id;
    int money;
    int position;
    DICE dice;
    int tour;
    int inventory[10]; 
    int prison;      
    int pass;
    int bankrupt;
    int hotels;
    int houses;
} PLAYER; 

typedef struct SET {
    int id;
    char name[10];
    int price;
    int max_properties;
    int properties[4];
} SET;

typedef struct SPACE {
    char name[50];
    int price;
    int loyer[6];
    SET set;
    int owner;
    int houses;
    int mortgage;
    int type;
} SPACE;

typedef struct BANK {
    int houses;
    int hotels;
} BANK;


typedef struct BOARD {
    int nb_players;
    int active_players;
    SPACE spaces[40];
    BANK bank;
    PLAYER *players;
    PLAYER *loosers;
} BOARD;


typedef int (*cards) (PLAYER *player);

extern BOARD board_classic;
extern cards chances[13];
extern cards comm_chest[17];

/* ------ DEALING WITH INPUT ------ */
void set_players (BOARD *board);
void set_name (PLAYER *player, int position);
char *user_input (char *string, size_t b, FILE *c);
void check_total (BOARD *board);
void press_enter (PLAYER *player);
char prompt_yn (const char *question, const char first_choice, const char second_choice, ...);

/* ------ PRINTING INFOS ------ */
void print_position (SPACE *space, PLAYER *joueurs, PLAYER *joueur);

/* ------ LAUNCHING GAME ------ */
void initialize_players (BOARD *board);
void sort_players (BOARD *board);
void set_id (BOARD *board);

/* ------ GAME MECHANICS ------ */
int check_bankruptcy(BOARD *board, int counter);
void roll_dice (PLAYER *player);
void check_lap  (PLAYER *player);

void jail_player (PLAYER *player, const char *message);
int  is_jailed (PLAYER *player, BOARD *board);
void send_jail (PLAYER *player, BOARD *board, SPACE *space);

void pay_owner (PLAYER *player, SPACE *space, BOARD *board);
int draw_money (PLAYER *player, int fees, BOARD *board);

void build_or_mortgage (PLAYER *player, SPACE *space, BOARD *board);
void buy_property (PLAYER *player, SPACE *space);
int check_house (PLAYER *player, SPACE *space);
void buy_house (PLAYER *player, SPACE *space, BOARD *board);

void print_bank(BOARD *board);
void print_winner(BOARD *board);
void print_loosers(BOARD *board);

/* ------- COMMON CARDS ------ */
int advance_to_go(PLAYER *player);
int get_out_of_jail (PLAYER *player); //Bad denomination
int street_repairs (PLAYER *player);

#endif
