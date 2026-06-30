#include "Game.h"
#include <string>
using namespace std;

Game::Game(int id, int p1, int p2, const string& name)
    : gameId(id), player1Id(p1), player2Id(p2), currentPlayer(1), gameName(name) {}

 string Game::getGameName() const
{
     return gameName;
}
int Game::getPlayer1Id() const
{
    return Player1Id;
}

int Game::getPlayer2Id() const
{
    return Player2Id;
}
bool Game::isPlayerTurn(int playerId) const
    {
    return (playerId == Player1Id && currentPlayer == 1) || (playerId == Player2Id && currentPlayer == 2);
    }

int Game::getOpponentId(int playerId) const
    {
        if (playerId == Player1Id) return Player2Id;
        if (playerId == Player2Id) return Player1Id;
        return -1;
    }
void Game::switchTurn()
    {
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }

int Game::getCurrentPlayer() const
    {
        return currentPlayer;
    }
