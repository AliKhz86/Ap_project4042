#include "cell.h"
#include <vector>
using namespace std;

Cell::Cell() : value(0), row(-1), col(-1) {}

int Cell::getRow() const
{
    return row;
}

int Cell::getCol() const
{
    return col;
}

int Cell::getValue() const
{
    return value;
}

const vector<Cell*>& Cell::getNeighbors() const
{
    return neighbors;
}

void Cell::setValue(int valu)
{
    value = valu;
}

void Cell::setRow(int ro)
{
    row =ro;
}

void Cell::setCol(int co)
{
    col =co;
}

void Cell::addNeighbors(Cell* ce)
{
     neighbors.push_back(ce);
}



bool Cell::isEmpty() const
{
     if(value == 0)
    {
        return true;
    }
     return false;
}


bool Cell::isPlayerpiece(int player) const
{
    if(value == player)
    {
        return true;
    }
    return false;
}

bool Cell::isNeighbor(Cell* cell) const
{
    for(auto it = neighbors.begin() ; it != neighbors.end() ;it++)
    {
        if(*it == cell)
        {
            return true;
        }
    }
    return false;
}

void Cell::clearNeighbors()
{
    neighbors.clear();
}