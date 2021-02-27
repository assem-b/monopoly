#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define NO_OWNER -1             

#define PLAYER_AFFORD_PROPERTY    current_player->argent > space->prix
#define PLAYER_AFFORD_HOUSE       current_player->argent > space->set.prix 
#define PLAYER_IS_OWNER           space->proprietaire == current_player->id
#define PLAYER_OWNS_WHOLE_SET     current_player->inventory[space->set.id] == space->set.max_properties
#define OWNER_IS_NOT_PLAYER       (space->proprietaire != -1) && (space->proprietaire != current_player->id)
#define OWNER                     joueurs[space->proprietaire]

enum space_category { STREET, RAILROAD, UTILITY, TAX,
                      COMMUNITY_CHEST, CHANCE,
                      NOTHING_HAPPEN, PRISON, GO_TO_PRISON };

int main ()
{
    srand(time(NULL));
  
    unsigned total_players = set_players(); 
    total_players = check_total(total_players);  /* Has to be between 2 - 12 */

    JOUEUR joueurs[total_players]; 

    initialize_players(joueurs,  total_players);
    sort_players(joueurs, total_players); /* Dice score sorted by descending order */ 
    set_id(joueurs, total_players);      /* Each player has an ID*/

    printf("-------------- LANCEMENT DU JEU -------------- \n");

    JOUEUR *current_player = malloc(sizeof(JOUEUR));
    SPACE *space       = malloc(sizeof(SPACE));

    for (int i = 0; i < total_players; i++) {
         
        // Check if player has money
        *current_player = joueurs[i];
        press_enter(current_player);

        if (current_player->prison == 0) {
            throw_dice(current_player);        
            current_player->position += current_player->dice.sum;
        }

        if (current_player->dice.row == 3) 
            send_to_jail(current_player, "You made three doubles in a row."); 
        
        check_lap(current_player);                                    

out_of_jail:
        *space = board[current_player->position];
        print_position(space, joueurs, current_player);

	if (space->type == STREET || space->type == RAILROAD || space->type == UTILITY) {     

             if (space->proprietaire == NO_OWNER)
                 buy_property(current_player, space);
              
             else if (space->proprietaire != current_player->id) 
                 OWNER = pay_owner(current_player, OWNER, space);        

             else if (space->type == STREET && space->proprietaire == current_player->id) 
                 buy_house(current_player, space);             
             
        }

        else if (space->type == TAX) {
            printf("%s pays %d of taxes", current_player->nom, space->prix);
            current_player->argent -= space->prix;
        }

        else if (space->type == COMMUNITY_CHEST) {

        }

        else if (space->type == CHANCE) {

        }     

        else if (space->type == PRISON) {
            if (current_player->prison > 0) {
                int rc = get_out_jail(current_player);
                if (rc == 0) goto out_of_jail;
            }
        }

        else if (space->type == GO_TO_PRISON) 
            go_prison(current_player, joueurs, space);
        

        joueurs[i] = *current_player;
        board[current_player->position] = *space;

        if ( i == (total_players - 1) ) /* if this the last player */
            i = -1;                    /* reset to -1 to go back to the first */
      
    }

    return 0;
}
