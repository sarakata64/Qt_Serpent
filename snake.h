#ifndef SNAKE_H
#define SNAKE_H


#include <QWidget>
#include <QtWidgets>
#include <QKeyEvent>
#include <QImage>



class Snake : public QWidget {

  public:
      Snake(QWidget *parent = nullptr);

  protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);
      void keyPressEvent(QKeyEvent *);

  private:
      QImage dot;
      QImage head;
      QImage apple;

      static const int B_WIDTH = 400;
      static const int B_HEIGHT = 400;
      static const int DOT_SIZE = 10;
      static const int ALL_DOTS = 900;
      static const int RAND_POS = 29;
      static const int DELAY = 140;

      int timerId;
      int dots;
      int apple_x;
      int apple_y;

      int x[ALL_DOTS];
      int y[ALL_DOTS];

      bool leftDirection;
      bool rightDirection;
      bool upDirection;
      bool downDirection;
      bool inGame;
      void chargementImage();
      void initGame();
      void positionSerpent();
      void gain();
      void Collision();
      void deplacment();
      void affichage();
      void fin(QPainter &);
};

#endif // SNAKE_H
