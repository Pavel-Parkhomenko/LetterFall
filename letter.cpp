#include "letter.h"
#include <QLabel>
#include <QFont>
#include <QDebug>
#include <QRandomGenerator>

Letter::Letter(QString text, QWidget *parent)
    : QWidget{parent}
{
  QLabel *label = new QLabel(this);


  label->setText(text);
  QColor color = QColor::fromHsv(getRand(1, 255), getRand(1, 255), getRand(1, 255));

  QFont font = label->font();
  font.setPointSize(30);
  label->setFont(font);
  label->setStyleSheet(QString("color: %1;").arg(color.name()));


  QFontMetrics metrics(font);
  QRect textRect = metrics.boundingRect(text);
  const int padding = 5;
  setFixedSize(
      textRect.width() + 2 * padding,
      textRect.height() + 2 * padding
      );

  label->setAlignment(Qt::AlignCenter);
  label->setGeometry(0, 0, width(), height());

}

int Letter::getRand(int min, int max) {
  return QRandomGenerator::global()->bounded(min, max + 1);
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

Letter::~Letter() {
  if(fallAnimation) delete fallAnimation;
}
