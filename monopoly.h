#ifndef _monopoly_h
#define _monopoly_h
#include <stdio.h>

#define NB_SPACES 39

struct DICE {
    int sum;
    int first;
    int second;
    int row;
};



struct joueur {
    char nom[15];
    int id;
    int argent;
    int position;
    struct DICE dice;
    int tour;
    int inventory[10]; 
    int gare;
    int services;
    int prison;
    int pass;
}; 

struct couleur {
    int id;
    char name[10];
    int prix;
    int max_properties;
};

struct banque {
    int maisons;
    int hotels;
};

struct propriete {
    char nom[50];
    int prix;
    int loyer[6];
    struct couleur ensemble;
    int proprietaire;
    int maisons;
    int type;
};

extern struct propriete plateau[40];

/* ------ DEALING WITH INPUT ------ */
int   validation_number (char *nb_joueurs);
int   get_int (char *nb_joueurs);
void  give_name(struct joueur *current_player, int position);
char  *take_input(char *string, size_t b, FILE *c);
char  get_yn (char *message);
void  wait_enter(struct joueur *current_player);

/* ------ PRINTING INFOS ------ */
void  print_dice(struct DICE dice_player);
void  print_position(struct propriete *space, struct joueur *joueurs, struct joueur *joueur);

/* ------ LAUNCHING GAME ------ */
void  sort_players(struct joueur *joueurs, int participants);
void  give_id(struct joueur *joueurs, int participants);

/* ------ GAME MECHANICS ------ */

void throw_dice(struct joueur *current_player);
void check_lap (struct joueur *current_player);
void check_row (struct joueur *current_player);
void buy_property (struct joueur *current_player, struct propriete *space);

#endif
