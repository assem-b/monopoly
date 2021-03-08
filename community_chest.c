#include "dbg.h"
#include "monopoly.h"

int advance_to_go (PLAYER *player) {
    printf("Advance to go and collect 200$");
    player->position = 0;
    player->money += 200;

    return 0;
}

int bank_error (PLAYER *player) {
    printf("Bank error in your favor ! +200$ \n");
    player->money += 200;
    return 0;
}

int doctor_fee (PLAYER *player) {
    printf("Doctor's fees -50$ \n");
    player->money -= 50;
    return 0;
}

int stock_sold (PLAYER *player) {
    printf("From sale of stock you won 50$ \n");
    player->money += 50;
    return 0;
}

int get_out_of_jail (PLAYER *player) {
    printf("You won a card to avoid jail. \n");
    player->pass = 1;
    return 0;
}

int go_to_jail (PLAYER *player) {
    printf("You pull a go to jail card ! \n");
    send_jail(player, &board_classic, &board_classic.spaces[player->position]);
    return 0;
}

int grand_opera_night (PLAYER *player) {
    printf("Grand Opera Night, you collect 50$ from every player. \n");
    int sum = 0;  
    for (int i = 0; i < board_classic.nb_players; i++) {
        if (board_classic.players[i].id != player->id && board_classic.players[i].bankrupt == 0) {
            sum += 50;
            player->money += 50; 
            board_classic.players[i].money -= 50;
        }
    }
    printf("You collected %d. \n", sum);

    return 0;
}

int holiday_fund_matures (PLAYER *player) {
    printf("Holiday fund matures 100$ \n");
    player->money += 50;
    return 0;
}

int income_tax_refund (PLAYER *player) {
    printf("Income tax refund 20$. \n");
    player->money += 20;
    return 0;
}

int birthday (PLAYER *player) {
    printf("It's your birthday you get 10$ from everybody. \n");
    int sum = 0; 
    for (int i = 0; i < board_classic.nb_players; i++) {
        if (board_classic.players[i].id != player->id && board_classic.players[i].bankrupt == 0) {
            sum += 10;
            player->money += 10;
            board_classic.players[i].money -= 10;
        }
    }
    printf("You collected %d. \n", sum);
    return 0;
}

int life_insurance_mature (PLAYER *player) {
    printf("Life insurance matures - You collected 100$. \n");
    player->money += 100;
    return 0;
}

int hospital_fees (PLAYER *player) {
    printf("Hospital fees - 100$. \n");
    player->money -= 100;
    return 0;
}

int school_fees (PLAYER *player) {
    printf("School fees - 50$. \n");
    player->money -= 50;
    return 0;
}

int consulty_fee (PLAYER *player) {
    printf("You won 25$ as consulty fee. \n");
    player->money += 25;
    return 0;
}

int street_repairs (PLAYER *player) {
    printf("Pay $40 per house and $115 per hotel you own. \n");

    int fees = 0;
    fees  = player->houses * 40;
    fees += player->hotels * 115;

    printf("Total cost: %d \n", fees);
    return 0;
}

int won_beauty_contest (PLAYER *player) {
    printf("You have won second prize in a beauty contest. You won 10$. \n");
    player->money += 10;
    return 0;
}

int inherit (PLAYER *player) {
    printf("You inherit +10$. \n");
    player->money += 10;
    return 0;
}

//typedef int (*cards) (PLAYER *player);

cards comm_chest [17] = { advance_to_go,
                          bank_error,
                          doctor_fee,
                          stock_sold,
                          get_out_of_jail,
                          
                          go_to_jail,
                          grand_opera_night,
                          holiday_fund_matures,
                          income_tax_refund,
                          birthday,
         
                          life_insurance_mature,
                          hospital_fees,
                          school_fees,
                          consulty_fee,
                          street_repairs,

                          won_beauty_contest,
                          inherit }; 
