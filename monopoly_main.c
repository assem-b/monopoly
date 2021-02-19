#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum space_category { PRIVATE_PROPERTY, RAILROAD,
                      UTILITIE, TAX,
                      COMMUNITY_CHEST, CHANCE,
                      NOTHING_HAPPEN, PRISON, GO_TO_PRISON };

int main ()
{
    srand(time(NULL));

    printf("Nombre de joueurs [2 - 12]: ");
    
    char nb_joueurs[3];
    unsigned total_players = get_int(nb_joueurs); 

    while (total_players < 2 || total_players > 12) {
        printf("Il faut un chiffre entre 2 et 12, vous avez tapé [%d]: ", total_players);
        total_players = get_int(nb_joueurs);
    }

    struct joueur joueurs[total_players]; 
    struct joueur *current_player = (struct joueur *)malloc(sizeof(struct joueur));

    for (int i = 0; i < total_players; i++) {
        *current_player = joueurs[i]; 
        give_name(current_player, i);    
      
        current_player->dice.row =    0;  /* Definining some value to avoid    */
        current_player->position =    0;  /* incrementation on undefined value */
        current_player->tour     =    0;
        current_player->argent   = 1500;  /* Each player starts with 1500$     */

        throw_dice(current_player);
        joueurs[i] = *current_player;
    }
     
    sort_players(joueurs, total_players); /* Dice score sorted by descending order */ 
    give_id(joueurs, total_players);      /* Each player has an ID: position in the array + 1 */

    printf("-------------- LANCEMENT DU JEU -------------- \n");

    struct propriete *space = (struct propriete *)malloc(sizeof(struct propriete));

    for (int i = 0; i < total_players; i++) {
         
        // Check if player has money
        *current_player = joueurs[i];

        wait_enter(current_player);
        throw_dice(current_player);        
        current_player->position += current_player->dice.sum;

        check_row(current_player); /* check row before lap */
        check_lap(current_player); /* to prevent him from getting 200$ */

        *space = plateau[current_player->position];

        if (space->type == PRIVATE_PROPERTY) {
             print_position(space, joueurs, current_player);
             if (!space->proprietaire && current_player->argent > space->prix)
                 buy_property(current_player, space);
             //else if (space, *joueurs).proprietaire != current_player.id)
             //else if (space, *joueurs).proprietaire == current_player.id)            
 
        }

        else if (space->type == RAILROAD) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == UTILITIE) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == TAX) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == COMMUNITY_CHEST) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == CHANCE) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == NOTHING_HAPPEN) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == PRISON) {
            print_position(space, joueurs, current_player);
        }

        else if (space->type == GO_TO_PRISON) {
            print_position(space, joueurs, current_player);
        }

        joueurs[i] = *current_player;
        plateau[current_player->position] = *space;

        if ( i == (total_players - 1) ) /* if this the last player */
            i = -1;                    /* reset to -1 to go back to the first */

       
    }

    return 0;
}
