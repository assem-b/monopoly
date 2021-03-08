#include "dbg.h"
#include "monopoly.h"

void advance_player (PLAYER *player, int space_position) {
    if (player->position > space_position) player->money += 200;
    player->position = space_position;
    printf("You move to %s. \n", board_classic.spaces[player->position].name);
}

void advance_nearest (PLAYER *player, int type) {
    while(board_classic.spaces[player->position].type != type) {
        if (player->position > NB_SPACES) player->position = 0;
        printf("[TCHOU] [TCHOU] %s \n", board_classic.spaces[player->position].name);
        player->position += 1;
    }
}

void win_money(PLAYER *player, int money, char *message) {
    printf("%s  ", message);
    player->money += money;
}

void loose_money(PLAYER *player, int money, char *message) {
    printf("%s  ", message);
    player->money -= money;
}

// Player is moved to given position and collect 200$ if go is passed.
int advance_Illinois (PLAYER *player) {
    advance_player(player, 24);
    return 1;
}

int advance_stCharles_place (PLAYER *player) {
    advance_player(player, 11);
    return 1;
}


//check payment
int advance_nearest_Utility (PLAYER *player) {
    printf("Trip to the nearest Utility. \n");
    advance_nearest(player, 2);
    return 1;

}

int advance_nearest_Railroad (PLAYER *player) {
    printf("Trip to the nearest Railroad ! \n");
    advance_nearest(player, 1);
    return 1;
}

int bank_dividend (PLAYER *player) {
    win_money(player, 50, "Bank pays you dividend of $50.");
    return 0;
}

int go_back_three (PLAYER *player) {
    printf("You go back three spaces. \n");
    player->position -= 3;
    return 1;
}

int pay_poor_tax (PLAYER *player) {
    loose_money(player, 15, "Pay poor tax $15.");
    return 0;
}

int trip_readingRailroad (PLAYER *player) {
    advance_player(player, 5);
    return 1;
}

int walk_boardwalk (PLAYER *player) {
    advance_player(player, 39);
    return 1;
}

int building_loan_mature (PLAYER *player) {
    win_money(player, 150, "Your building loan matures. Receive $150.");
    return 0;
}

int crossword_winner (PLAYER *player) {
    win_money(player, 100, "You have won a crossword competition $100.");
    return 0;
}

cards chances[13] = { advance_to_go,
                      advance_Illinois,
                      advance_stCharles_place,
                      advance_nearest_Utility,
                      advance_nearest_Railroad,
                      
                      bank_dividend,
                      go_back_three,
                      pay_poor_tax,
                      trip_readingRailroad,
                      
                      walk_boardwalk,
                      building_loan_mature,
                      crossword_winner  };
