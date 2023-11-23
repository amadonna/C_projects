#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <QDialog>

extern "C" {
#include "s21_calc.h"
}

namespace Ui {
class Graphic;
}

class Graphic : public QDialog {
  Q_OBJECT

 public:
  explicit Graphic(QWidget *parent = nullptr);
  ~Graphic();
 public slots:
  void slot(QString func);
 private slots:

  void on_pushButton_ok_clicked();

 private:
  Ui::Graphic *ui;
  QString t;
  long double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
};

#endif  // GRAPHIC_H
