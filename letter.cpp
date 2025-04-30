#include "letter.h"
#include <QLabel>
#include <QFont>
#include <QDebug>

Letter::Letter(QString text, QWidget *parent)
    : QWidget{parent}
{
  QLabel *label = new QLabel(this);


  label->setText(text);

  QFont font = label->font();
  font.setPointSize(20);
  label->setFont(font);

  setFixedSize(label->size());
//  startFallAnimation();
}

int Letter::getEndPositions() {
  return parentWidget()->height() - height() - 50;
}

void Letter::updateFallAnimation(int newEndValue) {
  if (fallAnimation && fallAnimation->state() == QAbstractAnimation::Running) {
    int currentTime = fallAnimation->currentTime();
    fallAnimation->pause();
    fallAnimation->setEndValue(newEndValue);
    fallAnimation->setCurrentTime(currentTime);
    fallAnimation->resume();
  }
}

void Letter::startFallAnimation() {
  fallAnimation = new QPropertyAnimation(this, "posY");
  fallAnimation->setDuration(2000);
  fallAnimation->setStartValue(this->y());

  fallAnimation->setEndValue(getEndPositions());
  fallAnimation->setEasingCurve(QEasingCurve::OutBounce);

//  connect(fallAnimation, &QPropertyAnimation::finished, this, []() {
////    fallAnimation->deleteLater();
//  });

  fallAnimation->start();//QPropertyAnimation::DeleteWhenStopped
}
