#include "Fanorona.h"

Fanorona::Fanorona(int Id , int IdP1, int IdP2 , string name)
    : Game(Id, IdP1, IdP2, "Fanorona"),player1count(22),player2count(22)
{
    waitingAgainCapture = false;

    canTwoWayCalim = false;

    initializeBoard();
}

void Fanorona:: startGame()
{
    while (getCurrentPlayer() != 1)
    {
        switchTurn();
    }
    resetGame();
}

void Fanorona::resetGame()
{
    waitingAgainCapture = false;

    player1count=22;

    player2count=22;

    canTwoWayCalim = false;

    initializeBoard();
}

void Fanorona::initializeBoard()
{
    for(int  i =0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            board[i][j].setRow(i);
            board[i][j].setCol(j);
        }
    }

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {
            board[i][j].clearNeighbors();
        }

    }
    //set value
    for(int i =0;i<2;i++)
    {
        for(int j =0;j<9;j++)
        {
            board[i][j].setValue(2);
        }
    }
    for(int i =3;i<5;i++)
    {
        for(int j =0;j<9;j++)
        {
            board[i][j].setValue(1);
        }
    }
    board[2][0].setValue(1);
    board[2][2].setValue(1);
    board[2][5].setValue(1);
    board[2][7].setValue(1);

    board[2][4].setValue(0);

    board[2][1].setValue(2);
    board[2][3].setValue(2);
    board[2][6].setValue(2);
    board[2][8].setValue(2);

    //=============================================================
    //set neighbors

    //set board[0][0]
    board[0][0].addNeighbors(&board[0][1]);
    board[0][0].addNeighbors(&board[1][1]);
    board[0][0].addNeighbors(&board[1][0]);

    //set board[1][0]
    board[1][0].addNeighbors(&board[1][1]);
    board[1][0].addNeighbors(&board[0][2]);
    board[1][0].addNeighbors(&board[0][0]);

    //set board[2][0]
    board[2][0].addNeighbors(&board[1][0]);
    board[2][0].addNeighbors(&board[1][1]);
    board[2][0].addNeighbors(&board[2][1]);
    board[2][0].addNeighbors(&board[3][1]);
    board[2][0].addNeighbors(&board[3][0]);

    //set board[3][0]
    board[3][0].addNeighbors(&board[2][0]);
    board[3][0].addNeighbors(&board[3][1]);
    board[3][0].addNeighbors(&board[4][0]);

    //set board[4][0]
    board[4][0].addNeighbors(&board[3][0]);
    board[4][0].addNeighbors(&board[3][1]);
    board[4][0].addNeighbors(&board[4][1]);

    //set board[0][8]
    board[0][8].addNeighbors(&board[1][7]);
    board[0][8].addNeighbors(&board[0][7]);

    //set board[1][8]
    board[1][8].addNeighbors(&board[0][8]);
    board[1][8].addNeighbors(&board[1][7]);
    board[1][8].addNeighbors(&board[2][7]);

    //set board[2][8]
    board[2][8].addNeighbors(&board[1][8]);
    board[2][8].addNeighbors(&board[1][7]);
    board[2][8].addNeighbors(&board[2][7]);
    board[2][8].addNeighbors(&board[3][7]);
    board[2][8].addNeighbors(&board[3][8]);

    //set board[3][8]
    board[3][8].addNeighbors(&board[2][8]);
    board[3][8].addNeighbors(&board[3][7]);
    board[3][8].addNeighbors(&board[4][8]);

    //set board[4][8]
    board[4][8].addNeighbors(&board[3][8]);
    board[4][8].addNeighbors(&board[3][7]);
    board[4][8].addNeighbors(&board[4][7]);

    //set [0] , ...
    for(int g = 1 ; g<=7;g+=2)
    {
        board[0][g].addNeighbors(&board[0][g+1]);
        board[0][g].addNeighbors(&board[1][g]);
        board[0][g].addNeighbors(&board[0][g-1]);
    }

    for(int g = 1 ; g<=7;g+=2)
    {
        board[4][g].addNeighbors(&board[4][g+1]);
        board[4][g].addNeighbors(&board[3][g]);
        board[4][g].addNeighbors(&board[4][g-1]);
    }

    for(int n =2 ; n<=6 ; n+=2)
    {
        board[0][n].addNeighbors(&board[0][n+1]);
        board[0][n].addNeighbors(&board[0][n-1]);
        board[0][n].addNeighbors(&board[1][n-1]);
        board[0][n].addNeighbors(&board[1][n]);
        board[0][n].addNeighbors(&board[1][n+1]);
    }

    for(int n =2 ; n<=6 ; n+=2)
    {
        board[4][n].addNeighbors(&board[4][n+1]);
        board[4][n].addNeighbors(&board[4][n-1]);
        board[4][n].addNeighbors(&board[3][n-1]);
        board[4][n].addNeighbors(&board[3][n]);
        board[4][n].addNeighbors(&board[3][n+1]);
    }

    for(int m = 1;m<=7;m+=2)
    {
        board[1][m].addNeighbors(&board[0][m-1]);
        board[1][m].addNeighbors(&board[0][m]);
        board[1][m].addNeighbors(&board[0][m+1]);
        board[1][m].addNeighbors(&board[1][m-1]);
        board[1][m].addNeighbors(&board[1][m+1]);
        board[1][m].addNeighbors(&board[2][m-1]);
        board[1][m].addNeighbors(&board[2][m]);
        board[1][m].addNeighbors(&board[2][m+1]);

    }

    for(int m = 1;m<=7;m+=2)
    {
        board[3][m].addNeighbors(&board[2][m-1]);
        board[3][m].addNeighbors(&board[2][m]);
        board[3][m].addNeighbors(&board[2][m+1]);
        board[3][m].addNeighbors(&board[3][m-1]);
        board[3][m].addNeighbors(&board[3][m+1]);
        board[3][m].addNeighbors(&board[4][m-1]);
        board[3][m].addNeighbors(&board[4][m]);
        board[3][m].addNeighbors(&board[4][m+1]);

    }


    for(int n =2 ; n<=6 ; n+=2)
    {
        board[1][n].addNeighbors(&board[0][n]);
        board[1][n].addNeighbors(&board[1][n+1]);
        board[1][n].addNeighbors(&board[1][n-1]);
        board[1][n].addNeighbors(&board[2][n]);
    }

    for(int n =2 ; n<=6 ; n+=2)
    {
        board[3][n].addNeighbors(&board[2][n]);
        board[3][n].addNeighbors(&board[3][n+1]);
        board[3][n].addNeighbors(&board[3][n-1]);
        board[3][n].addNeighbors(&board[4][n]);
    }
    for(int n =1 ; n<=7 ; n+=2)
    {
        board[2][n].addNeighbors(&board[1][n]);
        board[2][n].addNeighbors(&board[2][n+1]);
        board[2][n].addNeighbors(&board[2][n-1]);
        board[2][n].addNeighbors(&board[3][n]);
    }
    for(int m = 2;m<=6;m+=2)
    {
        board[2][m].addNeighbors(&board[1][m-1]);
        board[2][m].addNeighbors(&board[1][m]);
        board[2][m].addNeighbors(&board[1][m+1]);
        board[2][m].addNeighbors(&board[2][m-1]);
        board[2][m].addNeighbors(&board[2][m+1]);
        board[2][m].addNeighbors(&board[3][m-1]);
        board[2][m].addNeighbors(&board[3][m]);
        board[2][m].addNeighbors(&board[3][m+1]);

    }


}

vector<Cell*> Fanorona:: getvalidMoves(int r, int c)
{
    vector<Cell*> validmoves;

    if(r<0 || r >= 5 || c<0 || c >= 9)
    {
        return validmoves;
    }

    Cell* thisCell = &board[r][c];

    if( !thisCell->isPlayerpiece(getCurrentPlayer()))
    {
        return validmoves;
    }

    vector<Cell*> neighbors;

    neighbors = thisCell->getNeighbors();

    for(int i =0 ; i<neighbors.size();i++)
    {
        if(neighbors[i]->isEmpty())
        {
            validmoves.push_back(neighbors[i]);
        }
    }
    return validmoves;
}

bool Fanorona:: isValidMove(int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow < 0 || fromRow >= 5 || fromCol < 0 || fromCol >= 9) return false;
    if (toRow < 0 || toRow >= 5 || toCol < 0 || toCol >= 9) return false;

    Cell* firstCell =  &board[fromRow][fromCol];

    Cell* secondCell =  &board[toRow][toCol];

    if (firstCell->isNeighbor(secondCell) && secondCell->isEmpty())
    {
        if (waitingAgainCapture &&toRow == previousRow &&toCol == previousCol)
        {
            return false;
        }
        return true;
    }
    return false;
}

void Fanorona::executeMove(int fromRow, int fromCol, int toRow, int toCol)
{

    if (!isValidMove(fromRow, fromCol, toRow, toCol)) return;

    int currentPlayer = getCurrentPlayer();

    int opvalue = (getCurrentPlayer() == 1) ? 2 : 1 ;


    previousRow = fromRow;
    previousCol = fromCol;

    lastFromRow = fromRow;
    lastFromCol = fromCol;

    lastToRow = toRow;
    lastToCol = toCol;

    bool canApproach = false;
    bool canWithdrawal = false;


    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    int nr = toRow + dr;
    int nc = toCol + dc;

    int pr = fromRow - dr;
    int pc = fromCol - dc;

    int captured = 0;

    if (nr >= 0 && nr < 5 && nc >= 0 && nc < 9 )
    {
        if (board[nr][nc].getValue() == opvalue)
            canApproach = true;
    }

    if (pr >= 0 && pr < 5 && pc >= 0 && pc < 9)
    {
        if (board[pr][pc].getValue() == opvalue)
            canWithdrawal = true;
    }

    if (canApproach && canWithdrawal)
    {

        canTwoWayCalim =true;

        pieceForTwoWayCapture = getPieceTwoWay();
        waitingAgainCapture = true;
        board[toRow][toCol].setValue(currentPlayer);
        board[fromRow][fromCol].setValue(0);
        return;
    }
    board[toRow][toCol].setValue(currentPlayer);
    board[fromRow][fromCol].setValue(0);
    if (canApproach && !canWithdrawal)
    {
        captured =claimPiece(fromRow, fromCol, toRow, toCol, dr, dc, true);
    }

    if (!canApproach && canWithdrawal)
    {
        captured =claimPiece(fromRow, fromCol, toRow, toCol, dr, dc, false);
    }



    if (captured > 0)
    {

        if (currentPlayer == 1)
        {
            player2count -= captured;
        }
        else
        {
            player1count -= captured;
        }

        vector<Cell*> captures = getPossibleCaptures(toRow, toCol);

        if (!captures.empty())
        {

            pendingCaptures = captures;
            waitingAgainCapture= true;
            return;
        }
    }



    waitingAgainCapture = false;
    pendingCaptures.clear();
    previousRow = -1;
    previousCol = -1;
    switchTurn();






}

void Fanorona::selectCaptureType(int row, int col)
{
    if (!canTwoWayCalim)
        return;

    if (row < 0 || row >= 5 || col < 0 || col >= 9)
        return;

    int opponent = (getCurrentPlayer() == 1) ? 2 : 1;

    if (board[row][col].getValue() != opponent)
        return;

    int dr = lastToRow - lastFromRow;
    int dc = lastToCol - lastFromCol;

    bool approach = false;
    bool found = false;

   
    int checkRow = lastToRow + dr;
    int checkCol = lastToCol + dc;

    while (checkRow >= 0 && checkRow < 5 &&
           checkCol >= 0 && checkCol < 9 &&
           board[checkRow][checkCol].getValue() == opponent)
    {
        if (checkRow == row && checkCol == col)
        {
            approach = true;
            found = true;
            break;
        }

        checkRow += dr;
        checkCol += dc;
    }

  
    if (!found)
    {
        checkRow = lastFromRow - dr;
        checkCol = lastFromCol - dc;

        while (checkRow >= 0 && checkRow < 5 &&
               checkCol >= 0 && checkCol < 9 &&
               board[checkRow][checkCol].getValue() == opponent)
        {
            if (checkRow == row && checkCol == col)
            {
                approach = false;
                found = true;
                break;
            }

            checkRow -= dr;
            checkCol -= dc;
        }
    }

  
    if (!found)
        return;

    int captured = claimPiece(lastFromRow,lastFromCol,lastToRow,lastToCol,dr,dc,approach);

    if (getCurrentPlayer() == 1)
        player2count -= captured;
    else
        player1count -= captured;

    board[lastToRow][lastToCol].setValue(getCurrentPlayer());
    board[lastFromRow][lastFromCol].setValue(0);
    waitingAgainCapture = false;
    pieceForTwoWayCapture.clear();
    pendingCaptures.clear();
    canTwoWayCalim = false;

    vector<Cell*> captures = getPossibleCaptures(lastToRow, lastToCol);

    if (!captures.empty())
    {
        pendingCaptures = captures;
        waitingAgainCapture = true;
        return;
    }
    waitingAgainCapture = false;
    canTwoWayCalim = false;
    pieceForTwoWayCapture.clear();
    pendingCaptures.clear();
    previousRow = -1;
    previousCol = -1;
    switchTurn();
}

vector<Cell*> Fanorona::getPieceTwoWay()
{
    vector<Cell*> pieces;
    int currentPlayer = getCurrentPlayer();
    int opponent = (currentPlayer == 1) ? 2 : 1;


    int dr = lastToRow - lastFromRow;
    int dc = lastToCol - lastFromCol;


    int checkRow = lastFromRow - dr;
    int checkCol = lastFromCol - dc;

    while (checkRow >= 0 && checkRow < 5 && checkCol >= 0 && checkCol < 9) {
        if (board[checkRow][checkCol].getValue() == opponent) {
            pieces.push_back(&board[checkRow][checkCol]);
            checkRow -= dr;
            checkCol -= dc;
        } else {
            break;
        }
    }


    checkRow = lastToRow + dr;
    checkCol = lastToCol + dc;

    while (checkRow >= 0 && checkRow < 5 && checkCol >= 0 && checkCol < 9)
    {
        if (board[checkRow][checkCol].getValue() == opponent) {
            pieces.push_back(&board[checkRow][checkCol]);
            checkRow += dr;
            checkCol += dc;
        } else {
            break;
        }
    }

    return pieces;
}

vector<Cell*> Fanorona::getPossibleCaptures(int fromRow, int fromCol)
{
    vector<Cell*> possibleMoves;

    int currentPlayer = getCurrentPlayer();

    int opponent = (currentPlayer == 1) ? 2 : 1;

    vector<Cell*> neighbors = board[fromRow][fromCol].getNeighbors();

    for (Cell* neighbor : neighbors)
    {
        if (!neighbor->isEmpty()) continue;

        int toRow = neighbor->getRow();
        int toCol = neighbor->getCol();

        if (toRow == previousRow && toCol == previousCol)
            continue;

        int dr = toRow - fromRow;
        int dc = toCol - fromCol;


        int checkRow = fromRow - dr;
        int checkCol = fromCol - dc;
        if (checkRow >= 0 && checkRow < 5 && checkCol >= 0 && checkCol < 9)
        {
            if (board[checkRow][checkCol].getValue() == opponent)
            {
                possibleMoves.push_back(neighbor);
                continue;
            }
        }


        checkRow = fromRow + dr;
        checkCol = fromCol + dc;
        if (checkRow >= 0 && checkRow < 5 && checkCol >= 0 && checkCol < 9) {
            if (board[checkRow][checkCol].getValue() == opponent) {
                possibleMoves.push_back(neighbor);
            }
        }
    }

    return possibleMoves;
}

int Fanorona::claimPiece(int fromRow, int fromCol,int toRow, int toCol, int dr, int dc, bool approach)
{
    int opponent = (getCurrentPlayer() == 1) ? 2 : 1;
    int captured = 0;

    int checkRow;
    int checkCol;

    if (approach)
    {
        
        checkRow = toRow + dr;
        checkCol = toCol + dc;

        while (checkRow >= 0 && checkRow < 5 &&
               checkCol >= 0 && checkCol < 9 &&
               board[checkRow][checkCol].getValue() == opponent)
        {
            board[checkRow][checkCol].setValue(0);
            captured++;

            checkRow += dr;
            checkCol += dc;
        }
    }
    else
    {
        
        checkRow = fromRow - dr;
        checkCol = fromCol - dc;

        while (checkRow >= 0 && checkRow < 5 &&
               checkCol >= 0 && checkCol < 9 &&
               board[checkRow][checkCol].getValue() == opponent)
        {
            board[checkRow][checkCol].setValue(0);
            captured++;

            checkRow -= dr;
            checkCol -= dc;
        }
    }

    return captured;
}

void Fanorona::claimPieceagain(int toRow, int toCol )
{
    if (!waitingAgainCapture) return;

    bool found = false;
    for (int g= 0 ;g < pendingCaptures.size();g++)
    {
        if (pendingCaptures[g]->getRow() == toRow && pendingCaptures[g]->getCol() == toCol)
        {
            found = true;
            break;
        }
    }
    if (!found) return;



    executeMove(lastToRow, lastToCol, toRow, toCol);
}

bool Fanorona::getWaiting()
{
    return waitingAgainCapture;
}

int Fanorona:: getValue(int row ,int col) const
{
    return board[row][col].getValue();
}

bool Fanorona::getCanTwoWay()
{
    return canTwoWayCalim;
}

bool Fanorona::isGameOver() const
{

    if(player1count==0 || player2count == 0)
    {
        return true;
    }
    if (!canMove(getCurrentPlayer()))
    {
        return true;
    }
    return false;
}

bool Fanorona::canMove(int n) const
{
    for(int i =0;i<5;i++)
    {
        for(int j=0;j<9;j++)
        {

            if(board[i][j].getValue()==n)
            {
                vector<Cell*> neighbor =board[i][j].getNeighbors();
                for(int f= 0;f<neighbor.size();f++)
                {
                    if(neighbor[f]->isEmpty())
                    {
                        return true;
                    }

                }
            }

        }

    }
    return false;
}

int Fanorona::getWinner() const
{
    if (!isGameOver()) return 0;

    if (player1count == 0) return 2;
    if (player2count == 0) return 1;

    if (!canMove(getCurrentPlayer()))
    {
        return (getCurrentPlayer() == 1) ? 2 : 1;
    }
    return 0;
}

bool Fanorona::isPlayerPiece(int row, int col) const
{
    if (row < 0 || row >= 5 || col < 0 || col >= 9)
    {
        return false;
    }

    if (board[row][col].isEmpty())
    {
        return false;
    }

    return board[row][col].isPlayerpiece(getCurrentPlayer());
}

vector<Cell*> Fanorona::getPieceTwo()
{
    return pieceForTwoWayCapture;
}