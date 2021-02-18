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
        current_player->position -= NB_SPACES - 1;
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
    int answer = getchar();
    while ( answer != 'y' && answer != 'n' ) {
        printf("Incorrect answer, answer by [y/n]: ");
        while ((answer = getchar()) != '\n');
        answer = getchar();
    }
    return answer; 
}

void buy_property (struct joueur *current_player, struct propriete *space)
{
    char *message = "Do you want to buy the property ?";
    char answer = get_yn(message);   
    
    if (answer == 'y' && current_player->argent > space->prix) {
        current_player->argent -= space->prix; 
        space->proprietaire     = current_player->id;
            
            if (!current_player->inventory[space->ensemble.id])
                 current_player->inventory[space->ensemble.id] = 1;
                         
            else if (current_player->inventory[space->ensemble.id] == space->ensemble.max_properties)
                printf("Congratulations ! You buy the whole set ! Next time you can build house \n");
            
            else 
                current_player->inventory[space->ensemble.id] = +1; 
    }   
}


