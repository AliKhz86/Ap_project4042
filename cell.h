#ifndef CELL_H
#define CELL_H
#include <vector>
using namespace std;
class Cell
{
    int value; //  0 = nobody| 1= player1 |  2 =player2

    int row;

    int col;

    vector<Cell*> neighbors;

public:

    Cell();

    //getters

     int getValue()const;

     const vector<Cell*>& getNeighbors() const;

     int getRow() const;

     int getCol() const;



    //setters

    void setCol(int co);

    void setRow(int ro);

    void setValue(int valu);

    void addNeighbors(Cell* ce);

    //checkers

    bool isEmpty() const;

    bool isPlayerpiece(int player) const ;

    bool isNeighbor(Cell* cell) const;
	
     void Cell::clearNeighbors() ;
};

#endif // CELL_H
