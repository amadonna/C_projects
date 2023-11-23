#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget{parent}, ui(new Ui::Widget) {
  ui->setupUi(this);
  scale_num = 0.3;
  ui->label_scale->setText(QString::number(scale_num, 'f', 2));
  ui->x_rotation->setMaximum(181);
  ui->x_rotation->setMinimum(-181);

  ui->y_rotation->setMaximum(181);
  ui->y_rotation->setMinimum(-181);

  ui->z_rotation->setMaximum(181);
  ui->z_rotation->setMinimum(-181);
  ui->z_rotation->setValue(0);
  ui->y_rotation->setValue(0);
  ui->x_rotation->setValue(0);
  ui->label_x_rot->setValidator(new QIntValidator(-180, 18, this));
  ui->label_y_rot->setValidator(new QIntValidator(-180, 18, this));
  ui->label_z_rot->setValidator(new QIntValidator(-180, 18, this));
  QDoubleValidator *doubleValidator = new QDoubleValidator(-1, 1, 2, this);
  doubleValidator->setNotation(QDoubleValidator::StandardNotation);
  ui->label_x_move->setValidator(doubleValidator);
  ui->label_y_move->setValidator(doubleValidator);
  ui->label_z_move->setValidator(doubleValidator);

  connect(ui->x_rotation, &QScrollBar::sliderMoved, this, [=] {
    int x_val = 0;
    x_val = ui->x_rotation->value();
    ui->label_x_rot->setText(QString::number(x_val));
  });
  connect(ui->label_x_rot, &QLineEdit::textChanged, this, [=] {
    int x_val = 0;
    x_val = ui->label_x_rot->text().toInt();
    ui->x_rotation->setValue(x_val);
  });

  connect(ui->y_rotation, &QScrollBar::sliderMoved, this, [=] {
    int y_val = 0;
    y_val = ui->y_rotation->value();
    ui->label_y_rot->setText(QString::number(y_val));
  });
  connect(ui->label_y_rot, &QLineEdit::textChanged, this, [=] {
    int y_val = 0;
    y_val = ui->label_y_rot->text().toInt();
    ui->y_rotation->setValue(y_val);
  });

  connect(ui->z_rotation, &QScrollBar::sliderMoved, this, [=] {
    int z_val = 0;
    z_val = ui->z_rotation->value();
    ui->label_z_rot->setText(QString::number(z_val));
  });
  connect(ui->label_z_rot, &QLineEdit::textChanged, this, [=] {
    int z_val = 0;
    z_val = ui->label_z_rot->text().toInt();
    ui->z_rotation->setValue(z_val);
  });
  prev_angle_x = 0;
  prev_angle_y = 0;
  prev_angle_z = 0;
  translate_x = translate_y = translate_z = 0;
  prev_coor_x = prev_coor_y = prev_coor_z = 0;

  file_exists = 0;

  connect(ui->x_move_down, SIGNAL(clicked()), this, SLOT(translation()));
  connect(ui->x_move_up, SIGNAL(clicked()), this, SLOT(translation()));
  connect(ui->y_move_down, SIGNAL(clicked()), this, SLOT(translation()));
  connect(ui->y_move_up, SIGNAL(clicked()), this, SLOT(translation()));
  connect(ui->z_move_down, SIGNAL(clicked()), this, SLOT(translation()));
  connect(ui->z_move_up, SIGNAL(clicked()), this, SLOT(translation()));
}

Widget::~Widget() {
  cleanAll(&myData);
  delete ui;
}

void Widget::on_pushButton_clicked() {
  QString str;
  str = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users",
                                     "All Files (*.obj)");
  ui->label_filename->setText(str);
  QByteArray s = str.toLocal8Bit();
  char *filename = s.data();
  cleanAll(&myData);
  myData.countEdges = 0;
  myData.countFacets = 0;
  myData.countVertex = 0;
  myData.poligons = NULL;
  myData.vector_3d = NULL;
  translate_x = translate_y = translate_z = 0;
  scale_num = 0.3;
  ui->label_scale->setText(QString::number(scale_num, 'f', 2));
  ui->z_rotation->setValue(0);
  ui->y_rotation->setValue(0);
  ui->x_rotation->setValue(0);
  if (readOne(filename, &myData) == 0) {
    readTwo(filename, &myData);
    file_exists = 1;
    centerVertex(&myData);
    changeScale(&myData, 0.3);
    ui->label_Vertexes->setText(QString::number(myData.countVertex));
    ui->label_edges->setText(QString::number(myData.countEdges));
  } else {
    ui->label_filename->setText("FILE NOT FOUND!(");
    file_exists = 0;
  }
}

void Widget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void Widget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Widget::paintGL() {
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslated(translate_x, translate_y, translate_z);

  draw();
}

void Widget::draw() {
  glVertexPointer(3, GL_DOUBLE, 0, myData.vector_3d);

  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawElements(GL_LINES, myData.countFacets, GL_UNSIGNED_INT,
                 myData.poligons);

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Widget::on_button_scale_down_clicked() {
  if (file_exists && scale_num > 0.01) {
    scale_num -= 0.01;
    changeScale(&myData, scale_num);
    ui->label_scale->setText(QString::number(scale_num, 'f', 2));
    update();
  }
}

void Widget::on_button_scale_up_clicked() {
  if (file_exists && scale_num < 1.3) {
    scale_num += 0.01;
    changeScale(&myData, scale_num);
    ui->label_scale->setText(QString::number(scale_num, 'f', 2));
    update();
  }
}

void Widget::translation() {
  if (file_exists) {
    QPushButton *button = (QPushButton *)sender();
    if (button->text() == "X-") translate_x -= 0.1;
    if (button->text() == "X+") translate_x += 0.1;
    if (button->text() == "Y-") translate_y -= 0.1;
    if (button->text() == "Y+") translate_y += 0.1;
    if (button->text() == "Z-") translate_z -= 0.1;
    if (button->text() == "Z+") translate_z += 0.1;
    update();
  }
}

void Widget::on_label_scale_textEdited(const QString &arg1) {
  double arg = 0;
  arg = arg1.toDouble();
  if (file_exists && arg > 0.01 && arg < 1.3) {
    scale_num = arg;
    changeScale(&myData, scale_num);
    ui->label_scale->setText(QString::number(scale_num));
    update();
  }
}

void Widget::on_label_x_move_textEdited(const QString &arg1) {
  double temp = 0;
  if (file_exists) {
    temp = arg1.toDouble();
    if (temp < -1.6)
      temp = -1.5;
    else if (temp > 1.6)
      temp = 1.5;
    translate_x += temp - prev_coor_x;
    prev_coor_x = temp;
    update();
  }
}

void Widget::on_label_y_move_textEdited(const QString &arg1) {
  double temp = 0;
  if (file_exists) {
    temp = arg1.toDouble();
    if (temp < -1.6)
      temp = -1.5;
    else if (temp > 1.6)
      temp = 1.5;
    translate_y += temp - prev_coor_y;
    prev_coor_y = temp;
    update();
  }
}

void Widget::on_label_z_move_textEdited(const QString &arg1) {
  double temp = 0;
  if (file_exists) {
    temp = arg1.toDouble();
    if (temp < -1.6)
      temp = -1.5;
    else if (temp > 1.6)
      temp = 1.5;
    translate_z += temp - prev_coor_z;
    prev_coor_z = temp;
    update();
  }
}

void Widget::on_x_rotation_valueChanged(int value) {
  double angle = 0;
  double pr_a = 0;
  angle = (double)value / 180 * M_PI;
  pr_a = (double)prev_angle_x / 180 * M_PI;
  rote_X(&myData, angle - pr_a);
  prev_angle_x = value;
  update();
}

void Widget::on_y_rotation_valueChanged(int value) {
  double angle = 0;
  double pr_a = 0;
  angle = (double)value / 180 * M_PI;
  pr_a = (double)prev_angle_y / 180 * M_PI;
  rote_Y(&myData, angle - pr_a);
  prev_angle_y = value;
  update();
}

void Widget::on_z_rotation_valueChanged(int value) {
  double angle = 0;
  double pr_a = 0;
  angle = (double)value / 180 * M_PI;
  pr_a = (double)prev_angle_z / 180 * M_PI;
  rote_Z(&myData, angle - pr_a);
  prev_angle_z = value;
  update();
}
