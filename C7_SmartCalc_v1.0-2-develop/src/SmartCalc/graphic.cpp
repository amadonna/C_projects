#include "graphic.h"

#include <limits.h>

//#include "s21_smartcalc.h"
#include "ui_graphic.h"

Graphic::Graphic(QWidget *parent) : QDialog(parent), ui(new Ui::Graphic) {
  ui->setupUi(this);

  this->setFixedSize(800, 655);
  ui->spinBox->setMinimum(-1000000);
  ui->spinBox_2->setMinimum(-1000000);
  ui->spinBox_3->setMinimum(-1000000);
  ui->spinBox_4->setMinimum(-1000000);
  ui->spinBox->setMaximum(1000000);
  ui->spinBox_2->setMaximum(1000000);
  ui->spinBox_3->setMaximum(1000000);
  ui->spinBox_4->setMaximum(1000000);
  ui->spinBox->setValue(-10);
  ui->spinBox_2->setValue(10);
  ui->spinBox_3->setValue(-10);
  ui->spinBox_4->setValue(10);

  connect(ui->pushButton_ok, SIGNAL(clicked()), this,
          SLOT(on_pushButton_ok_clicked()));
}

Graphic::~Graphic() { delete ui; }

void Graphic::slot(QString func) {
  ui->label_5->setText(func);
  t = func;
  t.replace("mod", "%");
}

void Graphic::on_pushButton_ok_clicked() {
  ui->label_5->setText(t);
  // QString temp;

  // printf("func = %s\n", str);
  long double resY = 0;
  long double resYMax = 0;
  long double result = 0;
  // QPen pen;
  // pen.setColor(QColor(137, 38, 87));
  xBegin = ui->spinBox->value();
  xEnd = ui->spinBox_2->value();
  resY = ui->spinBox_3->value();
  resYMax = ui->spinBox_4->value();

  h = 0.05;

  ui->graphicsView->xAxis->setRange(xBegin, xEnd);
  ui->graphicsView->yAxis->setRange(resY, resYMax);
  std::string str_string;
  const char *str;
  str_string = t.toStdString();
  str = str_string.c_str();

  // printf("str = %s\n", str);

  for (X = xBegin; X <= xEnd; X += h) {
    // printf("x = %Lf\n", X);
    if (s21_smart_calc(str, &result, X) == 0) {
      if (result <= resY * 2 || result >= resYMax * 2) result = qQNaN();
      y.push_back(result);
      x.push_back(X);
    } else
      ui->label_5->setText(" error");
  }
  ui->graphicsView->addGraph();
  ui->graphicsView->graph(0)->addData(x, y);
  ui->graphicsView->replot();
  x.clear();
  y.clear();
}
