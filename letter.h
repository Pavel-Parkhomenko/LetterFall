#ifndef LETTER_H
#define LETTER_H

#include <QWidget>
#include <QPropertyAnimation>

class Letter : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(int posY READ posY WRITE setPosY  NOTIFY posYChanged)

public:
  explicit Letter(QString text, QWidget *parent = nullptr);
  ~Letter();

  void startFallAnimation();
  int getEndPositions();
  bool isWillShift = false;
  void updateFallAnimation(int newEndValue);
  QPropertyAnimation *fallAnimation = nullptr;
  int getRand(int min, int max);

  int posY() const {
    return m_posY;
  }

  void setPosY(int yy) {
    m_posY = yy;
    move(this->x(), m_posY);
    emit posYChanged();
  }

private:
  int m_posY;
//  QPropertyAnimation *fallAnimation = nullptr;

signals:
  void posYChanged();

};

#endif // LETTER_H
