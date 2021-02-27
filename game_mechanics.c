#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void initialize_players (JOUEUR *joueurs, int total_players)
{
    for (int i = 0; i < total_players; i++) {
        set_name(&joueurs[i], i);
        joueurs[i].prison   = 0;
        joueurs[i].dice.row = 0;
        joueurs[i].tour     = 0;
        joueurs[i].position = 0; 
        for (int j = 0; j < 11; j++)
            joueurs[i].inventory[j] = 0;

        joueurs[i].argent = 15000000;
        throw_dice(&joueurs[i]);        
    }         
}

void check_lap (JOUEUR *current_player) 
{
    if (current_player->position >= NB_SPACES) {   /* This function keeps track of the number  */
        current_player->position -= NB_SPACES;     /* of laps the player accomplished.         */
        current_player->argent   += 200;           /* Each lap the player receives 200$ from the bank */
        current_player->tour     += 1;
        printf("You pass over GO +200$ \n");
    }

}

void send_to_jail (JOUEUR *current_player, const char *message) 
{
    current_player->position = 10;  /* Player's position is prison's space */
    current_player->prison   =  5;  
    current_player->dice.row =  0;  
    printf("%s\n", message);    
}

void go_prison (JOUEUR *current_player, JOUEUR *joueurs, SPACE *space)
{
    send_to_jail(current_player, "Bad luck !");
    current_player->prison -= 1;
    *space = board[current_player->position];
    print_position(space, joueurs, current_player);
}

static int escape_jail (JOUEUR *current_player)
{
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

static int pay_jail (JOUEUR *current_player)
{
    current_player->argent -= 50;
    printf("You paid 50$ to get out of jail. \n");
    throw_dice(current_player);

    return 0;
}

int get_out_jail (JOUEUR *current_player)
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

static JOUEUR draw_money (JOUEUR *current_player, JOUEUR owner, int fees)
{
    current_player->argent -= fees;
    owner.argent += fees;

    return owner;
}

JOUEUR pay_owner (JOUEUR *current_player, JOUEUR owner, SPACE *space) 
{
    int fees = 0;
    
    if (space->type == 0) fees = space->loyer[space->maisons];
    else if (space->type == 1) fees = space->loyer[owner.inventory[space->set.id]- 1];
    
    else if (space->type == 2) {
        if (owner.inventory[space->set.id] == 1) fees = current_player->dice.sum * 4;
        else if (owner.inventory[space->set.id] == 2) fees = current_player->dice.sum * 10;
    }

    owner = draw_money(current_player, owner, fees);
 
    printf("%s owns %d to %s", current_player->nom, fees, owner.nom);

    return owner;
}

static int check_set_completion (JOUEUR *current_player, SPACE *space)
{
    int owned_set = current_player->inventory[space->set.id];
    int whole_set = space->set.max_properties; 

    if (owned_set == whole_set) return 0;
    
    printf("You must own the whole set before buying houses.\n"); 
    return 1; 
}

int check_money_necessary (JOUEUR *current_player, int price, const char *message) 
{
    if (current_player->argent > price) return 0; 
    
    printf("You don't have enough money for %s \n", message); 
    
    return 1;
}

void buy_property (JOUEUR *current_player, SPACE *space)
{  
    int rc = check_money_necessary(current_player, space->prix, space->nom);   
    if (rc == 1) return;

    const char *question = "Do you want to buy the property ?";
    const char answer = prompt_yn(question);
      
    if (answer == 'y') {
        current_player->argent -= space->prix; 
        space->proprietaire     = current_player->id; 
        current_player->inventory[space->set.id] += 1;                 

        if (space->type == 0 && current_player->inventory[space->set.id] == space->set.max_properties)
            printf("Well done ! You bought the whole set ! Next time you can build house. \n");           
    }

    return;   
}

static char *question_buy (int nb_houses) 
{
    char *house_or_hotel;  /* This function check if the word hotel or house has to be used */ 
    
    if (nb_houses < 4) house_or_hotel = "Do you want to buy a house ?";
    else house_or_hotel = "Do you want to buy a hotel ?";

    return house_or_hotel;
}


static void suggest_house (JOUEUR *current_player, SPACE *space) 
{
   const char *house_or_hotel;
   if (space->maisons < 4) house_or_hotel = "house";
   else house_or_hotel = "hotel";
   
   printf("To build %s you need to build there first:\n", house_or_hotel);
   
   for (int i = 0; i < space->set.max_properties; i++) {
       
       if (current_player->position != space->set.properties[i] 
           && space->maisons > board[space->set.properties[i]].maisons)

           printf("%s [HOUSE OWNED: %d]\n", board[space->set.properties[i]].nom,
                                            board[space->set.properties[i]].maisons);
   }
   
   return;
}


static int check_house_progression (JOUEUR *current_player, SPACE *space)
{
    int iteration  = space->set.max_properties;
    SET set = space->set;
 
    for (int i = 0; i < iteration; i++) {
        if (current_player->position != space->set.properties[i]
            && space->maisons > board[set.properties[i]].maisons) { 
            suggest_house(current_player, space);
            return 1;
         }
    }
 
    return 0;
}

static int check_house_maximum (SPACE *space)
{
    if (space->maisons == 5) {
        printf("You reach the maximum level\n");
        return 1;
    }

    return 0;
}

void buy_house (JOUEUR *current_player, SPACE *space)
{  
    int rc = check_house_maximum(space);
    if (rc == 1) return;    

    rc = check_set_completion(current_player, space); 
    if (rc == 1) return;
    
    rc = check_house_progression(current_player, space);
    if (rc == 1) return; 

    const char *question = question_buy(space->maisons);   
    const char answer    = prompt_yn(question); 
    
    if (answer == 'y' && (space->maisons < 5)) {
        current_player->argent -= space->set.prix;
        space->maisons += 1;
    }
    
    return;
}







