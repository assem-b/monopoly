#include "monopoly.h"


const SET
    marron      = {.id = 0, 
                  .name="Marron",   
                  .price = 50, 
                  .max_properties = 2, 
                  .properties = { 1,  3 }
                 },

    bleu_ciel  = {.id = 1,
                  .name="Bleu ciel",
                  .price = 50, 
                  .max_properties = 3,
                  .properties = { 6,  8,  9 } 
                 },

    violet     = {.id = 4,
                  .name="Violet",   
                  .price = 100,
                  .max_properties = 3,
                  .properties = { 11, 13, 14 }
                 },

    orange     = {.id = 2,
                  .name="Orange",   
                  .price = 100,
                  .max_properties = 3,
                  .properties = { 16, 18, 19 }
                 },

    rouge      = {.id = 3,
                  .name="Rouge",
                  .price = 150, 
                  .max_properties = 3, 
                  .properties = { 21, 23, 24 }
                 },

    jaune      = {.id = 7,
                  .name="Jaune",
                  .price = 150,
                  .max_properties = 3,
                  .properties = { 26, 27, 29 }
                 },

    vert       = {.id = 5,
                  .name="Vert",
                  .price = 200,
                  .max_properties = 3,
                  .properties = { 31, 32, 34 }
                 },

    bleu       = {.id = 6,
                  .name="Bleu",
                  .price = 200,
                  .max_properties = 2,
                  .properties = { 37, 39 }
                 },

    railroad   = {.id = 8,
                  .name="RAILROADS", 
                  .max_properties = 4,
                  .properties = { 5, 15, 25, 35 }
                 },

    utilitie   = {.id = 9,
                  .name="UTILITIES", 
                  .max_properties = 2,
                  .properties = { 12, 28 }
                 };

const SPACE

    /* STREETS */  
    
    med_avenue = {.name = "Mediterranea, Avenue",
                  .price = 60,
                  .loyer = { 2, 10, 30, 90, 160, 250 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = marron
                },

    bal_avenue = {.name = "Baltic Avenue",
                  .price = 60,
                  .loyer = { 4, 20, 60, 180, 320, 450 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = marron
                 },

    ori_avenue = {.name = "Oriental Avenue",
                  .price = 100,
                  .loyer = { 6, 30, 90, 270, 400, 550 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = bleu_ciel
                 },

    ver_avenue = {.name = "Vermont Avenue",
                  .price = 100,
                  .loyer = { 6, 30, 90, 270, 400, 550 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = bleu_ciel
                 },
 
    con_avenue = {.name = "Connecticut Avenue",
                  .price = 120,
                  .loyer = { 8, 40, 100, 300, 450, 600 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = bleu_ciel
                },

    st_charles = {.name = "St.Charles Place",
                  .price = 140,
                  .loyer = { 10, 50, 150, 450, 625, 750 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = violet
                 },

    sta_avenue = {.name = "States Avenue",
                  .price = 140,
                  .loyer = { 10, 50, 150, 450, 625, 750 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = violet},

    vir_avenue = {.name = "Virginia Avenue",
                  .price = 160,
                  .loyer = { 12, 60, 180, 500, 700, 900 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = violet
                 },

    st_james   = {.name = "St.James Place",
                  .price = 180,
                  .loyer = { 14, 70, 200, 550, 750, 950 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = orange},

    ten_avenue = {.name = "Tennessee Avenue",
                  .price = 180,
                  .loyer = {14, 70, 200, 550, 750, 950},
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = orange
                 },
 
    new_avenue = {.name = "New York Avenue",
                  .price = 200,
                  .loyer = { 16, 80, 220, 600, 800, 1000 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = orange
                 },

    ken_avenue = {.name = "Kentucky Avenue",
                  .price = 220,
                  .loyer = { 18, 90, 250, 700, 875, 1050 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = rouge
                 },

    ind_avenue = {.name = "Indiana Avenue",
                  .price = 220,
                  .loyer = { 18, 90, 250, 700, 875, 1050 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = rouge
                 },

    ill_avenue = {.name = "Illinois Avenue",
                  .price = 240,
                  .loyer = { 20, 100, 300, 750, 925, 1100 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = rouge
                 },

    atl_avenue = {.name = "Atlantic Avenue",
                  .price = 260,
                  .loyer = { 22, 110, 330, 800, 975, 1150 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = jaune
                 },

    ven_avenue = {.name = "Ventnor Avenue",
                  .price = 260,
                  .loyer = { 22, 110, 330, 800, 975, 1150 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = jaune},

    mar_garden = {.name = "Marvin Gardens",
                  .price = 280,
                  .loyer = { 24, 120, 360, 850, 1025, 1200 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = jaune
                 },


    pac_avenue = {.name = "Pacific Avenue",
                  .price = 300,
                  .loyer = { 26, 130, 390, 900, 1100, 1275 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = vert
                 },
 
    nca_avenue = {.name = "North Carolina Avenue",
                  .price = 300,
                  .loyer = { 26, 130, 390, 900, 1100, 1275 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = vert
                 },
 
    pen_avenue = {.name = "Pennsylvania Avenue",
                  .price = 320,
                  .loyer = { 28, 150, 450, 1000, 1200, 1400 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0, 
                  .set = vert
                 },

    park_place = {.name = "Park Place",
                  .price = 350,
                  .loyer = { 50, 200, 600, 1400, 1700, 2000 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0, 
                  .set = bleu
                 },

    board_walk = {.name = "Board Walk",
                  .price = 400,
                  .loyer = { 50, 200, 600, 1400, 1700, 2000 },
                  .owner = -1,
                  .type = 0,
                  .houses = 0,
                  .mortgage = 0,
                  .set = bleu
                 },

    /* RAILROADS */

    reading_railroad      = {.name = "Reading Railroad",
                             .price = 200,
                             .loyer = { 25, 50, 100, 200 },
                             .type = 1,
                             .set = railroad,
                             .owner = -1},

    pennsylvania_railroad = {.name = "Pennsylvania Railroad",
                             .price = 200,
                             .loyer = { 25, 50, 100, 200 },
                             .type = 1,
                             .set = railroad,
                             .owner = -1
                            },

    bo_railroad           = {.name = "B & O railroad",
                             .price = 200,
                             .loyer = { 25, 50, 100, 200 },
                             .type = 1,
                             .set = railroad,
                             .owner = -1
                            },

    short_line            = {.name = "Short Line",
                             .price = 200,
                             .loyer = { 25, 50, 100, 200 },
                             .type = 1,
                             .set = railroad,
                             .owner = -1
                            },

    /* UTILITY */

    electric_company = {.name = "Electric Company",
                        .price = 150,
                        .type = 2,
                        .owner = -1,
                        .set = utilitie
                       },

    water_works      = {.name = "Water works",
                        .price = 150,
                        .type = 2,
                        .owner = -1,
                        .set = utilitie
                       },

    /* TAX */

    income_tax       = {.name = "Taxe sur le revenu",
                        .price = 200,
                        .type = 3
                       },

    luxury_tax       = {.name = "Taxe sur le luxe",
                        .price = 100,
                        .type = 3
                       },

    /* PULL A CARD SPACE */
    
    community_chest = {.name = "Community Chest",
                       .type = 4 },
 
    chance          = {.name = "Chance",
                       .type = 5 },

    /* MISCELLANOUS */    

    go              = {.name = "Go",
                       .type = 6 },

    prison          = {.name = "Prison",
                       .type = 7 },

    go_to_prison    = {.name = "Go To Prison",
                       .type = 8 },

    free_parking    = {.name = "Free Parking",
                       .type = 6 };


const BANK bank = { .houses = 32, .hotels = 12 };

BOARD board_classic = { .bank = bank,

                        .spaces = { go, 
                        med_avenue,
                        community_chest,
                        bal_avenue, 
                        income_tax,
                        reading_railroad, 
                      
                        ori_avenue,
                        chance,
                        ver_avenue, 
                        con_avenue,
                        prison, 

                        st_charles, 
                        electric_company,
                        sta_avenue,
                        vir_avenue,
                        pennsylvania_railroad,
                       
                        st_james,
                        community_chest,
                        ten_avenue,
                        new_avenue,
                        free_parking,
 
                        ken_avenue, 
                        chance,
                        ind_avenue,
                        ill_avenue,
                        bo_railroad,
 
                        atl_avenue,
                        ven_avenue,
                        water_works,
                        mar_garden,
                        go_to_prison,
 
                        pac_avenue,
                        nca_avenue,
                        community_chest,
                        pen_avenue,
                        short_line, 
                  
                        chance,
                        park_place,
                        luxury_tax,
                        board_walk}};

