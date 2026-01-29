#include "GameManager.hpp"
#include "DisplayUtils.hpp"

const std::vector<CircleSize> SIZES = {SMALL, MEDIUM, LARGE};

void GameManager::incrementRoundCount(int n)
{
    this->roundCount += n;
}

int GameManager::getRoundCount() const
{
    return this->roundCount;
}

void GameManager::setRoundCount(int roundCount)
{
    this->roundCount = roundCount;
}


std::array<Player *, 4> GameManager::getPlayers() const {
    return this->players;
}

GameManager::GameManager(std::array<Player *, 4> &newPlayers)
    : board(), roundCount(0)
{
    // Save players in the class
    if (newPlayers.size() == 4)
    {
        for (int i = 0; i < 4; i++)
        {
            this->players[i] = newPlayers[i];
        }
    }
    else
    {
        throw std::invalid_argument("4 players are needed");
    }
}

GameManager::~GameManager()
{

    // Free memory
    for (int i = 0; i < 4; i++)
    {
        delete this->players[i];
        this->players[i] = nullptr;
    }
}
void GameManager::manageGame()
{
    // Try and Catch exceptions
    try
    {
        startGame();
        manageRounds();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Game error: " << e.what() << std::endl;
    }
}
void GameManager::startGame()
{
    // Init everything
    choosePlayerOrder();
    setRoundCount(0);
    manageRounds();
}

Board &GameManager::getBoard()
{
    return this->board;
}

Player *GameManager::getWinner()
{
    return this->winnerPlayer;
}

void GameManager::choosePlayerOrder()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    // Randomise players orders
    std::shuffle(this->players.begin(), this->players.end(), gen);
}

std::string GameManager::renderBoard()
{
    std::vector<Player *> vplayers;
    for (auto &&p : this->players)
    {
        vplayers.push_back(p);
    }
    return Render::board(this->board) + "\n\n" + Render::playersInventory(vplayers);
}

bool GameManager::playRound()
{
    // Play one round
    for (int i = 0; i < 4; i++)
    {
        std::pair<int, int> position = this->players[i]->placeCircle(*this);

        if (checkWinConditions(position.first, position.second, this->players[i]->getColor(),&(this->board)))
        {
            std::cout << "bravo!!" << std::endl;
            setWinner(this->players[i]);
            return true;
        }
    }
    return false;
}

void GameManager::manageRounds()
{
    bool playerWin = false;

    // Exit  if there is a winner or all round has been played
    while (isLastRound() == false && playerWin == false)
    {
        incrementRoundCount(1);
        playerWin = playRound();
    }
    std::cout << "Game over" << std::endl;
}

bool GameManager::isLastRound() const
{
    int round = getRoundCount();
    // Check the number of round
    if (round == NBROUND)
    {
        return true;
    }
    else if (round < NBROUND)
    {
        return false;
    }
    else
    {
        // Raise exception if the roundcount is invalid
        throw std::range_error("Number of round is out of allowed range");
    }
}
void GameManager::setWinner(Player *winner)
{
    this->winnerPlayer = winner;
}


// Check Win
bool GameManager::checkWinConditions(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const
{
    // On propage le pointeur sourceBoard aux trois sous-conditions
    return (checkWinCondition1(x, y, targetColor, sourceBoard) || 
            checkWinCondition2(x, y, targetColor, sourceBoard) || 
            checkWinCondition3(x, y, targetColor, sourceBoard));
}


// Condition
bool GameManager::checkWinCondition1(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const
{
    // Si sourceBoard est fourni, on l'utilise, sinon on utilise le plateau interne
    const Board& b = (sourceBoard != nullptr) ? *sourceBoard : this->board;

    // on verifie sur les colonnes

    // Ascendant
    if (b.getFrame(x, 0).getCircle(SMALL) != nullptr &&
        b.getFrame(x, 1).getCircle(MEDIUM) != nullptr &&
        b.getFrame(x, 2).getCircle(LARGE) != nullptr)
    {
        if (b.getFrame(x, 0).getCircle(SMALL)->getColor() == targetColor &&
            b.getFrame(x, 1).getCircle(MEDIUM)->getColor() == targetColor &&
            b.getFrame(x, 2).getCircle(LARGE)->getColor() == targetColor)
        {
            return true;
        }
    }

    // Descendant
    if (b.getFrame(x, 0).getCircle(LARGE) != nullptr &&
        b.getFrame(x, 1).getCircle(MEDIUM) != nullptr &&
        b.getFrame(x, 2).getCircle(SMALL) != nullptr)
    {
        if (b.getFrame(x, 0).getCircle(LARGE)->getColor() == targetColor &&
            b.getFrame(x, 1).getCircle(MEDIUM)->getColor() == targetColor &&
            b.getFrame(x, 2).getCircle(SMALL)->getColor() == targetColor)
        {
            return true;
        }
    }

    // on verifie sur les lignes

    // Ascendant
    if (b.getFrame(0, y).getCircle(SMALL) != nullptr &&
        b.getFrame(1, y).getCircle(MEDIUM) != nullptr &&
        b.getFrame(2, y).getCircle(LARGE) != nullptr)
    {
        if (b.getFrame(0, y).getCircle(SMALL)->getColor() == targetColor &&
            b.getFrame(1, y).getCircle(MEDIUM)->getColor() == targetColor &&
            b.getFrame(2, y).getCircle(LARGE)->getColor() == targetColor)
        {
            return true;
        }
    }

    // Descendant
    if (b.getFrame(0, y).getCircle(LARGE) != nullptr &&
        b.getFrame(1, y).getCircle(MEDIUM) != nullptr &&
        b.getFrame(2, y).getCircle(SMALL) != nullptr)
    {
        if (b.getFrame(0, y).getCircle(LARGE)->getColor() == targetColor &&
            b.getFrame(1, y).getCircle(MEDIUM)->getColor() == targetColor &&
            b.getFrame(2, y).getCircle(SMALL)->getColor() == targetColor)
        {
            return true;
        }
    }

    if (x == y)
    { // on est sur la diagonale "/"
        // Ascendant
        if (b.getFrame(0, 0).getCircle(SMALL) != nullptr &&
            b.getFrame(1, 1).getCircle(MEDIUM) != nullptr &&
            b.getFrame(2, 2).getCircle(LARGE) != nullptr)
        {
            if (b.getFrame(0, 0).getCircle(SMALL)->getColor() == targetColor &&
                b.getFrame(1, 1).getCircle(MEDIUM)->getColor() == targetColor &&
                b.getFrame(2, 2).getCircle(LARGE)->getColor() == targetColor)
            {
                return true;
            }
        }

        // Descendant
        if (b.getFrame(0, 0).getCircle(LARGE) != nullptr &&
            b.getFrame(1, 1).getCircle(MEDIUM) != nullptr &&
            b.getFrame(2, 2).getCircle(SMALL) != nullptr)
        {
            if (b.getFrame(0, 0).getCircle(LARGE)->getColor() == targetColor &&
                b.getFrame(1, 1).getCircle(MEDIUM)->getColor() == targetColor &&
                b.getFrame(2, 2).getCircle(SMALL)->getColor() == targetColor)
            {
                return true;
            }
        }
    }
    if ((x + y) == 2)
    { // on est sur la diagonale "\"
        // Ascendant
        if (b.getFrame(0, 2).getCircle(SMALL) != nullptr &&
            b.getFrame(1, 1).getCircle(MEDIUM) != nullptr &&
            b.getFrame(2, 0).getCircle(LARGE) != nullptr)
        {
            if (b.getFrame(0, 2).getCircle(SMALL)->getColor() == targetColor &&
                b.getFrame(1, 1).getCircle(MEDIUM)->getColor() == targetColor &&
                b.getFrame(2, 0).getCircle(LARGE)->getColor() == targetColor)
            {
                return true;
            }
        }

        // Descendant
        if (b.getFrame(0, 2).getCircle(LARGE) != nullptr &&
            b.getFrame(1, 1).getCircle(MEDIUM) != nullptr &&
            b.getFrame(2, 0).getCircle(SMALL) != nullptr)
        {
            if (b.getFrame(0, 2).getCircle(LARGE)->getColor() == targetColor &&
                b.getFrame(1, 1).getCircle(MEDIUM)->getColor() == targetColor &&
                b.getFrame(2, 0).getCircle(SMALL)->getColor() == targetColor)
            {
                return true;
            }
        }
    }

    return false;
}


bool GameManager::checkWinCondition2(const int x, const int y, CircleColor targetColor, const Board* sourceBoard) const
{
    // Si sourceBoard est fourni, on l'utilise, sinon on utilise le plateau interne
    const Board& b = (sourceBoard != nullptr) ? *sourceBoard : this->board;

    for (CircleSize size : SIZES)
    {
        // on verifie sur les colonnes

        if (b.getFrame(x, 0).getCircle(size) != nullptr &&
            b.getFrame(x, 1).getCircle(size) != nullptr &&
            b.getFrame(x, 2).getCircle(size) != nullptr)
        {
            if (b.getFrame(x, 0).getCircle(size)->getColor() == targetColor &&
                b.getFrame(x, 1).getCircle(size)->getColor() == targetColor &&
                b.getFrame(x, 2).getCircle(size)->getColor() == targetColor)
            {
                return true;
            }
        }

        // on verifie sur les lignes

        if (b.getFrame(0, y).getCircle(size) != nullptr &&
            b.getFrame(1, y).getCircle(size) != nullptr &&
            b.getFrame(2, y).getCircle(size) != nullptr)
        {
            if (b.getFrame(0, y).getCircle(size)->getColor() == targetColor &&
                b.getFrame(1, y).getCircle(size)->getColor() == targetColor &&
                b.getFrame(2, y).getCircle(size)->getColor() == targetColor)
            {
                return true;
            }
        }

        if (x == y)
        { // on est sur la diagonale "/"

            if (b.getFrame(0, 0).getCircle(size) != nullptr &&
                b.getFrame(1, 1).getCircle(size) != nullptr &&
                b.getFrame(2, 2).getCircle(size) != nullptr)
            {
                if (b.getFrame(0, 0).getCircle(size)->getColor() == targetColor &&
                    b.getFrame(1, 1).getCircle(size)->getColor() == targetColor &&
                    b.getFrame(2, 2).getCircle(size)->getColor() == targetColor)
                {
                    return true;
                }
            }
        }

        else if ((x + y) == 2)
        { // on est sur la diagonale "\"
            if (b.getFrame(0, 2).getCircle(size) != nullptr &&
                b.getFrame(1, 1).getCircle(size) != nullptr &&
                b.getFrame(2, 0).getCircle(size) != nullptr)
            {
                if (b.getFrame(0, 2).getCircle(size)->getColor() == targetColor &&
                    b.getFrame(1, 1).getCircle(size)->getColor() == targetColor &&
                    b.getFrame(2, 0).getCircle(size)->getColor() == targetColor)
                {
                    return true;
                }
            }
        }
    }
    return false;
}


bool GameManager::checkWinCondition3(const int x, const int y, const CircleColor targetColor, const Board* sourceBoard) const
{
    const Board& b = (sourceBoard != nullptr) ? *sourceBoard : this->board;

    Circle *small = b.getFrame(x, y).getCircle(SMALL);
    Circle *medium = b.getFrame(x, y).getCircle(MEDIUM);
    Circle *large = b.getFrame(x, y).getCircle(LARGE);

    if (small == nullptr || medium == nullptr || large == nullptr)
    {
        return false;
    }

}

