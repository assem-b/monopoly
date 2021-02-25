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
int   set_players (void);
void  set_name(struct joueur *current_player, int position);
char  *user_input(char *string, size_t b, FILE *c);
int   check_total (int total_players);
void  press_enter(struct joueur *current_player);
char  prompt_yn(const char *question);

/* ------ PRINTING INFOS ------ */
void  print_position(struct propriete *space, struct joueur *joueurs, struct joueur *joueur);

/* ------ LAUNCHING GAME ------ */
void  sort_players(struct joueur *joueurs, int participants);
void  set_id(struct joueur *joueurs, int participants);

/* ------ GAME MECHANICS ------ */
void throw_dice(struct joueur *current_player);
void check_lap (struct joueur *current_player);
void send_to_jail(struct joueur *current_player, const char *message);
int get_out_jail(struct joueur *current_player);
void go_prison(struct joueur *current_player, struct joueur *joueurs, struct propriete *space);
struct joueur pay_owner (struct joueur *current_player, struct joueur owner, struct propriete *space);
void buy_property (struct joueur *current_player, struct propriete *space);
void buy_house (struct joueur *current_player, struct propriete *space);


#endif
