#include <gtest/gtest.h>
#include <array>
#include "GameManager.hpp"
#include "PlayerBot.hpp"
#include "Board.hpp"

class BotFullTest : public ::testing::Test {
protected:
    PlayerBot* botOrange;
    PlayerBot* botBlue;
    PlayerBot* botGreen;
    PlayerBot* botRed;
    GameManager* gm;

    void SetUp() override {
        botOrange = new PlayerBot(ORANGE, "Orange");
        botBlue   = new PlayerBot(BLUE,   "Blue");
        botGreen  = new PlayerBot(GREEN,  "Green");
        botRed    = new PlayerBot(RED,    "Red");
        std::array<Player*, 4> players = {botOrange, botBlue, botGreen, botRed};
        gm = new GameManager(players);
        // On donne toujours un inventaire plein au bot testé (Red)
        botRed->setInventory({3, 3, 3});
    }

    void TearDown() override {
        delete gm;
    }

    // Utilitaire pour nettoyer le board entre deux phases d'un même test
    void clearBoard() {
        for(int x=0; x<3; x++)
            for(int y=0; y<3; y++)
                for(auto s : {SMALL, MEDIUM, LARGE})
                    gm->getBoard().getFrame(x,y).removeCircle(ORANGE, s); // Nettoie toutes couleurs
    }
};

// CATEGORIE 1 : LES DIAGONALES

TEST_F(BotFullTest, BlocksDiagonalMain) {
    Board& b = gm->getBoard();
    // Menace Blue en diagonale (0,0) et (1,1) -> Cible (2,2)
    b.getFrame(0, 0).tryToPlace(BLUE, SMALL);
    b.getFrame(1, 1).tryToPlace(BLUE, MEDIUM);
    
    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 2) << "Echec: Le bot n'a pas bloque la diagonale principale (Condition 1)";
}

TEST_F(BotFullTest, BlocksDiagonalInverse) {
    Board& b = gm->getBoard();
    // Menace Green en diagonale (0,2) et (1,1) -> Cible (2,0)
    b.getFrame(0, 2).tryToPlace(GREEN, LARGE);
    b.getFrame(1, 1).tryToPlace(GREEN, MEDIUM);
    
    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 0) << "Echec: Le bot n'a pas bloque la diagonale inverse (Condition 1)";
}

// L'EMBOÎTEMENT 

TEST_F(BotFullTest, BlocksDangerOnOccupiedFrame) {
    Board& b = gm->getBoard();
    // Blue menace en (2,0), (2,1) -> Cible (2,2) avec un LARGE
    b.getFrame(2, 0).tryToPlace(BLUE, LARGE);
    b.getFrame(2, 1).tryToPlace(BLUE, LARGE);

    // PIÈGE : Le bot a déjà une petite pièce à lui en (2,2)
    b.getFrame(2, 2).tryToPlace(RED, SMALL);

    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 2) << "Echec: Le bot refuse de bloquer car il a deja une petite piece sur la case cible";
}

TEST_F(BotFullTest, BlocksEvenWithMixedColorsOnFrame) {
    Board& b = gm->getBoard();
    // L'adversaire Bleu menace de gagner en (1,1) avec un LARGE.
    b.getFrame(0,1).tryToPlace(BLUE, LARGE);
    b.getFrame(2,1).tryToPlace(BLUE, LARGE);
    
    // MAIS en (1,1), il y a DEJA un SMALL Orange.
    b.getFrame(1, 1).tryToPlace(ORANGE, SMALL);

    botRed->setInventory({1, 1, 1});
    auto move = botRed->placeCircle(*gm);

    // Le bot DOIT jouer en (1,1) malgré la présence du Orange
    EXPECT_EQ(move.first, 1);
    EXPECT_EQ(move.second, 1);
}

TEST_F(BotFullTest, BlocksConcentricEvenIfOtherColorsPresent) {
    Board& b = gm->getBoard();
    // Orange menace en (0,0) : possède déjà SMALL et LARGE. Cible (0,0) avec MEDIUM.
    b.getFrame(0, 0).tryToPlace(ORANGE, SMALL);
    b.getFrame(0, 0).tryToPlace(ORANGE, LARGE);
    
    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 0);
    EXPECT_EQ(move.second, 0) << "Echec: Le bot n'a pas bloque la victoire concentrique (Condition 3)";
}


TEST_F(BotFullTest, BlocksDescendingAlignment) {
    Board& b = gm->getBoard();
    // Blue en (0,0) LARGE, (1,0) MEDIUM -> Cible (2,0) SMALL
    b.getFrame(0, 0).tryToPlace(BLUE, LARGE);
    b.getFrame(1, 0).tryToPlace(BLUE, MEDIUM);
    
    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 0);
}

// INVENTAIRE

TEST_F(BotFullTest, PriorityToWinOverBlock) {
    Board& b = gm->getBoard();
    // 1. Menace Orange imminente en (0,0)
    b.getFrame(0, 1).tryToPlace(ORANGE, MEDIUM);
    b.getFrame(0, 2).tryToPlace(ORANGE, MEDIUM);
    
    // 2. MAIS le bot peut gagner en (2,2)
    b.getFrame(2, 0).tryToPlace(RED, SMALL);
    b.getFrame(2, 1).tryToPlace(RED, SMALL);

    auto move = botRed->placeCircle(*gm);
    EXPECT_EQ(move.first, 2);
    EXPECT_EQ(move.second, 2) << "Echec: Le bot devrait GAGNER plutot que de BLOQUER";
}