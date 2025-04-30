#include "mainwindow.h"
#include "letter.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

//  setAttribute(Qt::WA_TranslucentBackground);
  setWindowFlags(windowFlags());
  // Qt::FramelessWindowHint

  resize(300, 600);
  setFocusPolicy(Qt::StrongFocus);  // Разрешаем фокус
  setFocus();
}

MainWindow::~MainWindow()
{
  for(auto l: qAsConst(letters)) {
    delete l;
    l = nullptr;
  }

  delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {

  if(event->key() == Qt::Key_Backspace) {
    actionBackspace();
    QWidget::keyPressEvent(event);
    return;
  }

  Letter *letter = new Letter(event->text(), this);
  checkWidthWindow(letter);

  letter->move(posX, posY);
  letter->show();
  letters.push_back(letter);

  posX += 30;

  QWidget::keyPressEvent(event);
}

void MainWindow::checkWidthWindow(Letter *letter) {
  if(posX + 30 < this->width()) {
    letter->startFallAnimation();
    return;
  }

  shiftLetters();
  letter->startFallAnimation();
  posX = 50;
}

void MainWindow::shiftLetters() {
  for(auto l: qAsConst(letters)) {
    if(l->fallAnimation) {
      if(l->fallAnimation->state() == QAbstractAnimation::Running) {
        l->updateFallAnimation(l->getEndPositions() - 50);
      }
      else l->move(l->x(), l->y() - 50);
    }

  }
}

void MainWindow::actionBackspace() {
  if(letters.isEmpty()) return;
  delete letters.back();
  letters.pop_back();
  posX -= 30;
}
