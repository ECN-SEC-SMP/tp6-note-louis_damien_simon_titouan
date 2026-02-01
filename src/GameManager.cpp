#include "GameManager.hpp"
#include "DisplayUtils.hpp"

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

    // Check if game mode is TwoPlayer
    if (this->players.at(0)->getName() == this->players.at(2)->getName())
    {
        if (gen() % 2) // Change on pair numbers
        {
            auto playerCopy = this->players;
            for (size_t i = 0; i < this->players.size(); i++)
            {
                int index = (i + 1) % this->players.size();
                this->players[i] = playerCopy.at(index);
            }
        }
        return;
    }

    // Else randomise players orders
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

        if (checkWinConditions(position.first, position.second, this->players[i]->getColor()))
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

bool GameManager::checkWinConditions([[maybe_unused]] const int x, [[maybe_unused]] const int y, [[maybe_unused]] const CircleColor targetColor) const
{
    // TODO: Implementation needed
    return false;
}