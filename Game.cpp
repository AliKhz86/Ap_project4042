#include "Game.h"
#include <string>
using namespace std;

Game::Game(int id, int p1, int p2, const string& name)
    : gameId(id), player1Id(p1), player2Id(p2), currentPlayer(1), gameName(name) {}

int Game::getGameId() const
{
    return gameId;
}
 string Game::getGameName() const
{
     return gameName;
}
int Game::getPlayer1Id() const
{
    return player1Id;
}

int Game::getPlayer2Id() const
{
    return player2Id;
}
bool Game::isPlayerTurn(int playerId) const
    {
    return (playerId == player1Id && currentPlayer == 1) || (playerId == player2Id && currentPlayer == 2);
    }

int Game::getOpponentId(int playerId) const
    {
        if (playerId == player1Id) return player2Id;
        if (playerId == player2Id) return player1Id;
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
