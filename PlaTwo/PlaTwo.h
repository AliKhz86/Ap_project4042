#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PlaTwo.h"

class PlaTwo : public QMainWindow
{
    Q_OBJECT

public:
    PlaTwo(QWidget *parent = nullptr);
    ~PlaTwo();

private:
    Ui::PlaTwoClass ui;
};

