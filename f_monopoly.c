#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Validation entrée utilisateur

int validation_number (char *nb_joueurs) //Check if every char can be converted to an int before using atoi
{
    unsigned c;
    for (c = 0; c < strlen(nb_joueurs); c++) {
        if (c != 0 && nb_joueurs[c] == '\n') nb_joueurs[c] = '\0';
        else if ( !isdigit(nb_joueurs[c]) ) return 1;
    }
  
    return 0;
}

int get_int (char *nb_joueurs) 
{
    take_input(nb_joueurs, sizeof(nb_joueurs), stdin);
    int rc = validation_number(nb_joueurs);
   
    while (rc == 1) {                                         /* If not a valid number */
        printf("Incorrect. Please type a number [2 - 12]: "); /* retry until it's correct */
        take_input(nb_joueurs, sizeof(nb_joueurs), stdin);      
        rc = validation_number(nb_joueurs);
    }

    int total = atoi(nb_joueurs); /* Validation is correct no danger to user atoi */
    return total; 
}



void give_name (struct joueur *current_player, int position)
{ 
    printf("Enter player name [%d]: ", position + 1);
    take_input(current_player->nom, sizeof(current_player->nom), stdin);
}



void throw_dice(struct joueur *current_player)  
{          
    struct DICE dice = current_player->dice;

    dice.first   = rand() % 6 + 1;
    dice.second  = rand() % 6 + 1;
   
    dice.sum = dice.first + dice.second;
    
    if (dice.first == dice.second) dice.row += 1;
    else dice.row = 0;   

    current_player->dice = dice;
    print_dice(current_player->dice);  
}

void sort_players(struct joueur *joueurs, int participants) 
{
    struct joueur tmp;

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

void give_id(struct joueur *joueurs, int participants)
{
    for(int i = 0; i < participants; i++) {
        joueurs[i].id = i + 1; //+1 to make id's starting from 1 and not zero
    }
}


void wait_enter(struct joueur *current_player) {
    printf("\n\nIt's up to %s [Money: %d$] [Lap: %d] [ENTER TO CONTINUE]", current_player->nom, current_player->argent, current_player->tour);
    getchar();
}

void print_position(struct propriete *space, struct joueur *joueurs, struct joueur *current_player) {
    char *owner = NULL;
    if (space->proprietaire) owner = joueurs[space->proprietaire - 1].nom; 
    printf("%s [POSITION: %d] [PRICE: %d] [OWNER: %s]\n ", space->nom, current_player->position, space->prix, owner); 
}

void print_dice(struct DICE dice) {
    printf("Your result : %d (%d + %d) \n", dice.sum, dice.first, dice.second);
    if (dice.row == 1) printf("Two more rows and you go to jail\n");
    else if (dice.row == 2)printf("One more row and you go to jail\n");
}






