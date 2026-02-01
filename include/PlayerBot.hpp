#pragma once

#include <string>
#include <vector>
#include "Player.hpp" 

// Déclarations anticipées
class Board; 
class GameManager;

/**
 * @struct move
 * @brief Représente un coup complet sur le plateau.
 */
struct move { 
    int x;           ///< Coordonnée X (colonne)
    int y;           ///< Coordonnée Y (ligne)
    CircleSize size; ///< Taille du cercle (SMALL, MEDIUM, LARGE)
};

/**
 * @class PlayerBot
 * @brief Joueur contrôlé par un BOT utilisant des simulations et une analyse de danger.
 */
class PlayerBot : public Player
{
public:
    /** @name Cycle de vie */
    ///@{
    PlayerBot(CircleColor color, std::string name);
    virtual ~PlayerBot();
    ///@}

    /** @name Action de jeu */
    ///@{
    /**
     * @brief Analyse le plateau et choisit le meilleur emplacement pour un cercle.
     * @param gameManager Référence vers le gestionnaire de partie pour les règles.
     * @return std::pair<int, int> Les coordonnées (x, y) du coup choisi.
     */
    std::pair<int, int> placeCircle(GameManager &gameManager) override;
    ///@}

    /** @name Gestion de l'inventaire */
    ///@{
    /** @brief Met à jour l'inventaire complet du bot. */
    void setInventory(PlayerInventory_t newInv);

    /** @brief Retire une pièce spécifique de l'inventaire après un placement. */
    void removeCircle(CircleSize size);
    ///@}

    /** @name Logique BOT CLEVER */
    ///@{
    /**
     * @brief Évalue récursivement la qualité d'un plateau par simulation.
     * @param simBoard Copie du plateau pour la simulation.
     * @param simInv Copie de l'inventaire simulé.
     * @param depth Profondeur de recherche restante.
     * @param gm Référence pour vérifier les conditions de victoire.
     * @param myColor Couleur du bot pour le calcul du score.
     * @return int Score d'évaluation du plateau (plus il est élevé, mieux c'est).
     */
    int evaluateRecursive(Board &simBoard, PlayerInventory_t simInv, int depth, GameManager &gm, CircleColor myColor);
    ///@}
};