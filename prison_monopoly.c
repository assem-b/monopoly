#include "monopoly.h"

void jail_player (PLAYER *player, const char *message) 
{
    player->position = 10;
    player->prison   =  5;
    player->dice.row =  0;
    printf("%s \n", message);
}

void send_jail (PLAYER *player, BOARD *board, SPACE *space)
{
    jail_player(player, "Bad luck !");
    player->prison -= 1;
    print_position(&board->spaces[player->position], board->players, player);
}

//Role dice if the player make a double, he is free
static int dice_prison (PLAYER *player)
{
    roll_dice(player);

    if (player->dice.row == 1) {
        printf("Well done you made a double ! You're free. \n");
        return 0;
    }

    player->prison -= 1;
    int chances = player->prison - 1;

    if (chances > 0)
        printf("%d chances to make a double to leave jail for free.\n", chances);
    else
        printf("Next time you have to pay 50$ to get out of jail. \n");

    return 1;
}

static int pay_prison (PLAYER *player, BOARD *board)
{
    draw_money(player, 50, board);

    if (player->bankrupt == 1) {
        printf("Prison ruined you. \n");
        return 1;
    }

    if (player->bankrupt == 0) printf("You paid 50$ to get out of jail. \n");

    roll_dice(player);

    return 0;
}

static int check_prison_counter (PLAYER *player, BOARD *board)
{
    int rc = 1;

    if (player->prison == 1)
        rc = pay_prison(player, board);

    else if (player->prison > 1 && player->prison < 5)
        rc = dice_prison(player);

    else if (player->prison == 5)
        player->prison -= 1;

    return rc;
}

static void reset_prison_counter (PLAYER *player)
{
    player->dice.row = 0;
    player->prison = 0;
    player->position += player->dice.sum;

    return;
}

int is_jailed (PLAYER *player, BOARD *board)
{
    int rc;
    rc = check_prison_counter(player, board);

    if (rc == 1) return 1;

    if (rc == 0) reset_prison_counter(player);

    return 0;
}

