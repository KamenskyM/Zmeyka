#pragma once

#include <QWidget>
#include <QKeyEvent>

class Zmeyka : public QWidget {

  public:
      Zmeyka(QWidget *parent = 0);

  protected:
      void paintEvent(QPaintEvent *);

  private:
      QImage tail;
      QImage head;
      QImage apple;

      static const int CELL_SIZE = 20; //размер клетки
      static const int F_WIDTH = 600; //ширина игрового поля
      static const int F_HEIGHT = 600; //высота игрового поля
      static const int ALL_CELLS = 900; //общее количество клеток на поле
      static const int SPEED = 120; //скорость игры
      static const int RAND_POS = 29; //для вычисления случайной позиции яблока

      int timerId;
      int cells;
      int apple_x;
      int apple_y;

      int x[ALL_CELLS];
      int y[ALL_CELLS];

      bool inGame;

      void loadImages();
      void initGame();
      void placeApple();
      void contactApple();
      void doShow();
      void gameOver(QPainter &);
};

