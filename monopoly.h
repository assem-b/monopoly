#ifndef _monopoly_h
#define _monopoly_h

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

int   validation_number (char *entree);
int   get_int (char *entree);
void  get_name(struct joueur *current_player, int position);
void  throw_dice(struct joueur *current_player);

void  press_enter(struct joueur *current_player);
void  descending_order(struct joueur *joueurs, int participants);
void  attribution_id(struct joueur *joueurs, int participants);

void  print_position(struct propriete *space, struct joueur *joueurs);
void  print_dice(struct DICE dice_player);

/* ------ GAME MECHANICS ------ */

void check_lap (struct joueur *current_player);
void check_row (struct joueur *current_player);
char get_yn (char *message);
void buy_property (struct joueur *current_player, struct propriete *space);
#endif
