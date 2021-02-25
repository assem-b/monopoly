#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void check_lap (struct joueur *current_player) 
{
    if (current_player->position >= NB_SPACES) {
        current_player->position -= NB_SPACES;
        current_player->argent   += 200;
        current_player->tour     += 1;
        printf("You pass over GO +200$ \n");
    }

}

void send_to_jail (struct joueur *current_player, const char *message) 
{
    current_player->position = 10;
    current_player->prison   =  5;
    current_player->dice.row =  0;
    printf("%s \n", message);    
}

void go_prison (struct joueur *current_player, struct joueur *joueurs, struct propriete *space)
{
    send_to_jail(current_player, "Bad luck !");
    current_player->prison -= 1;
    *space = plateau[current_player->position];
    print_position(space, joueurs, current_player);
}

static int escape_jail (struct joueur *current_player)
{
    printf("\n");
    throw_dice(current_player);
    if (current_player->dice.row == 1) {
        printf("Well done you made a double ! You're free. \n"); 
        return 0;
    }
 
    current_player->prison -= 1;
    int chances = current_player->prison - 1;
    
    if (chances > 0) 
        printf("You still have %d chances to make a double before paying 50$ to get out of jail.\n", chances);
    else 
        printf("Next time you have to pay 50$ to get out of jail. \n");
    
    return 1; 
}

static int pay_jail (struct joueur *current_player)
{
    current_player->argent -= 50;
    printf("You paid 50$ to get out of jail. \n");
    throw_dice(current_player);

    return 0;
}

int get_out_jail (struct joueur *current_player)
{
    int rc = -1;
    if (current_player->prison == 1)
        rc = pay_jail(current_player);
    else if (current_player->prison > 1 && current_player->prison < 5)
        rc = escape_jail(current_player);

    if (rc == 0) {
        current_player->dice.row = 0;
        current_player->prison   = 0;
        current_player->position += current_player->dice.sum;
        return 0;
    }
   
    if (current_player->prison == 5) current_player->prison -= 1; 
    rc = 1;
    return rc;
} 

static struct joueur draw_money (struct joueur *current_player, struct joueur owner, int fees)
{
    current_player->argent -= fees;
    owner.argent += fees;

    return owner;
}

struct joueur pay_owner (struct joueur *current_player, struct joueur owner, struct propriete *space) 
{
    int fees = 0;
    
    if (space->type == 0) fees = space->loyer[space->maisons];
    else if (space->type == 1) fees = space->loyer[owner.inventory[space->ensemble.id]- 1];
    
    else if (space->type == 2) {
        if (owner.inventory[space->ensemble.id] == 1) fees = current_player->dice.sum * 4;
        else if (owner.inventory[space->ensemble.id] == 2) fees = current_player->dice.sum * 10;
    }

    owner = draw_money(current_player, owner, fees);
 
    printf("%s owns %d to %s", current_player->nom, fees, owner.nom);

    return owner;
}

void buy_property (struct joueur *current_player, struct propriete *space)
{
    char *question = "Do you want to buy the property ?";
    char answer = prompt_yn(question);
         
    if (answer == 'y' && current_player->argent > space->prix) {
        current_player->argent -= space->prix; 
        space->proprietaire     = current_player->id;
            
            if (current_player->inventory[space->ensemble.id] == 0)
                 current_player->inventory[space->ensemble.id] = 1;
            
            else  
                current_player->inventory[space->ensemble.id] += 1;                 

     if (space->type == 0 && current_player->inventory[space->ensemble.id] == space->ensemble.max_properties)
        printf("Well done ! You bought the whole set ! Next time you can build house. \n");           
    }

    return;   
}

void buy_house (struct joueur *current_player, struct propriete *space)
{
    char *question = "Do you want to buy a HOUSE ?";
    char answer    = prompt_yn(question); 

    if (answer == 'y' && (space->maisons < 4)) {
        current_player->argent -= space->ensemble.prix;
        if (!space->maisons) space->maisons = 1;
        else space->maisons += 1;
    }
    
    else if (answer == 'y' && space->maisons == 4) {
        current_player->argent -= space->ensemble.prix;
        space->maisons += 1;
    }

    else if (space->maisons == 5)
        printf("LEVEL MAX\n");

}







