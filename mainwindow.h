#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>

#include "letter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void actionBackspace();
  void checkWidthWindow(Letter *letter);
  void shiftLetters();

  private:
  Ui::MainWindow *ui;

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  QVector<Letter*> letters;
  int posX = 100;
  int posY = 0;
};
#endif // MAINWINDOW_H
