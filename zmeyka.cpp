#include <QPainter>
#include <QTime>
#include "zmeyka.h"

Zmeyka::Zmeyka(QWidget *parent) : QWidget(parent) {

    setStyleSheet("background-color:black;");
    inGame = true;
    leftMove = false;
    rightMove = true;
    upMove = false;
    downMove = false;
    resize(F_WIDTH, F_HEIGHT);
    loadImages();
    initGame();
}

void Zmeyka::loadImages() {
    tail.load("D:\\Zmeyka\\tail.png");
    head.load("D:\\Zmeyka\\head.png");
    apple.load("D:\\Zmeyka\\apple.png");
}

void Zmeyka::initGame() {
    cells = 3;
    for (int z = 0; z < cells; z++) {
        x[z] = 50 - z * 10;
        y[z] = 50;
    }
    placeApple();
    timerId = startTimer(SPEED);
}

void Zmeyka::paintEvent(QPaintEvent *e) {

    Q_UNUSED(e);

    doShow();
}

void Zmeyka::doShow() {
    QPainter qp(this);
    if (inGame) {
        qp.drawImage(apple_x, apple_y, apple);
        for (int z = 0; z < cells; z++) {
            if (z == 0) {
                qp.drawImage(x[z], y[z], head);
            } else {
                qp.drawImage(x[z], y[z], tail);
            }
        }
    } else {
        gameOver(qp);
    }
}

void Zmeyka::gameOver(QPainter &qp) {
    QString message = "Game over";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);
    qp.setPen(QColor(Qt::white));
    qp.setFont(font);
    int h = height();
    int w = width();
    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message);
}

void Zmeyka::placeApple() {
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
    int r = qrand() % RAND_POS;
    apple_x = (r * CELL_SIZE);
    r = qrand() % RAND_POS;
    apple_y = (r * CELL_SIZE);
}

void Zmeyka::move() {
    for (int z = cells; z > 0; z--) {
        x[z] = x[(z - 1)];
        y[z] = y[(z - 1)];
    }
    if (leftMove) {
        x[0] -= CELL_SIZE;
    }
    if (rightMove) {
        x[0] += CELL_SIZE;
    }
    if (upMove) {
        y[0] -= CELL_SIZE;
    }
    if (downMove) {
        y[0] += CELL_SIZE;
    }
}

void Zmeyka::keyPressEvent(QKeyEvent *e) {
    int key = e->key();
    if ((key == Qt::Key_Left) && (!rightMove)) {
        leftMove = true;
        upMove = false;
        downMove = false;
    }
    if ((key == Qt::Key_Right) && (!leftMove)) {
        rightMove = true;
        upMove = false;
        downMove = false;
    }
    if ((key == Qt::Key_Up) && (!downMove)) {
        upMove = true;
        rightMove = false;
        leftMove = false;
    }
    if ((key == Qt::Key_Down) && (!upMove)) {
        downMove = true;
        rightMove = false;
        leftMove = false;
    }
    QWidget::keyPressEvent(e);
}

void Zmeyka::checkContact() {
    for (int z = cells; z > 0; z--) {
        if ((z > 4) && (x[0] == x[z]) && (y[0] == y[z])) {
            inGame = false;
        }
    }
    if (y[0] >= F_HEIGHT) {
        inGame = false;
    }
    if (y[0] < 0) {
        inGame = false;
    }
    if (x[0] >= F_WIDTH) {
        inGame = false;
    }
    if (x[0] < 0) {
        inGame = false;
    }
    if(!inGame) {
        killTimer(timerId);
    }
}

void Zmeyka::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);
    if (inGame) {
        contactApple();
        checkContact();
        move();
    }
    repaint();
}

void Zmeyka::contactApple() {
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        cells++;
        placeApple();
    }
}
