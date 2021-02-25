#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SPACE_IS_PRIVATE_PROPERTY space->type == PRIVATE_PROPERTY
#define SPACE_IS_RAILROAD         space->type == RAILROAD
#define SPACE_IS_UTILITIE         space->type == UTILITIE 
#define SPACE_IS_TAX              space->type == TAX
#define SPACE_IS_COMMUNITY_CHEST  space->type == COMMUNITY_CHEST
#define SPACE_IS_CHANCE           space->type == CHANCE
#define SPACE_IS_NOTHING_HAPPEN   space->type == NOTHING_HAPPEN
#define SPACE_IS_PRISON           space->type == PRISON
#define SPACE_IS_GO_TO_PRISON     space->type == GO_TO_PRISON
#define SPACE_NO_OWNER            (!space->proprietaire)             

#define PLAYER_AFFORD_PROPERTY    current_player->argent > space->prix
#define PLAYER_AFFORD_HOUSE       current_player->argent > space->ensemble.prix 
#define PLAYER_IS_OWNER           space->proprietaire == current_player->id
#define PLAYER_OWNS_WHOLE_SET     current_player->inventory[space->ensemble.id] == space->ensemble.max_properties

#define OWNER_IS_NOT_PLAYER       space->proprietaire && (space->proprietaire != current_player->id)
#define OWNER                     joueurs[space->proprietaire - 1]


enum space_category { PRIVATE_PROPERTY, RAILROAD,
                      UTILITIE, TAX,
                      COMMUNITY_CHEST, CHANCE,
                      NOTHING_HAPPEN, PRISON, GO_TO_PRISON };

int main ()
{
    srand(time(NULL));
  
    unsigned total_players = set_players(); 
    total_players = check_total(total_players);  /* Has to be between 2 - 12 */

    struct joueur joueurs[total_players]; 
    struct joueur *current_player = (struct joueur *)malloc(sizeof(struct joueur));

    for (int i = 0; i < total_players; i++) {
        *current_player = joueurs[i]; 
        set_name(current_player, i);    
        current_player->prison   =    0;
        current_player->dice.row =    0;  /* Initializing some value to avoid    */
        current_player->position =    0;  /* incrementation on undefined value */
        current_player->tour     =    0;
        for (int j = 0; j < 11; j++)
            current_player->inventory[j] = 0;

        current_player->argent   = 1500;  /* Each player starts with 1500$     */

        throw_dice(current_player);
        joueurs[i] = *current_player;
    }
     
    sort_players(joueurs, total_players); /* Dice score sorted by descending order */ 
    set_id(joueurs, total_players);      /* Each player has an ID: position in the array + 1 */

    printf("-------------- LANCEMENT DU JEU -------------- \n");

    struct propriete *space = (struct propriete *)malloc(sizeof(struct propriete));

    for (int i = 0; i < total_players; i++) {
         
        // Check if player has money
        *current_player = joueurs[i];

        press_enter(current_player);

        if (current_player->prison == 0) {
            throw_dice(current_player);        
            current_player->position += current_player->dice.sum;
        }

        if (current_player->dice.row == 3) 
            send_to_jail(current_player, "You made three doubles in a row."); /* check row before lap */
        
        check_lap(current_player);                                       /* to prevent him from getting 200$ */

out_of_jail:
        *space = plateau[current_player->position];

	if (space->type == 0 || space->type == 1 || space->type == 2) {
             print_position(space, joueurs, current_player);

             if (SPACE_NO_OWNER && PLAYER_AFFORD_PROPERTY)
                 buy_property(current_player, space);
              
             else if (OWNER_IS_NOT_PLAYER)
                 OWNER = pay_owner(current_player, OWNER, space);        
 
             else if (space->type == 0 && PLAYER_OWNS_WHOLE_SET && PLAYER_AFFORD_HOUSE)
                 buy_house(current_player, space);             
 
        }

        else if (SPACE_IS_TAX) {
            print_position(space, joueurs, current_player);
            printf("\n%s pays %d of taxes", current_player->nom, space->prix);
            current_player->argent -= space->prix;
        }

        else if (SPACE_IS_COMMUNITY_CHEST) {
            print_position(space, joueurs, current_player);
        }

        else if (SPACE_IS_CHANCE) {
            print_position(space, joueurs, current_player);
        }

        else if (SPACE_IS_NOTHING_HAPPEN) 
            print_position(space, joueurs, current_player);
        

        else if (SPACE_IS_PRISON) {
            print_position(space, joueurs, current_player);
            if (current_player->prison > 0) {
                int rc = get_out_jail(current_player);
                if (rc == 0) goto out_of_jail;
            }
        }

        else if (SPACE_IS_GO_TO_PRISON) {
            print_position(space, joueurs, current_player);
            go_prison(current_player, joueurs, space);
        }

        joueurs[i] = *current_player;
        plateau[current_player->position] = *space;

        if ( i == (total_players - 1) ) /* if this the last player */
            i = -1;                    /* reset to -1 to go back to the first */

       
    }

    return 0;
}
