#include "boardwidget.h"
#include "QColor"
#include <QWidget>
#include <QPainter>

BoardWidget::BoardWidget(QWidget *parent)
    : QWidget{parent}
{
    resize(800 , 400);

}


void BoardWidget::drawBoard(QPainter& painter)
{
    painter.setPen(QPen(Qt::black, 1));
    for(int i=0;i<8;i++ )
    {
        painter.drawLine(cellSize*i,0,cellSize*i,height());

    }

    for(int i=0;i<4;i++ )
    {
        painter.drawLine(0,cellSize*i,width(),cellSize*i);
    }

    painter.drawLine(0,2*cellSize,2*cellSize,height());
    painter.drawLine(width()-2*cellSize,0,width(),2*cellSize);

    for(int i = 0 ;i<=2;i++)
    {

        painter.drawLine(2*i*cellSize,0,2*i*cellSize+4*cellSize,height());
    }


    painter.drawLine(0,2*cellSize,2*cellSize,0);
    painter.drawLine(width()-2*cellSize,height(),width(),2*cellSize);

    for(int i = 0 ;i<=2;i++)
    {

        painter.drawLine(4*cellSize+2*i*cellSize,0,2*cellSize*i,height());
    }
}

void BoardWidget::drawEllipse(QPainter& painter)
{ 
   if (!game)
    return;
  for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int value = game->getValue(i, j);
            if (value == 0) continue;

            int x = j * cellSize;
            int y = i * cellSize;

            painter.setBrush(value == 1 ? Qt::black : Qt::white);
            painter.setPen(Qt::black);
            painter.drawEllipse(x - 18, y - 18, 36, 36);
        }
    }
}

void BoardWidget::drawHighlight(QPainter& painter)
{
    if (validMoves.empty() || !isPieceSelected)
        return;

    for(Cell * temp : validMoves)
    {
        int x = temp->getCol() *cellSize;
        int y = temp->getRow() * cellSize;
        painter.setBrush(Qt::green);
        painter.drawEllipse(x- 18, y - 18, 36, 36);
    }
}

void BoardWidget::drawTwoWayHighlights(QPainter& painter)
{
    if(!game->getCanTwoWay())
        return;

    vector<Cell*> pieces = game->getPieceTwo();
    for (Cell* cell : pieces)
    {
        int x = cell->getCol() * cellSize;
        int y = cell->getRow() * cellSize ;
	painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::green);
        painter.drawEllipse(x - 24, y - 24, 48, 48);

    }
}


void BoardWidget::handleFirstClick(int row , int col)
{
    if (game->isPlayerPiece(row, col))
    {
        selectedRow = row;
        selectedCol = col;
        isPieceSelected = true;
        validMoves = game->getvalidMoves(row, col);
        update();
    }
}

void BoardWidget::handleSecondClick(int row , int col)
{
    for (Cell* cell : validMoves)
    {
        if (cell->getRow() == row && cell->getCol() == col)
        {
            game->executeMove(selectedRow, selectedCol, row, col);
            cancelSelection();
            update();
            return;
        }
    }
    cancelSelection();
    update();
}

void BoardWidget::cancelSelection()
{
    isPieceSelected = false;
    selectedRow = -1;
    selectedCol = -1;
    validMoves.clear();
}

void BoardWidget::setGame(Fanorona * game)
{
    this->game = game;
    update();
}

void BoardWidget::paintEvent(QPaintEvent * event )
{
if (!game)
    return;
 QPainter painter(this);

    drawBoard(painter);
    drawEllipse(painter);
    drawHighlight(painter);
    drawTwoWayHighlights(painter);
}

void BoardWidget::mousePressEvent(QMouseEvent * event)
{
    if (!game) return;

    int x = event->pos().x();
    int y = event->pos().y();
    int row = y / cellSize;
    int col = x / cellSize;

    if (row < 0 || row >= 5 || col < 0 || col >= 9) return;


    if (game->getWaiting())
    {
        game->claimPieceagain(row, col);
        update();
        return;
    }

    if (game->getCanTwoWay())
    {
        game->selectCaptureType(row, col);
        update();
        return;
    }

    if (!isPieceSelected)
    {
        handleFirstClick(row, col);
        return;
    }

     handleSecondClick(row, col);
}
