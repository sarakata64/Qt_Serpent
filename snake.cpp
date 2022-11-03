#include <QPainter>
#include <QTime>
#include "snake.h"
#include <QFontMetrics>
#include <QString>
Snake::Snake(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:blue;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);
    chargementImage();
    initGame();
}

void Snake::chargementImage() {
// chargement des images

    dot.load(":/image/apple.png");
    head.load(":/image/head.png");
    apple.load(":/image/apple.png");

// redimensionnemnet des images à 20 px
    dot = dot.scaled(20, 20, Qt::KeepAspectRatio);
    head = head.scaled(20, 20, Qt::KeepAspectRatio);
    apple = apple.scaled(20, 20, Qt::KeepAspectRatio);
}

void Snake::initGame() {

    // nombre de points initial
    dots = 3;

    for (int z = 0; z < dots; z++) {
        x[z] = 50 - z * 20;
        y[z] = 50;
    }

    positionSerpent();

    timerId = startTimer(DELAY);
}

void Snake::paintEvent(QPaintEvent *) {

     affichage();
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(7);
    painter.setPen(pen);
    QBrush brush1(Qt::blue,Qt::SolidPattern);
    QRect rec1(0,0,B_WIDTH,B_HEIGHT);
    painter.drawRect(rec1);

}

void Snake::affichage() {

    QPainter qp(this);

    if (inGame) {

        qp.drawImage(apple_x, apple_y, apple);

        for (int z = 0; z < dots; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], dot);
            }
        }

    } else {

        fin(qp);
    }
}

void Snake::fin(QPainter &qp) {

    QString message = QString("FIN ! vous avez eu %1 points ").arg(dots-3);
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);

    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

// on verifie pour voir si le serpent a pu manger la pomme ou pas, si oui, on augmente le point puis on fait apparaitre une autre pomme aléatoirement
void Snake::gain() {

    if ((x[0] == apple_x) && (y[0] == apple_y)) {

        dots++;
       positionSerpent();
    }
}

// le deplacement  et le control du serpent
void Snake::deplacment() {

    for (int z = dots; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }

    if (leftDirection) {
        x[0] -= DOT_SIZE;
    }

    if (rightDirection) {
        x[0] += DOT_SIZE;
    }

    if (upDirection) {
        y[0] -= DOT_SIZE;
    }

    if (downDirection) {
        y[0] += DOT_SIZE;
    }
}
// on si le serpent n'est pas depassé le cadre du jeu
void Snake::Collision() {

    for (int z = dots; z > 0; z--) {
// on verifie pour voir si le serpent ne s'est pas mordu
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }

    if (y[0] >= B_HEIGHT) {
        inGame = false;
    }

    if (y[0] < 0) {
        inGame = false;
    }

    if (x[0] >= B_WIDTH) {
        inGame = false;
    }

    if (x[0] < 0) {
        inGame = false;
    }

    if(!inGame) {
        killTimer(timerId);
    }
}

// choisir aleatoirement la position de la pomme
void Snake::positionSerpent() {

    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());

    int r = qrand() % RAND_POS;
    apple_x = (r * DOT_SIZE);

    r = qrand() % RAND_POS;
    apple_y = (r * DOT_SIZE);
}

void Snake::timerEvent(QTimerEvent *) {



    if (inGame) {

        gain();
        Collision();
        deplacment();
    }

    repaint();
}

// évenement KeyPress pour le controle
void Snake::keyPressEvent(QKeyEvent *e) {

    int key = e->key();

    if ((key == Qt::Key_Left) && (!rightDirection)) {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Right) && (!leftDirection)) {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
    }

    if ((key == Qt::Key_Up) && (!downDirection)) {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    if ((key == Qt::Key_Down) && (!upDirection)) {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
    }

    QWidget::keyPressEvent(e);
}

