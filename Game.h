#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;
class Game
{
private:
    int GameId;
    int Player1Id;
    int Player2Id;
    int currentPlayer;      // 1 or 2 کدام بازیکن در حال بازی است
    string gameName;

public:

    Game(int id, int p1, int p2, const string& name);


    virtual ~Game() {}

    virtual void startGame() = 0;


    virtual bool isValidMove(int from, int to) = 0;


    virtual void executeMove(int from, int to) = 0;


    virtual bool isGameOver() const = 0;


    virtual int getWinner() const = 0;


    virtual string getGameState() const = 0;

    virtual void saveGame()=0;

    virtual void resetGame() = 0;

    int getCurrentPlayer() const;

    void switchTurn();

    int getGameId() const { return gameId; }


    string getGameName() const ;

    int getPlayer1Id() const;

    int getPlayer2Id() const ;

    bool isPlayerTurn(int playerId) const ;


    // دریافت  id بازیکن مقابل
    int getOpponentId(int playerId) const ;



}


#endif // GAME_H
