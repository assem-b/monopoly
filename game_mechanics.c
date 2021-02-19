#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void check_lap (struct joueur *current_player) 
{
    if (current_player->position > NB_SPACES) {
        current_player->position -= NB_SPACES;
        current_player->argent   += 200;
        current_player->tour     += 1;
        printf("You pass over GO +200$ \n");
    }

}

void check_row (struct joueur *current_player) 
{
    if (current_player->dice.row == 3) {
        current_player->position = 10;
        current_player->prison   =  4;
        current_player->dice.row =  0;
        printf("You make 3 double in a row, welcome to jail ! \n");
    }  
}


char get_yn (char *message) 
{
    printf("%s [y/n]: ", message);
    char answer[2];
    take_input(answer, sizeof(answer), stdin);
    while (answer[0] != 'y' && answer[0] != 'n' ) {
        printf("Incorrect answer, type [y/n]: ");
        take_input(answer, sizeof(answer), stdin);
    }
    return answer[0]; 
}

void buy_property (struct joueur *current_player, struct propriete *space)
{
    char *message = "Do you want to buy the property ?";
    char answer = get_yn(message);
         
    if (answer == 'y' && current_player->argent > space->prix) {
        current_player->argent -= space->prix; 
        space->proprietaire     = current_player->id;
            
            if (current_player->inventory[space->ensemble.id] == 0)
                 current_player->inventory[space->ensemble.id] = 1;
                         
            else if (current_player->inventory[space->ensemble.id] == space->ensemble.max_properties)
                printf("Congratulations ! You bought the whole set ! Next time you can build house \n");
            
            else 
                current_player->inventory[space->ensemble.id] += 1; 
    }   

}


