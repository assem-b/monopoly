#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Dealing with user input */

static int check_for_int (char *nb_joueurs) //Check if every char can be converted to an int before using atoi
{
    unsigned c;
    for (c = 0; c < strlen(nb_joueurs); c++) {
        if (c != 0 && nb_joueurs[c] == '\n')
            nb_joueurs[c] = '\0';
        else if ( !isdigit(nb_joueurs[c]) )
            return 1;
    }
  
    return 0;
}

static char *keep_ask_number (int rc, char *nb_players) //If error keep asking for an input without letters
{
    while (rc == 1) {
        printf("Incorrect. Please type a number [2 - 12]: ");
        user_input(nb_players, sizeof(nb_players), stdin);
        rc = check_for_int(nb_players);
    }

    return nb_players;
}

int set_players (void) 
{
    printf("Number of players [2 - 12]: ");
    char *nb_players = malloc(3);
    
    user_input(nb_players, 3, stdin);
    int rc = check_for_int(nb_players);
     
    if (rc == 1) nb_players = keep_ask_number(rc, nb_players); 
    
    int total = atoi(nb_players); /* Validation is correct no danger to user atoi */
    free(nb_players);

    return total; 
}

int check_total (int total_players) 
{    
    while (total_players < 2 || total_players > 12){
        printf("Please type a number between 2 and 12 \n"); 
        total_players = set_players();
    }
  
    return total_players;    
}

void set_name (JOUEUR *current_player, int position)
{ 
    printf("Enter player name [%d]: ", position + 1);
    user_input(current_player->nom, sizeof(current_player->nom), stdin);
}

static void print_dice(JOUEUR *current_player)
{
    printf("Your result : %d (%d + %d) \n", current_player->dice.sum,
                                            current_player->dice.first,
                                            current_player->dice.second);
    if (current_player->prison  == 0)    
        if (current_player->dice.row == 2) printf("One more row and you go to jail\n");
}

void throw_dice(JOUEUR *current_player)  
{          
    DICE dice = current_player->dice;

    dice.first   = rand() % 6 + 1;
    dice.second  = rand() % 6 + 1;   
    dice.sum = dice.first + dice.second;
    
    if (dice.first == dice.second) dice.row += 1;
    else dice.row = 0;   

    current_player->dice = dice;
    print_dice(current_player);  
}

void sort_players(JOUEUR *joueurs, int participants) 
{
    JOUEUR tmp;

    for (int i = 0; i < participants; i++) {
        for (int j = 0; j < (participants - 1); j++) {
            if (joueurs[j].dice.sum < joueurs[j + 1].dice.sum ) {
                tmp = joueurs[j];
                joueurs[j] = joueurs[j + 1];
                joueurs[j + 1] = tmp;  
            }
         }
    }
}

void set_id(JOUEUR *joueurs, int participants)
{
    for(int i = 0; i < participants; i++) 
        joueurs[i].id = i;
}

void press_enter(JOUEUR *current_player) 
{
    printf("\n\n");
    printf("It's up to %s [Money: %d$] [Lap: %d] [ENTER TO CONTINUE]", current_player->nom,
                                                                       current_player->argent,
                                                                       current_player->tour);
    getchar();
    
}


static void print_private_property (SPACE *space, JOUEUR *joueurs, JOUEUR *current_player) 
{ 
    printf("[PRICE: %d] ", space->prix);
    char *owner = NULL;
     if (space->proprietaire != -1) { 
        owner = joueurs[space->proprietaire].nom; 
        printf("[OWNER: %s] ", owner);
     }
     printf("[SET: %s] ", space->set.name);
     if (space->proprietaire == current_player->id) 
         printf("[SET ACQUIRED: %d/%d] ", current_player->inventory[space->set.id], 
                                          space->set.max_properties);
     if (space->maisons)
         printf("[HOUSES OWNED: %d]", space->maisons);
}


void print_position(SPACE *space, JOUEUR *joueurs, JOUEUR *current_player) 
{
    printf("%s [POSITION: %d] ", space->nom, current_player->position);

    if (space->type == 0 || space->type == 1 || space->type == 2)  
        print_private_property(space, joueurs, current_player);

    printf("\n");        
         
}





