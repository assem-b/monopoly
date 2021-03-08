#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Initialize all undefined value 
void initialize_players (BOARD *board)
{
    for (int i = 0; i < board->nb_players; i++) {
        set_name(&board->players[i], i);
        board->players[i].prison   = 0;
        board->players[i].dice.row = 0;
        board->players[i].tour     = 0;
        board->players[i].position = 0;
        board->players[i].bankrupt = 0;
        board->players[i].houses   = 0;
        board->players[i].hotels   = 0; 
        for (int j = 0; j < 11; j++)
            board->players[i].inventory[j] = 0;

        board->players[i].money = 1500;
        roll_dice(&board->players[i]);        
    }         
}

//If player is bankrupted every owned space is reset
static void reset_properties (PLAYER *player, BOARD *board)
{
    for (int i = 0;  i < 40; i++) {
        if ((  board->spaces[i].type == 0 
            || board->spaces[i].type == 1
            || board->spaces[i].type == 2)
            && player->id == board->spaces[i].owner) {
            board->spaces[i].owner  = -1;
            board->spaces[i].houses =  0;
        }
     } 
 
    return;
}

void remove_player (PLAYER *player, BOARD *board)
{
   player->bankrupt = 1;   
   
   reset_properties(player, board); 
   printf("! %s is bankrupt ! \n", player->name); 

   board->active_players -= 1;
   int last_element = board->active_players - 1;

   board->loosers[last_element] = *player;
}

int check_bankruptcy (BOARD *board, int i)
{
    while (board->players[i].bankrupt == 1) {
        if (i == board->nb_players - 1) 
            i = 0;
        else 
            ++i;
    }

     return i;
}

/* This function keeps track of the number of laps 
 * the player accomplished. According to the rules 
 * each time GO is passed on, the player receive 200$ */

void check_lap (PLAYER *player) 
{
    if (player->position >= NB_SPACES) { 
        player->position -= NB_SPACES;           
        player->money    += 200;           
        player->tour     += 1;
        printf("You pass over GO +200$ \n");
    }
}

int draw_money (PLAYER *player, int fees, BOARD *board)
{
    if (fees > player->money) fees = player->money;

    player->money -= fees; 

    if (player->money < 1) remove_player(player, board);  

    return fees;   
}

static int is_setComplete (PLAYER *player, SPACE *space)
{
    int owned_set = player->inventory[space->set.id];
    int whole_set = space->set.max_properties;

    if (owned_set == whole_set) return 1;

    return 0;
}

void mortgage_property (PLAYER *player, SPACE *space, BOARD *board) 
{
    space->mortgage = 1;

    int amount = space->price / 2;

    player->money += amount;     

}

static void sell_house (PLAYER *player, SPACE *space, BOARD *board)
{
    int amount;
    amount = space->set.price / 2;
  
    if (space->houses == 5) 
        board->bank.hotels += 1;
     
    if (space->houses < 4)
        board->bank.houses += 1;

    print_bank(board);

    player->money += amount;

    return;
}


void build_or_mortgage (PLAYER *player, SPACE *space, BOARD *board)
{ 
    int set_complete = is_setComplete(player, space);

    char answer;
     
    if (space->houses == 0 && set_complete == 0) {
        answer = prompt_yn("Do you want to mortgage property ?", 'Y', 'N', '\0');
        if (answer == 'Y') mortgage_property(player, space, board);
    }

    if (space->houses == 0 && set_complete) {
        answer = prompt_yn("(B)uild or (M)ortgage or do (N)othing", 'B', 'M', 'N');
        if (answer == 'B')  buy_house(player, space, board);
        if (answer == 'M')  mortgage_property(player, space, board);
    }

    if (space->houses > 0 && set_complete) {
       answer = prompt_yn("(B)uild or (S)ell houses or do (N)othing ?", 'S', 'B', 'N');
       if (answer == 'B') buy_house(player, space, board); 
       if (answer == 'S') sell_house(player, space, board);
    }


    return;
}

static int pay_rent (int rent, SPACE *space, PLAYER *owner) 
{   
    int whole_set = is_setComplete(owner, space);
  
    rent = space->loyer[space->houses]; 

    if (whole_set == 1 && space->houses == 0)
        rent *= 2;

    return rent;
}

static int pay_railroad (int fees, PLAYER *owner, SPACE *space)
{
    fees = space->loyer[owner->inventory[space->set.id] - 1];   
    return fees;
}

static int pay_utilitie (int fees, PLAYER *player, PLAYER *owner, SPACE *space)
{
    if (owner->inventory[space->set.id] == 1)
        fees = player->dice.sum * 4;
    
    else if (owner->inventory[space->set.id] == 2) 
        fees = player->dice.sum * 10;
    
    return fees;
}


void pay_owner (PLAYER *player, SPACE *space, BOARD *board) 
{
    int fees = 0;

    PLAYER *owner = &board->players[space->owner];
 
    if (space->type == 0 && space->mortgage == 0)
        fees = pay_rent(fees, space, owner);  
  
    else if (space->type == 1)
        fees = pay_railroad(fees, owner, space);
    
    else if (space->type == 2) 
        fees = pay_utilitie (fees, player, owner, space);
  
    owner->money += draw_money(player, fees, board);
 
    if (space->type == 0 && space->mortgage == 1)
        printf("The property is mortgage, you owe nothing to %s. \n", owner->name);
    else
        printf("%s owe %d to %s. \n", player->name, fees, owner->name);

}



int is_affordable (PLAYER *player, int price, const char *message) //Solvability
{
    if (player->money > price) return 0; 
    
    printf("You don't have enough money for %s \n", message); 
    
    return 1;
}

void buy_property (PLAYER *player, SPACE *space)
{  
    int rc = is_affordable(player, space->price, space->name);   
    if (rc == 1) return;

    const char *question = "Do you want to buy the property ?";
    const char answer = prompt_yn(question, 'Y', 'N', '\0');
    
    if (answer == 'Y') {
        player->money -= space->price; 
        space->owner   = player->id; 
        player->inventory[space->set.id] += 1;                 

        if (space->type == 0 && player->inventory[space->set.id] == space->set.max_properties)
            printf("Well done ! You bought the whole set ! Next time you can build house. \n");           
    }

    return;   
}

static char *question_buy (int nb_houses) 
{
    char *house_or_hotel;  /* This function check if the word hotel or house has to be used */ 
    
    if (nb_houses < 4) 
        house_or_hotel = "Do you want to buy a house ?";
    else
        house_or_hotel = "Do you want to buy a hotel ?";

    return house_or_hotel;
}


static void suggest_house (PLAYER *player, BOARD *board, SPACE *space) 
{
   const char *house_or_hotel;
   if (space->houses < 4) house_or_hotel = "house";
   else house_or_hotel = "hotel";
   
   printf("To build %s you need to build there first:\n", house_or_hotel);
   
   for (int i = 0; i < space->set.max_properties; i++) {
       
       if (player->position != space->set.properties[i] 
           && space->houses > board->spaces[space->set.properties[i]].houses)


           printf("%s [HOUSE OWNED: %d]\n", board->spaces[space->set.properties[i]].name,
                                            board->spaces[space->set.properties[i]].houses);
   }
   
   return;
}

static int is_linearProgression (PLAYER *player, BOARD *board, SPACE *space)
{
    int iteration  = space->set.max_properties;
    SET set = space->set;
 
    for (int i = 0; i < iteration; i++) {
        if (player->position != space->set.properties[i]
            && space->houses > board->spaces[set.properties[i]].houses) {
            suggest_house (player, board, space);           
            return 1;
         }
    }
 
    return 0;
}


static int is_houseAvailable (BOARD *board, int nb_houses)
{
    if (board->bank.houses == 0 && nb_houses < 4) {
        printf("The bank has no house to sell. \n");
        return 1;
    }

    if (board->bank.hotels == 0 && nb_houses == 4) {
        printf("The bank has no hotel to sell. \n");
        return 1;
    }

    return 0;
} 
 
void buy_house (PLAYER *player, SPACE *space, BOARD *board)
{  
    if (space->mortgage == 1) {
        printf("Cannot build on a morgaged property"); 
        return;
    }

    if (space->houses == 5) {
        printf("You reach the level max. \n");
        return;
    }

    int rc = is_setComplete(player, space); 
    if (rc == 0) {
        printf("You must own the whole set before building houses. \n");
        return;
     }
    
    rc = is_linearProgression(player, board, space);
    if (rc == 1) return; 

    rc = is_houseAvailable(board, space->houses);
    if (rc == 1) return;

    rc = is_affordable(player, space->set.price, "house");
    if (rc == 1) return;

    const char *question = question_buy(space->houses);   
    const char answer    = prompt_yn(question, 'Y', 'N'); 

    if (answer == 'Y' && (space->houses < 5)) {
        player->money -= space->set.price;

        if (space->houses < 4)
            board->bank.houses -= 1;
        if (space->houses == 4)
            board->bank.hotels -= 1;
        
        print_bank(board);
        space->houses += 1;
    }
    
    return;
}







