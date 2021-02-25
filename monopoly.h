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

typedef struct JOUEUR {
    char nom[15];
    int id;
    int argent;
    int position;
    DICE dice;
    int tour;
    int inventory[10]; 
    int gare;
    int services;
    int prison;
    int pass;
} JOUEUR; 

typedef struct SET {
    int id;
    char name[10];
    int prix;
    int max_properties;
} SET;

struct banque {
    int maisons;
    int hotels;
};

typedef struct SPACE {
    char nom[50];
    int prix;
    int loyer[6];
    SET set;
    int proprietaire;
    int maisons;
    int type;
} SPACE;

extern SPACE plateau[40];

/* ------ DEALING WITH INPUT ------ */
int   set_players (void);
void  set_name(JOUEUR *current_player, int position);
char  *user_input(char *string, size_t b, FILE *c);
int   check_total (int total_players);
void  press_enter(JOUEUR *current_player);
char  prompt_yn(const char *question);

/* ------ PRINTING INFOS ------ */
void  print_position(SPACE *space, JOUEUR *joueurs, JOUEUR *joueur);

/* ------ LAUNCHING GAME ------ */
void  initialize_players (JOUEUR *joueurs, int total_players);
void  sort_players(JOUEUR *joueurs, int participants);
void  set_id(JOUEUR *joueurs, int participants);


/* ------ GAME MECHANICS ------ */
void throw_dice(JOUEUR *current_player);
void check_lap (JOUEUR *current_player);
void send_to_jail(JOUEUR *current_player, const char *message);
int get_out_jail(JOUEUR *current_player);
void go_prison(JOUEUR *current_player, JOUEUR *joueurs, SPACE *space);
JOUEUR pay_owner (JOUEUR *current_player, JOUEUR owner, SPACE *space);
void buy_property (JOUEUR *current_player, SPACE *space);
void buy_house (JOUEUR *current_player, SPACE *space);


#endif
