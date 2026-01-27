#include "GameManager.hpp"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <random>
#include <iostream>
#include <array>

void GameManager::incrementRoundCount(int n){
    this->roundCount+=n;
}

int GameManager::getRoundCount() const{
    return this->roundCount;
}

void GameManager::setRoundCount(int roundCount){
    this->roundCount = roundCount;
}


GameManager::GameManager(std::vector<Player*> &newPlayers): board(), roundCount(0) {
    // Save players in the class
    if(newPlayers.size()==4){
        for(int i=0; i<4; i++){
            this->players[i]=newPlayers[i];
        }
    }
    else{
        throw std::invalid_argument("4 players are needed");    
    }
}

GameManager::~GameManager() {

}

void GameManager::startGame(){
    // Try and Catch exceptions
    try {
        // Init everything
        choosePlayerOrder();
        setRoundCount(0);
        playRound();
    } catch (const std::exception& e) {
        std::cerr << "Game error: " << e.what() << std::endl;
    }
}

void GameManager::choosePlayerOrder(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(this->players.begin(), this->players.end(), gen);  // ✓ Fonctionne aussi avec std::vector
}

void GameManager::playRound(){
    if(!isLastRound()){
        incrementRoundCount(1);
        for(int i=0; i<4; i++){
            this->players[i]->placeCircle(*this);
            if (checkWinConditions()){
                this->players[i]->getColor(),
                std::cout<<"bravo!!"<<std::endl;
                // TODO: ending function
                return;  // Exit if someone wins
            }
        }
        playRound();  // Continue to next round
    }
}

bool GameManager::isLastRound() const{
    int round=getRoundCount();
    // Check the number of round
    if(round==nbRound){
        return true;
    }
    else if(round<nbRound){
        return false;
    }
    else{
    // Raise exception if the roundcount is invalid
    throw std::range_error("Number of round is out of allowed range");  
    }
}

bool GameManager::checkWinConditions() const{
    // TODO: Implementation needed
    return false;
}