#include "mainwindow.h"

#include <qslider.h>

#include <QString>

#include "graphic.h"
#include "ui_mainwindow.h"

//#include <QRegExp>
#include <stdlib.h>

// extern "C" int calc(char *str, double *res);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  // QWidget:setFixedSize()

  ui->setupUi(this);
  ui->result->setValidator(new QDoubleValidator(this));
  ui->result_3->setValidator(new QDoubleValidator(this));

  //    ui->tabWidget->setFixedSize(820,400);
  //    this->setFixedSize(817,378);

  // ui->horizontalSlider_sum->setRange(0, 135);
  ui->lineEdit_sum->setValidator(new QIntValidator(0, 999000000, this));
  QDoubleValidator *doubleValidator = new QDoubleValidator(0.0, 99.0, 2, this);
  doubleValidator->setNotation(QDoubleValidator::StandardNotation);
  ui->percent->setValidator(doubleValidator);
  // ui->percent->setValidator(new QDoubleValidator(0.0, 99.0, 3, this));
  // QDoubleValidator* doubleValidator_res = new QDoubleValidator(, 99.0, 2,
  // this);

  ui->result->setFocus();

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_neg, SIGNAL(clicked()), this, SLOT(negativity()));

  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_dsub, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(operations()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(operations()));

  connect(ui->pushButton_openb, SIGNAL(clicked()), this, SLOT(bracets()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(cleaner()));
  connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(cleaner()));

  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(funcs()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this, SLOT(x()));
  connect(ui->pushButton_equel, SIGNAL(clicked()), this, SLOT(eq()));
  // del_zero(QString *str)

  // connect(ui->lineEdit_sum, SIGNAL(clicked()), this,
  // SLOT(del_zero(ui->lineEdit_sum.text()))); connect(ui->percent,
  // SIGNAL(clicked()), this, SLOT()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString new_label;
  QString new_label_3;
  new_label = ui->result->text();
  new_label_3 = ui->result_3->text();
  if (ui->result->hasFocus()) {
    if (new_label == "0" || new_label == "error" || new_label == "nan")
      new_label.remove(0, new_label.length());
    if (new_label.endsWith(")") || new_label.endsWith("x") ||
        new_label.endsWith("pi"))
      new_label += "*";
    new_label += button->text();
    ui->result->setText(new_label);
  } else if (ui->result_3->hasFocus()) {
    // set_st_res_no_foc(ui->result, ui->result_2);
    // ui->result->setStyleSheet("background-color:rgb(180, 180, 180)");
    // ui->result_3->setStyleSheet("background-color:rgb(0,0,0)");
    if (new_label_3 == "0") new_label_3.remove(0, 1);
    new_label_3 += button->text();
    ui->result_3->setText(new_label_3);
  }
  // ui->result->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked() {
  QString temp;
  int check_dot = 0;
  int check_dot_1 = 0;
  int focus = 0;

  if (ui->result_3->hasFocus()) {
    focus = 1;
    temp = ui->result_3->text();
  } else
    temp = ui->result->text();

  if (temp == "error" || temp == "nan") temp = "0";
  if (temp.length() == 2 && temp.endsWith("."))
    temp.remove(temp.length() - 1, 1);
  else if (!(temp[temp.length() - 1] >= QChar('0')) &&
           !(temp[temp.length() - 1] <= QChar('9')) && temp != "0" &&
           temp[temp.length() - 1] != QChar('.'))
    temp += "0.";
  else {
    for (int i = 0; i < temp.length() - 1; i++) {
      if (!(temp[i] >= QChar('0')) && !(temp[i] <= QChar('9')) &&
          temp[i] != QChar('.'))
        check_dot = i;
    }
    for (int j = check_dot; j < temp.length() - 1; j++) {
      if (temp[j] == QChar('.')) check_dot_1 = 1;
    }
    if (check_dot_1 == 0) temp += ".";
  }
  if (focus == 0)
    ui->result->setText(temp);
  else
    ui->result_3->setText(temp);
}

void MainWindow::negativity() {
  QString temp;
  if (ui->result->hasFocus()) {
    temp = ui->result->text();
    if (temp == "error" || temp == "nan") temp = "0";
    int stop = 0;
    int i = 0;
    if ((temp.at(temp.length() - 1) >= QChar('0') &&
         temp.at(temp.length() - 1) <= QChar('9') && temp != "0") ||
        temp.at(temp.length() - 1) == QChar('.')) {
      i = temp.length() - 1;
      while (i >= 0 && stop == 0) {
        if ((temp.at(i) >= QChar('0') && temp.at(i) <= QChar('9')) ||
            temp.at(i) == QChar('.'))
          i--;
        else if ((temp.at(i) == QChar('-') || temp.at(i) == QChar('+')) &&
                 temp.at(i - 1) == QChar('e'))
          i--;
        else if (temp.at(i) == QChar('e'))
          i--;
        else
          stop = -1;
      }
      if (i <= 0) {
        temp.insert(0, QString("(-"));
        if (!temp.endsWith(".")) temp += ")";
      } else {
        if (temp.at(i) == QChar('-') && temp.at(i - 1) == QChar('('))
          temp.remove(i, 1);
        else {
          temp.insert(i + 1, QString("(-"));
          if (!temp.endsWith(".")) temp += ")";
        }
      }

    } else if (temp == "(-x)")
      temp = "x";
    else if (temp.endsWith("(-x)"))
      temp.remove(temp.length() - 4, 4);
    else if (temp.endsWith("x")) {
      temp.remove(temp.length() - 1, 1);
      temp += "(-x)";
    } else if (temp.endsWith(")")) {
      i = temp.length() - 2;
      while (i >= 0 && stop == 0) {
        if ((temp.at(i) >= QChar('0') && temp.at(i) <= QChar('9')) ||
            temp.at(i) == QChar('.'))
          i--;
        else if ((temp.at(i) == QChar('-') || temp.at(i) == QChar('+')) &&
                 temp.at(i - 1) == QChar('e'))
          i--;
        else if (temp.at(i) == QChar('e'))
          i--;
        else
          stop = -1;
      }

      if (temp.at(i) == QChar('-')) {
        if (i - 2 == -1 ||
            (temp.at(i - 2) <= QChar('a') && temp.at(i - 2) >= QChar('z'))) {
          temp.remove(i - 1, 2);
          temp.remove(temp.length() - 1, 1);
        } else {
          temp.remove(i - 1, 2);
          temp.remove(temp.length() - 1, 1);
        }
      }

    } else if (temp.endsWith("("))
      temp += "-";
    else if (temp.endsWith("(-"))
      temp.remove(temp.length() - 1, 1);
    else
      temp += "(-";

    //        if(temp.length() == 2)
    //            temp.remove(0, 2);
    //        else if(temp.at(temp.length() - 3) >= QChar('a') &&
    //        temp.at(temp.length() - 3) <= QChar('z')) {
    //            temp.remove(i - 1, 2);
    //            temp.remove(temp.length() - 1, 1);
    //        }

    ui->result->setText(temp);
  } else if (ui->result_3->hasFocus()) {
    temp = ui->result_3->text();
    long double num = 0;
    num = temp.toDouble();
    num *= -1;
    ui->result_3->setText(QString::number(num, 'g', 15));
  }
}

void MainWindow::operations() {
  QString temp;
  QPushButton *button = (QPushButton *)sender();
  if (ui->result->hasFocus()) {
    temp = ui->result->text();
    if (temp == "error" || temp == "nan") temp = "0";
    if (temp.endsWith("x") || temp.endsWith(")") ||
        (temp.at(temp.length() - 1) >= QChar('0') &&
         temp.at(temp.length() - 1) <= QChar('9'))) {
      temp += button->text();
    } else if (temp.endsWith("+") || temp.endsWith("*") || temp.endsWith("/") ||
               temp.endsWith("mod") || temp.endsWith("-") ||
               temp.endsWith("^")) {
      if (temp.endsWith("mod"))
        temp.remove(temp.length() - 3, 3);
      else
        temp.remove(temp.length() - 1, 1);
      temp += button->text();
    }
    ui->result->setText(temp);
  }
}

void MainWindow::bracets() {
  QString temp;
  if (ui->result->hasFocus()) {
    temp = ui->result->text();
    if (temp == "error" || temp == "nan") temp = "0";
    int open = 0;
    int close = 0;
    open = temp.count("(");
    close = temp.count(")");

    if (open - close == 0 || temp.endsWith("(")) {
      if (!temp.endsWith("(") && temp != "0" && !temp.endsWith("*") &&
          !temp.endsWith("+") && !temp.endsWith("/") && !temp.endsWith("-") &&
          !temp.endsWith("^"))
        temp += "*";
      if (temp == "0") temp.remove(0, 1);
      temp += "(";
    } else {
      if (!(temp.endsWith("+") || temp.endsWith("-") || temp.endsWith("*") ||
            temp.endsWith("/") || temp.endsWith("mod") || temp.endsWith("^")))
        temp += ")";
      else
        temp += "(";
    }
    ui->result->setText(temp);
  }
}

void MainWindow::cleaner() {
  QString temp;
  QPushButton *button = (QPushButton *)sender();
  if (ui->result->hasFocus()) {
    temp = ui->result->text();

    if (button->text() == "AC") {
      ui->result_2->setText("");
      temp = "0";
    } else if (button->text() == "C")
      temp.remove(temp.length() - 1, 1);
    if (temp.length() == 0 || (button->text() == "C" && temp.length() == 1))
      temp = "0";
    ui->result->setText(temp);
  } else if (ui->result_3->hasFocus()) {
    temp = ui->result_3->text();
    if (temp != "0") {
      if (button->text() == "AC")
        ui->result_3->setText("0");
      else if (button->text() == "AC")
        temp.remove(temp.length() - 1, 1);
    }
  }
}

void MainWindow::funcs() {
  QPushButton *button = (QPushButton *)sender();
  QString temp;
  if (ui->result->hasFocus()) {
    temp = ui->result->text();
    if (temp == "error" || temp == "nan") temp = "0";

    if (!(temp.endsWith("(") || temp.endsWith("+") || temp.endsWith("-") ||
          temp.endsWith("*") || temp.endsWith("/") || temp.endsWith("mod") ||
          temp.endsWith("^"))) {
      if (temp == "0") temp.remove(0, 1);
      if (temp.length() > 0) temp += "*";
    }
    temp += button->text() + "(";
    ui->result->setText(temp);
  }
}

void MainWindow::x() {
  QPushButton *button = (QPushButton *)sender();
  QString temp;

  if (ui->result->hasFocus()) {
    temp = ui->result->text();
    if (temp == "error" || temp == "nan") temp = "0";
    if (!(temp.endsWith("(") || temp.endsWith("+") || temp.endsWith("-") ||
          temp.endsWith("*") || temp.endsWith("/") || temp.endsWith("mod") ||
          temp.endsWith("^"))) {
      if (temp == "0") temp.remove(0, 1);
      if (temp.length() > 0) temp += "*";
    }
    temp += button->text();
    ui->result->setText(temp);
  }
}

void MainWindow::eq() {
  QString temp;
  // if (ui->result->hasFocus()) {
  temp = ui->result->text();
  if (temp == "error" || temp == "nan") temp = "0";
  ui->result_2->setText(temp);
  temp.replace("mod", "%");
  std::string str_string;
  str_string = temp.toStdString();
  const char *str = str_string.c_str();
  long double result_d;

  if (s21_smart_calc(str, &result_d, ui->result_3->text().toDouble()) == 0 &&
      isnan(result_d) == 0 && isinf(result_d) == 0 && temp.length() < 256)
    ui->result->setText(QString::number(result_d, 'g', 15));
  else
    ui->result->setText("error");
  //}
}

// void MainWindow::on_pushButton_g_clicked()
//{
//     graph_w = new Graphic;
//     graph_w->show();
//     connect(this, &MainWindow::signal, graph_w, &Graphic::slot);
//     emit signal(ui->result->text());
////    graph_w.setModal(true);

////    graph_w.exec();
//}

void MainWindow::on_pushButton_g_clicked() {
  graph_w = new Graphic;
  graph_w->show();
  connect(this, &MainWindow::signal, graph_w, &Graphic::slot);
  emit signal(ui->result->text());
  //    graph_w.setModal(true);

  //    graph_w.exec();
}

// void MainWindow::on_horizontalSlider_sum_valueChanged(int value)
//{
//     ui->lineEdit_sum->text().remove(0, ui->lineEdit_sum->text().length());
//     if(value <= 20)
//         value *= 10000;
//     else if(value > 20 && value < 37) {
//         int j = 0;
//         for(int i = 20; i < value; i++)
//             j++;
//         value = (value + j * 4) * 10000;
//     } else if(value >= 37 && value <= 126) {
//         int j = 63;
//         for(int i = 36; i < value; i++)
//             j += 9;
//         value = (value + j + 1) * 10000;
//     } else if(value > 126) {
//         int j = 107;
//         for(int i = 127; i < value; i++)
//             j -= 9;
//         value = (value - j) * 1000000;

//    }
//    ui->lineEdit_sum->setText(QString::number(value));
//}

// void MainWindow::on_lineEdit_sum_textEdited(const QString &arg1)
//{
//     int sett = arg1.toInt();
//     if(sett < 100000000 && sett > 0) {
//         if(sett <= 200000) {
//             sett = sett / 10000;
//         } else if(sett > 200000 && sett <= 1000000) {
//             int j = 0;
//             for(int i = 200000; i < sett; i+=50000)
//                 j++;
//             sett = (sett / 10000) - j * 4;
//         } else if(sett >= 1000000 && sett <= 10000000) {
//             int j = 63;
//             for(int i = 1000000; i < sett; i+= 100000)
//                 j+=9;
//             sett = (sett / 10000) - j - 1;
//         } else if(sett >= 10000000 && sett <= 100000000) {
//             int j = 107;
//             for(int i = 20000000; i < sett; i+= 10000000)
//                 j-=9;
//             sett = (sett / 1000000) + j;
//         }
//     }
//     ui->horizontalSlider_sum->setValue(sett);
// }

void MainWindow::on_pushButton_count_clicked() {
  // ui->label_per_m->setText("test");
  QString temp;
  QString temp_1;
  double month = 0;
  double sum_credit = 0;
  double percent = 0;
  int type = 0;
  //
  int i = 0;
  while (ui->month->currentText().at(i) >= QChar('0') &&
         ui->month->currentText().at(i) <= QChar('9')) {
    temp += ui->month->currentText().at(i);
    i++;
  }
  month = temp.toDouble();
  if (ui->month->currentText().contains("лет") ||
      ui->month->currentText().contains("год"))
    month *= 12;
  sum_credit = ui->lineEdit_sum->text().toDouble();
  percent = ui->percent->text().toDouble();

  credit cr = {0, 0, 0, 0, 0};
  // printf("month = %lf\n", month);
  type = ui->type->currentIndex();
  // printf("current_ind = %lf\n",percent);
  cr = s21_credit(sum_credit, month, percent / 100, type);
  if (type == 0) {
    ui->label_per_m->setText(QString::number(cr.per_month, 'f', 2) + " " +
                             ui->valuta->currentText());
    ui->label_pereplata->setText(QString::number(cr.pereplata, 'f', 2) + " " +
                                 ui->valuta->currentText());
    ui->label_sum->setText(QString::number(cr.sum, 'f', 2) + " " +
                           ui->valuta->currentText());
  } else {
    temp_1 += QString::number(cr.per_month_first, 'f', 2);
    temp_1 += " ... ";
    temp_1 += QString::number(cr.per_month_last, 'f', 2);
    ui->label_per_m->setText(temp_1 + " " + ui->valuta->currentText());
    ui->label_pereplata->setText(QString::number(cr.pereplata, 'f', 2) + " " +
                                 ui->valuta->currentText());
    ui->label_sum->setText(QString::number(cr.sum, 'f', 2) + " " +
                           ui->valuta->currentText());
  }
}

// void MainWindow::del_zero(QString *str) {
//     if(*str == "0")
//         str->remove(0, str->length());
// }

// void MainWindow::on_lineEdit_sum_textChanged(const QString &arg1)
//{
//     if(*str == "0")
//         str->remove(0, str->length());
// }
