#ifndef ّFANORONA_H
#define ّFANORONA_H

#include "Game.h"
#include <string>
#include "cell.h"
#include <vector>

class Fanorona : public Game
{

private:

    int previousRow = -1;

    int previousCol = -1;

    Cell board[5][9] ; //صقحه بازی

    int    player1count , player2count; //تعداد مهره هر بازیکن

    int lastFromRow, lastFromCol; // برای اخرین نقطه حضور

    int lastToRow, lastToCol;

    bool waitingAgainCapture ; //برای انتظار برای ادامه خوردندگی

    vector<Cell*> pendingCaptures;//لیست حرکات مجاز ادامه خورندگی

    bool canTwoWayCalim ; // برای تعیین اینکه میتوان دو طرف را خورد یا نه

    vector<Cell*> pieceForTwoWayCapture;//برای نگه داشتن مهره های ممکن برای  خورندگی دو طرفه


public:

    Fanorona(int Id , int IdP1, int IdP2 , string name);

    void initializeBoard(); // تنظیمات اولیه

    vector<Cell*> getvalidMoves(int r, int c); //تعیین مکان های ممکن برای رفتن

    vector<Cell*> getPossibleCaptures(int fromRow, int fromCol);//برای برگرداندن خانه های مجاز برای حرکت در ادامه خورندگی

    vector<Cell*> getPieceTwoWay();//برگرداندن خانه های مجاز برای حذف در دوطرفه

    int claimPiece(int fromRow, int fromCol,int toRow, int toCol, int dr, int dc, bool approach); //تابع خوردن مهره

    void claimPieceagain(int toRow, int toCol );//تابع بررسی خوردن دوباره مهره در ادامه خورندگی

    bool canMove(int n) const;//برای برزسی تمام شدن بازی

    bool getCanTwoWay();//برگرداندن متغیر بررسی خوردن دوطرفه

    bool getWaiting();//برگرداندن متغیر انتظار برای ادامه دادن به خوردن

    int getValue(int row ,int col) const; // برگرداندن ارزش هر خانه

    void selectCaptureType(int row, int col);//تابع برای  مدیریت خورندگی دو طرفه

    void startGame() override;


    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) override;


    void executeMove(int fromRow, int fromCol, int toRow, int toCol) override;


    string getGameState() const override;


    bool isGameOver() const override;


    int getWinner() const override;


    void saveGame() override;


    void resetGame() override;

    bool isPlayerPiece(int row, int col) const;

    vector<Cell*> getPieceTwo();

};

#endif // ّFANORONA_H
