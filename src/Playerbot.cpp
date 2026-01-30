#include "PlayerBot.hpp"
#include "Board.hpp"
#include "GameManager.hpp"
#include "Frame.hpp"
#include <vector>
#include <algorithm>

const std::vector<CircleSize> SIZES = {SMALL, MEDIUM, LARGE};

PlayerBot::PlayerBot(CircleColor color, std::string name)
    : Player(color, name)
{
}

PlayerBot::~PlayerBot() {}

// Fonction utilitaire pour vérifier l'inventaire
bool hasPiece(PlayerInventory_t inv, CircleSize s)
{
    if (s == SMALL)
        return inv.nbSmallCircles > 0;
    if (s == MEDIUM)
        return inv.nbMediumCircles > 0;
    if (s == LARGE)
        return inv.nbLargeCircles > 0;
    return false;
}

// Utilitaire pour retirer une pièce d'un inventaire simulé
PlayerInventory_t subPiece(PlayerInventory_t inv, CircleSize s)
{
    if (s == SMALL)
        inv.nbSmallCircles--;
    else if (s == MEDIUM)
        inv.nbMediumCircles--;
    else if (s == LARGE)
        inv.nbLargeCircles--;
    return inv;
}

void PlayerBot::setInventory(PlayerInventory_t newInv)
{
    this->inventory = newInv;
}

void PlayerBot::removeCircle(CircleSize s)
{
    PlayerInventory_t myInv = this->getInventory();
    if (s == SMALL)
        myInv.nbSmallCircles--;
    else if (s == MEDIUM)
        myInv.nbMediumCircles--;
    else if (s == LARGE)
        myInv.nbLargeCircles--;
    this->setInventory(myInv);
}

// Fonction d'évaluation récursive sur des copies
int PlayerBot::evaluateRecursive(Board &simBoard, PlayerInventory_t simInv, int depth, GameManager &gm, CircleColor myColor)
{
    int maxScore = 0;

    // Condition d'arrêt : on a atteint la profondeur max
    if (depth == 0)
        return 0;

    // On parcourt toutes les cases pour simuler NOTRE prochain coup
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (CircleSize s : SIZES)
            {
                // Si on a la pièce et que la case est libre sur la simulation
                if (hasPiece(simInv, s) && (simBoard.getFrame(x, y).getCircle(s) == nullptr))
                {
                    // Si ce coup nous fait gagner sur la simulation
                    if (gm.checkWinConditions(x, y, myColor, &simBoard))
                    {
                        // On donne un gros score, plus élevé si la victoire est proche
                        return 100 * depth;
                    }

                    // Sinon, on simule la pose et on descend plus profondément
                    if (depth > 1)
                    {
                        simBoard.getFrame(x, y).tryToPlace(myColor, s);

                        // Appel récursif avec l'inventaire mis à jour
                        int score = evaluateRecursive(simBoard, subPiece(simInv, s), depth - 1, gm, myColor);

                        // On nettoie la simulation
                        simBoard.getFrame(x, y).removeCircle(myColor, s);

                        maxScore = std::max(maxScore, score);
                    }
                }
            }
        }
    }

    return maxScore;
}

std::pair<int, int> PlayerBot::placeCircle(GameManager &gameManager)
{
    CircleColor color = this->getColor();
    PlayerInventory_t myInv = this->getInventory();

    // 1. VICTOIRYYYYYYYY EN 1 COUP

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (CircleSize s : SIZES)
            {
                if (hasPiece(myInv, s) && gameManager.getBoard().getFrame(x, y).getCircle(s) == nullptr)
                {
                    // POSE VIRTUELLE
                    if (gameManager.getBoard().getFrame(x, y).tryToPlace(color, s))
                    {
                        // On vérifie les conditions
                        bool iWin = gameManager.checkWinConditions(x, y, color, &gameManager.getBoard());

                        // NETTOYAGE
                        gameManager.getBoard().getFrame(x, y).removeCircle(color, s);

                        if (iWin)
                        {
                            // Si ça gagne, on pose pour de vrai et on valide
                            if (gameManager.getBoard().getFrame(x, y).tryToPlace(color, s))
                            {
                                removeCircle(s);
                                return {x, y};
                            }
                        }
                    }
                }
            }
        }
    }

    // 2. DANGER IMMÉDIAT
    auto players = gameManager.getPlayers();

    for (auto &opponent : players)
    {
        if (opponent->getColor() == color)
            continue;

        PlayerInventory_t oppInv = opponent->getInventory();

        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                for (CircleSize s : SIZES)
                {
                    // Si l'adversaire a la pièce et que l'emplacement est libre
                    if (hasPiece(oppInv, s) && gameManager.getBoard().getFrame(x, y).getCircle(s) == nullptr)
                    {

                        // POSE VIRTUELLE DE L'ADVERSAIRE
                        if (gameManager.getBoard().getFrame(x, y).tryToPlace(opponent->getColor(), s))
                        {

                            // On verif si il peut gagner comme ca
                            bool opponentWouldWin = gameManager.checkWinConditions(x, y, opponent->getColor(), &gameManager.getBoard());

                            // ON RETIRE TOUJOURS LA PIÈCE VIRTUELLE
                            gameManager.getBoard().getFrame(x, y).removeCircle(opponent->getColor(), s);

                            if (opponentWouldWin)
                            {

                                // On cherche n'importe laquelle de nos pièces pour occuper cette case (même taille ou autre)
                                for (CircleSize myS : SIZES)
                                {
                                    if (hasPiece(myInv, myS) && gameManager.getBoard().getFrame(x, y).getCircle(myS) == nullptr)
                                    {
                                        if (gameManager.getBoard().getFrame(x, y).tryToPlace(color, myS))
                                        {
                                            removeCircle(myS);
                                            return {x, y}; // Blocage effectué
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 3. ANALYSE PROFONDE SUR COPIE DU BOARD (RECURSIVE)
    int bestScore = -10000;
    move bestMove = {-1, -1, SMALL};

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (CircleSize sType : SIZES)
            {
                if (hasPiece(myInv, sType) && gameManager.getBoard().getFrame(x, y).getCircle(sType) == nullptr)
                {
                    // COPIE DE LA BOARD POUR SIMULER
                    Board boardCopy = Board(gameManager.getBoard());

                    // SIMULATION DE NOTRE PREMIER COUP
                    boardCopy.getFrame(x, y).tryToPlace(color, sType);

                    // CALCUL SCORE AVEC RÉCURSION ( profondeur 3 pour le TP)
                    int currentScore = evaluateRecursive(boardCopy, subPiece(myInv, sType), 3, gameManager, color);

                    if (currentScore > bestScore)
                    {
                        bestScore = currentScore;
                        bestMove = {x, y, sType};
                    }
                }
            }
        }
    }

    // Si il existe un case ou placer un cercle est strategique
    if (bestMove.x != -1 && bestScore > 0)
    {
        if (gameManager.getBoard().getFrame(bestMove.x, bestMove.y).tryToPlace(color, bestMove.size))
        {
            removeCircle(bestMove.size);
            return {bestMove.x, bestMove.y};
        }
    }

    // Sinon on pose 'EL CLASSICO'

    // On check le centre d'abord car comme au morpion ca semble plus strategique
    if (hasPiece(myInv, MEDIUM) && gameManager.getBoard().getFrame(1, 1).getCircle(MEDIUM) == nullptr)
    {
        if (gameManager.getBoard().getFrame(1, 1).tryToPlace(color, MEDIUM))
        {
            removeCircle(MEDIUM);
            return {1, 1};
        }
    }

    // Premier coup legal qui reste
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            for (CircleSize s : SIZES)
            {
                if (hasPiece(myInv, s) && gameManager.getBoard().getFrame(x, y).getCircle(s) == nullptr)
                {
                    if (gameManager.getBoard().getFrame(x, y).tryToPlace(color, s))
                    {
                        removeCircle(s);
                        return {x, y};
                    }
                }
            }
        }
    }

    return {-1, -1};
}