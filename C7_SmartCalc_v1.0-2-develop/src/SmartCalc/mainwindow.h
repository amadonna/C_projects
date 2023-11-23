#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <graphic.h>

#include <QMainWindow>
#include <QVector>

extern "C" {
#include "s21_calc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Graphic *graph_w;

 private slots:
  void digits_numbers();
  void on_pushButton_dot_clicked();
  void negativity();
  void operations();
  void bracets();
  void cleaner();
  void funcs();
  void x();
  void eq();
  void on_pushButton_g_clicked();
  void on_pushButton_count_clicked();
  // void del_zero(QString *str);

  // void on_lineEdit_sum_textChanged(const QString &arg1);

 signals:
  void signal(QString);
};

#endif  // MAINWINDOW_H
