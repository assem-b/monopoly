#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

// Check if each character is a digit
static int validate_number (char *nb_players) 
{
    for (int i = 0; i < strlen(nb_players); i++) {
 
        if (i != 0 && nb_players[i] == '\n')
            nb_players[i] = '\0';

        else if ( !isdigit(nb_players[i]) )
            return 1;
    }
    
    return 0;
}

// If a character is not a digit, keep asking a number
static char *keep_asking (int rc, char *nb_players) 
{
    while (rc == 1) {
        printf("Incorrect. Please type a number [2 - 12]: ");
        user_input(nb_players, sizeof(nb_players), stdin);
        rc = validate_number(nb_players);
    }

    return nb_players;
}

// Choose a number of player 
void set_players (BOARD *board) 
{
    printf("Number of players [2 - 12]: ");
    char *nb_players = malloc(3);
    
    user_input(nb_players, 3, stdin);
    int rc = validate_number(nb_players);
     
    if (rc == 1) nb_players = keep_asking(rc, nb_players); 
    
    int total = atoi(nb_players); /* Validation is correct no danger to user atoi */
    free(nb_players);

    board->nb_players = total; 
}

// The correct number of player is between 2 & 12 otherwise it's incorrect
void check_total (BOARD *board) 
{    
    while (board->nb_players < 2 || board->nb_players > 12) {
        printf("Please type a number between 2 and 12 \n"); 
        set_players(board);
    }
      
}

// Take input for player name
void set_name (PLAYER *player, int position)
{ 
    printf("Enter player name [%d]: ", position + 1);
    user_input(player->name, sizeof(player->name), stdin);
}


// Print dice results and warn the player if two doubles are made
static void print_dice(PLAYER player)
{
    printf("Your result : %d (%d + %d) \n", player.dice.sum,
                                            player.dice.first,
                                            player.dice.second);

    if (player.prison  == 0 && player.dice.row == 2)    
        printf("One more row and you go to jail\n");
}


// Two dice are rolled 
void roll_dice(PLAYER *player)  
{          
    DICE dice = player->dice;

    dice.first   = rand() % 6 + 1;
    dice.second  = rand() % 6 + 1;   
    dice.sum = dice.first + dice.second;
    
    if (dice.first == dice.second)
        dice.row += 1;
    else
        dice.row = 0;   

    player->dice = dice;
    print_dice(*player);  
}

// Sorting players with dice result in descending order 
void sort_players(BOARD *board) 
{
    PLAYER tmp;

    for (int i = 0; i < board->nb_players ; i++) {
        for (int j = 0; j < (board->nb_players - 1); j++) {
            if (board->players[j].dice.sum < board->players[j + 1].dice.sum ) {
                tmp = board->players[j];
                board->players[j] = board->players[j + 1];
                board->players[j + 1] = tmp;  
            }
         }
    }
}

//Each player is given an ID based on their index in the array
void set_id(BOARD *board){
    for(int i = 0; i < board->nb_players; i++) 
        board->players[i].id = i;
}

//Before waiting for pressing enter, player stats are displayed
void press_enter(PLAYER *player) 
{
    printf("\n\n");
    printf("It's up to %s [Money: %d$] [Lap: %d] [ENTER TO CONTINUE]", player->name,
                                                                       player->money,
                                                                       player->tour);
    getchar();
    return;    
}

//Print relevant information if space is a private property
static void print_private_property (SPACE *space, PLAYER *joueurs, PLAYER *player) 
{ 
    printf("[PRICE: %d] ", space->price);
    char *owner = NULL;

     if (space->owner != -1) { 
        owner = joueurs[space->owner].name; 
        printf("[OWNER: %s] ", owner);
     }
 
     printf("[SET: %s] ", space->set.name); 

     if (space->type == 0 && space->owner == player->id) {
         printf("\n[SET ACQUIRED: %d/%d] ", player->inventory[space->set.id], 
                                            space->set.max_properties);                                     
         printf("\n[MORTGAGE VALUE: %d] ", space->price / 2);
         printf("[UNMORTGAGE: %d] ", space->price + (space->price * 10 / 100));
     
     }

     if (space->houses)
         printf("[HOUSES OWNED: %d]", space->houses);

     return;
}

//Print space name and player position on the board
void print_position(SPACE *space, PLAYER *joueurs, PLAYER *player) 
{
    printf("%s [POSITION: %d] ", space->name, player->position);

    if (space->type == 0 || space->type == 1 || space->type == 2)  
        print_private_property(space, joueurs, player);

    printf("\n");        
    
    return;     
}

void print_bank (BOARD *board)
{
    if (board->bank.houses == 0 && board->bank.hotels == 0)
        printf("The bank has no more houses and hotels. \n");

    if (board->bank.houses == 0 && board->bank.hotels > 0)
        printf("The bank has no more house but  %d hotels. \n", board->bank.hotels);

    if (board->bank.houses > 0 && board->bank.hotels == 0)
        printf("The bank has %d houses but no hotel. \n", board->bank.houses);

    if (board->bank.houses > 0 && board->bank.hotels > 0)
       printf("Bank has %d houses and %d hotels. \n", board->bank.houses, board->bank.hotels);

    return;
}

void print_winner(BOARD *board)
{
    PLAYER winner;
   
    if (board->nb_players > 2) {
        for (int i = 0; i < (board->nb_players - 1); i++) {
            if (board->players[i].bankrupt == 0)
                winner = board->players[i];
         }
    }

    if (board->nb_players == 2) {
        for (int i = 0; i <= (board->nb_players - 1); i++) {
            if (board->players[i].bankrupt == 0)
                winner = board->players[i];
        }
    }

    printf("%s is the winner with %d$ \n", winner.name, winner.money);
}

void print_loosers(BOARD *board)
{
    for (int i = 0; i < (board->nb_players - 1); i++) 
        printf("%s \n", board->loosers[i].name);
}
       



