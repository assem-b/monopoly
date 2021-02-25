#include "monopoly.h"


const SET
    marron     = {.id = 0, .name="Marron",    .prix = 50,  .max_properties = 2},
    bleu_ciel  = {.id = 1, .name="Bleu ciel", .prix = 50,  .max_properties = 3},
    orange     = {.id = 2, .name="Orange",    .prix = 100, .max_properties = 3},
    rouge      = {.id = 3, .name="Rouge",     .prix = 150, .max_properties = 3},
    violet     = {.id = 4, .name="Violet",    .prix = 100, .max_properties = 3},
    vert       = {.id = 5, .name="Vert",      .prix = 200, .max_properties = 3},
    bleu       = {.id = 6, .name="Bleu",      .prix = 200, .max_properties = 2},
    jaune      = {.id = 7, .name="Jaune",     .prix = 150, .max_properties = 3},
    railroad   = {.id = 8, .name="RAILROADS",  .max_properties = 4},
    utilitie   = {.id = 9, .name="UTILITIES",  .max_properties = 2};
    

const SPACE
    med_avenue = {.nom = "Mediterranea, Avenue", .prix = 60, .loyer = {2, 10, 30, 90, 160, 250}, .proprietaire = 0, .type = 0, .maisons = 0,  .set = marron},
    bal_avenue = {.nom = "Baltic Avenue", .prix = 60, .loyer = {4, 20, 60, 180, 320, 450}, .proprietaire = 0, .type = 0, .maisons = 0, .set = marron},

    ori_avenue = {.nom = "Oriental Avenue", .prix = 100, .loyer = {6, 30, 90, 270, 400, 550}, .proprietaire = 0, .type = 0, .maisons = 0, .set = bleu_ciel},
    ver_avenue = {.nom = "Vermont Avenue", .prix = 100, .loyer = {6, 30, 90, 270, 400, 550}, .proprietaire = 0, .type = 0, .maisons = 0, .set = bleu_ciel},
    con_avenue = {.nom = "Connecticut Avenue", .prix = 120, .loyer = {8, 40, 100, 300, 450, 600}, .proprietaire = 0, .type = 0, .maisons = 0, .set = bleu_ciel},

    st_charles = {.nom = "St.Charles Place", .prix = 140, .loyer = {10, 50, 150, 450, 625, 750}, .proprietaire = 0, .type = 0, .maisons = 0, .set = violet},
    sta_avenue = {.nom = "States Avenue", .prix = 140, .loyer = {10, 50, 150, 450, 625, 750}, .proprietaire = 0, .type = 0, .maisons = 0, .set = violet},
    vir_avenue = {.nom = "Virginia Avenue", .prix = 160, .loyer = {12, 60, 180, 500, 700, 900}, .proprietaire = 0, .type = 0, .maisons = 0, .set = violet},

    st_james   = {.nom = "St.James Place", .prix = 180, .loyer = {14, 70, 200, 550, 750, 950}, .proprietaire = 0, .type = 0, .maisons = 0, .set = orange},
    ten_avenue = {.nom = "Tennessee Avenue", .prix = 180, .loyer = {14, 70, 200, 550, 750, 950}, .proprietaire = 0, .type = 0, .maisons = 0, .set = orange},
    new_avenue = {.nom = "New York Avenue", .prix = 200, .loyer = {16, 80, 220, 600, 800, 1000}, .proprietaire = 0, .type = 0, .maisons = 0, .set = orange},

    ken_avenue = {.nom = "Kentucky Avenue", .prix = 220, .loyer = {18, 90, 250, 700, 875, 1050}, .proprietaire = 0, .type = 0, .maisons = 0, .set = rouge},
    ind_avenue = {.nom = "Indiana Avenue", .prix = 220, .loyer = {18, 90, 250, 700, 875, 1050}, .proprietaire = 0, .type = 0, .maisons = 0, .set = rouge},
    ill_avenue = {.nom = "Illinois Avenue", .prix = 240, .loyer = {20, 100, 300, 750, 925, 1100}, .proprietaire = 0, .type = 0, .maisons = 0, .set = rouge},

    atl_avenue = {.nom = "Atlantic Avenue", .prix = 260, .loyer = {22, 110, 330, 800, 975, 1150}, .proprietaire = 0, .type = 0, .maisons = 0, .set = jaune},
    ven_avenue = {.nom = "Ventnor Avenue", .prix = 260, .loyer = {22, 110, 330, 800, 975, 1150}, .proprietaire = 0, .type = 0, .maisons = 0, .set = jaune},
    mar_garden = {.nom = "Marvin Gardens", .prix = 280, .loyer = {24, 120, 360, 850, 1025, 1200}, .proprietaire = 0, .type = 0, .maisons = 0, .set = jaune},

    pac_avenue = {.nom = "Pacific Avenue", .prix = 300, .loyer = {26, 130, 390, 900, 1100, 1275}, .proprietaire = 0, .type = 0, .maisons = 0, .set = vert},
    nca_avenue = {.nom = "North Carolina Avenue", .prix = 300, .loyer = {26, 130, 390, 900, 1100, 1275}, .proprietaire = 0, .type = 0, .maisons = 0, .set = vert},
    pen_avenue = {.nom = "Pennsylvania Avenue", .prix = 320, .loyer = {28, 150, 450, 1000, 1200, 1400}, .proprietaire = 0, .type = 0, .maisons = 0,  .set = vert},

    park_place = {.nom = "Park Place", .prix = 350, .loyer = {50, 200, 600, 1400, 1700, 2000}, .proprietaire = 0, .type = 0, .maisons = 0, .set = bleu},
    board_walk = {.nom = "Board Walk", .prix = 400, .loyer = {50, 200, 600, 1400, 1700, 2000}, .proprietaire = 0, .type = 0, .maisons = 0, .set = bleu},

    reading_railroad      = {.nom = "Reading Railroad", .prix = 200, .loyer = {25, 50, 100, 200}, .type = 1, .set = railroad, .proprietaire = 0},
    pennsylvania_railroad = {.nom = "Pennsylvania Railroad", .prix = 200, .loyer = {25, 50, 100, 200}, .type = 1, .set = railroad, .proprietaire = 0},
    bo_railroad           = {.nom = "B & O railroad", .prix = 200, .loyer = {25, 50, 100, 200}, .type = 1, .set = railroad, .proprietaire = 0},
    short_line            = {.nom = "Short Line", .prix = 200, .loyer = {25, 50, 100, 200}, .type = 1, .set = railroad, .proprietaire = 0},

    electric_company = {.nom = "Electric Company", .prix = 150, .type = 2, .proprietaire = 0, .set = utilitie},
    water_works      = {.nom = "Water works",     .prix = 150, .type = 2, .proprietaire = 0, .set = utilitie},

    income_tax       = {.nom = "Taxe sur le revenu", .prix = 200, .type = 3},
    luxury_tax       = {.nom = "Taxe sur le luxe", .prix = 100, .type = 3},
    
    community_chest = {.nom = "Community Chest", .type = 4}, 
    chance          = {.nom = "Chance", .type = 5},
    
    go              = {.nom = "Go", .type = 6},
    prison          = {.nom = "Prison", .type = 7},
    go_to_prison    = {.nom = "Go To Prison", .type = 8},
    free_parking    = {.nom = "Free Parking", .type = 6};

SPACE plateau[40] = {go, med_avenue, community_chest, bal_avenue, income_tax,
                     reading_railroad, ori_avenue, chance, ver_avenue, con_avenue,
                     prison, st_charles, electric_company, sta_avenue, vir_avenue,
                     pennsylvania_railroad, st_james, community_chest, ten_avenue, new_avenue,
                     free_parking, ken_avenue, chance, ind_avenue, ill_avenue,
                     bo_railroad, atl_avenue, ven_avenue, water_works, mar_garden,
                     go_to_prison, pac_avenue, nca_avenue, community_chest, pen_avenue,
                     short_line, chance, park_place, luxury_tax, board_walk };
