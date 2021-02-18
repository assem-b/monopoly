#include "dbg.h"
#include "monopoly.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Validation entrée utilisateur

int validation_number (char *nb_joueurs) 
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
    fgets(nb_joueurs, sizeof(nb_joueurs), stdin);
    int rc = validation_number(nb_joueurs);
   
    while (rc == 1) { 
        printf("Incorrect. Please type a number [2 - 12]");
        fgets(nb_joueurs, sizeof(nb_joueurs), stdin);
        rc = validation_number(nb_joueurs);
    }

    return atoi(nb_joueurs); 
}

void get_name (struct joueur *current_player, int position)
{
    char *nom = current_player->nom;   
    printf("Enter player name [%d]: ", position + 1);
    fgets(nom, sizeof(nom) + 1, stdin); // +1 for NULL BYTE 
    if (nom[strlen(nom) - 1] == '\n') 
        nom[strlen(nom) - 1] = '\0';
    else {
        int c;
        while((c = getchar()) != '\n' && c != EOF);
     } 
     *current_player->nom = *nom;    
}

void throw_dice(struct joueur *current_player)  
{          
    struct DICE dice = current_player->dice;

    dice.first   = rand() % 6 + 1;
    dice.second  = rand() % 6 + 1;
   
    dice.sum = dice.first + dice.second;
    
    if (dice.first == dice.second)
        dice.row += 1;
    else 
        dice.row = 0;   

    current_player->dice = dice;
    print_dice(current_player->dice);  
}

void descending_order(struct joueur *joueurs, int participants) 
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


void attribution_id(struct joueur *joueurs, int participants)
{
    for(int i = 0; i < participants; i++) {
        joueurs[i].id = i;
    }
}

void press_enter(struct joueur *current_player) {
    printf("It's up to %s [Money: %d$] [Lap: %d] [ENTER TO CONTINUE]", current_player->nom, current_player->argent, current_player->tour);
    int c;
    while((c = getchar()) != '\n');
}

void print_position(struct propriete *space, struct joueur *joueurs) {
    printf("%s \n\n", space->nom);
    if (space->proprietaire)
        printf("[OWNER: %s] \n", joueurs[space->proprietaire - 1].nom);
}

void print_dice(struct DICE dice) {
    printf("Your result : %d (%d + %d) \n", dice.sum, dice.first, dice.second);
    if (dice.row == 1)
        printf("Two more rows and you go to jail\n");
    else if (dice.row == 2)
        printf("One more row and you go to jail\n");
}






