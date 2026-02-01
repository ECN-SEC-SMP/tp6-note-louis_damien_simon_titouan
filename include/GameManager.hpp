#pragma once

#include <random>    
#include <algorithm> 
#include <iostream>  
#include <vector>
#include <string>
#include <array>
#include "Board.hpp"

class Player; 
enum CircleColor; 

/** @brief Nombre maximum de tours avant la fin de partie (9 cases * 3 tailles) */
#define NBROUND 27

/**
 * @class GameManager
 * @brief Gère l'orchestration de la partie, l'ordre des joueurs et les conditions de victoire.
 */
class GameManager
{
protected:
    Board board;                       ///< Le plateau de jeu
    std::array<Player *, 4> players;   ///< Liste des 4 joueurs
    int roundCount;                    ///< Compteur de tours actuel
    Player *winnerPlayer;              ///< Pointeur vers le vainqueur (nullptr si aucun)

public:
    /** @name Cycle de vie */
    ///@{
    /**
     * @brief Initialise une nouvelle partie avec 4 joueurs.
     * @param newPlayers Tableau contenant les pointeurs vers les joueurs.
     */
    GameManager(std::array<Player *, 4> &newPlayers);
    
    /**
     * @brief Libère la mémoire des joueurs et nettoie le manager.
     */
    ~GameManager();
    ///@}

    /** @name Orchestration du jeu */
    ///@{
    /** @brief Initialise l'ordre et lance la boucle de jeu principale. */
    void manageGame();
    
    /** @brief Configure le début de partie (mélange des joueurs, reset du compteur). */
    void startGame();
    
    /** @brief Gère la boucle des rounds jusqu'à la victoire ou la fin du plateau. */
    void manageRounds();
    
    /** @brief Exécute un tour complet (chaque joueur joue une fois). @return true si victoire. */
    bool playRound();
    
    /** @brief Mélange aléatoirement l'ordre des joueurs. */
    void choosePlayerOrder();
    ///@}

    /** @name Vérification des conditions de victoire */
    ///@{
    /** @brief Vérifie les 3 conditions de victoire pour une couleur donnée. */
    bool checkWinConditions(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    
    /** @brief Condition 1 : Tailles croissantes ou décroissantes alignées. */
    bool checkWinCondition1(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    
    /** @brief Condition 2 : Trois cercles de même taille alignés. */
    bool checkWinCondition2(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    
    /** @brief Condition 3 : Trois cercles concentriques sur la même case. */
    bool checkWinCondition3(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const;
    ///@}

    /** @name Accesseurs et Utilitaires */
    ///@{
    /** @return true si le nombre max de rounds est atteint. */
    bool isLastRound() const;
    
    /** @brief Génère un affichage texte du plateau et des inventaires. */
    std::string renderBoard();

    Board &getBoard();
    
    int getRoundCount() const;
    void setRoundCount(int roundCount);
    void incrementRoundCount(int n);
    
    Player *getWinner();
    void setWinner(Player *winner);
    
    std::array<Player *, 4> getPlayers() const;
    ///@}
};