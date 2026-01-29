#pragma once
#include "Player.hpp" 
#include <string>

// Déclarations anticipées pour éviter les inclusions circulaires
class Board; 
class GameManager;

struct move { 
    int x;          /**< Coordonnée X (colonne) */
    int y;          /**< Coordonnée Y (ligne) */
    CircleSize size; /**< Taille du cercle placé */
};

class PlayerBot : public Player
{
public:
    // Constructeur et Destructeur
    PlayerBot(CircleColor color, std::string name);
    ~PlayerBot();

    // Implémentation de la fonction virtuelle pure de la classe Player
    std::pair<int, int> placeCircle(GameManager &gameManager) override;

    // Fonction d'évaluation pour l'IA (récursivité)
    int evaluateRecursive(Board &simBoard, PlayerInventory_t simInv, int depth, GameManager &gm, CircleColor myColor);

};