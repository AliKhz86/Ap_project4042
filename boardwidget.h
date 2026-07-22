#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H
#include "Fanorona.h"
#include <vector>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QWidget>

class BoardWidget : public QWidget
{
    Q_OBJECT

    int cellSize =100;

    bool isPieceSelected = false;

    int selectedRow =-1 , selectedCol = -1;

    vector<Cell*> validMoves;

    Fanorona * game = nullptr;

private:

    void drawBoard(QPainter& painter);

    void drawEllipse(QPainter& painter);

    void drawTwoWayHighlights(QPainter& painter);

    void drawHighlight(QPainter& painter);

    void handleFirstClick(int row , int col);

    void handleSecondClick(int row , int col);

    void cancelSelection();


protected:

    void paintEvent(QPaintEvent * event ) override;

    void mousePressEvent(QMouseEvent * event) override;

public:
    explicit BoardWidget( QWidget *parent = nullptr);

    void setGame(Fanorona * game);

signals:
};

#endif // BOARDWIDGET_H
