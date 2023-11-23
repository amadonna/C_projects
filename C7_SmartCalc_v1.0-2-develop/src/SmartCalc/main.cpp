#include <QApplication>
#include <QLabel>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  //    QPalette pal = a.palette();
  //    pal.setColor(QPalette::Window, Qt::white);
  //    a.setPalette(pal);
  w.show();

  return a.exec();
}
