#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
using namespace std;

class Game {
private:
    int gameId;
    int player1Id;
    int player2Id;
    int currentPlayer;      // 1 = بازیکن اول, 2 = بازیکن دوم
    string gameName;

public:

    Game(int id, int p1, int p2, const string& name);

    //  Destructor
    virtual ~Game() {}

    // virtual void function


    virtual void startGame() = 0;


    virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) = 0;


    virtual void executeMove(int fromRow, int fromCol, int toRow, int toCol) = 0;


    virtual string getGameState() const = 0;


    virtual bool isGameOver() const = 0;


    virtual int getWinner() const = 0;


    virtual void saveGame() = 0;


    virtual void resetGame() = 0;

   //normal functions
    int getCurrentPlayer() const;
    void switchTurn();

    int getGameId() const;
    string getGameName() const;
    int getPlayer1Id() const;
    int getPlayer2Id() const;
    bool isPlayerTurn(int playerId) const;
    int getOpponentId(int playerId) const;
};

#endif // GAME_H