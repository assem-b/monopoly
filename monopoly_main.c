#include "dbg.h"
#include "monopoly.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int NO_OWNER  = -1;             
const int COMMUNITY_CHEST_CARDS = 16;
const int CHANCES_CARDS = 12;

enum type { STREET,
            RAILROAD,
            UTILITY,
            TAX,
            COMMUNITY_CHEST,
            CHANCE, 
            NOTHING_HAPPEN,
            PRISON, 
            GO_TO_PRISON };

int main ()
{
    srand(time(NULL));  

    BOARD *board = &board_classic;

    set_players(board); 
    check_total(board); 

    board->active_players = board->nb_players;

    PLAYER joueurs[board->nb_players];
    PLAYER loosers[board->nb_players];
    
    board->players = joueurs; 
    board->loosers = loosers;

    initialize_players(board);
    sort_players(board);  
    set_id(board);      

    for (int i = 0; i < (board->nb_players); i++)
        printf("%s \n", board->players[i].name);

    printf("-------------- LANCEMENT DU JEU -------------- \n");

    PLAYER *player;
    SPACE *space;

    for (int i = 0; i < board->nb_players; i++) {
        
        i = check_bankruptcy (board, i);     
  
        player = &board->players[i];
        press_enter(player);

        if (player->prison == 0) {
            roll_dice(player);        
            player->position += player->dice.sum;
        }

        if (player->dice.row == 3) 
            jail_player(player, "You made three doubles in a row."); 
        
        check_lap(player);                                    

new_position:
        space = &board->spaces[player->position];
        print_position(space, board->players, player);

        if (space->type == STREET || space->type == RAILROAD || space->type == UTILITY) {     

            if (space->owner == NO_OWNER)
                buy_property(player, space);
                
            else if (space->owner != player->id) 
                pay_owner(player, space, board);        

            else if (space->type == STREET && space->owner == player->id) 
                build_or_mortgage(player, space, board);
                                       
            board->spaces[player->position] = *space; 
        }       

        else if (space->type == TAX) 
            draw_money(player, space->price, board);

        else if (space->type == COMMUNITY_CHEST) {
            cards (community_chest) = comm_chest[rand() % COMMUNITY_CHEST_CARDS  + 0];
            int move_player = community_chest(player); 
            if (move_player) goto new_position;
        }

        else if (space->type == CHANCE) {
            cards (chance) = chances[rand() % CHANCES_CARDS + 0];
            int move_player = chance(player); 
            if (move_player) goto new_position;
        }      

        else if (space->type == PRISON && player->prison > 0) {
            int rc = is_jailed(player, board);
            if (rc == 0) goto new_position;
        }

        else if (space->type == GO_TO_PRISON) 
            send_jail(player, board, space);
      
        
        if (board->active_players == 1) break;         
 
        int last_player = board->nb_players - 1;
        if (i == last_player) i = -1; /* reset the loop */
       
    }
    
    print_winner(board);
    print_loosers(board);
 
    return 0;
}
