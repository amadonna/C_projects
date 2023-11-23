#ifndef WIDGET_H
#define WIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QFileDialog>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

#ifdef __cplusplus
extern "C" {
#endif
#include "../backend.h"
#ifdef __cplusplus
}
#endif

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  Ui::Widget *ui;

  Widget(QWidget *parent = nullptr);
  ~Widget();
  double translate_x, translate_y, translate_z;
  int prev_angle_x;
  int prev_angle_y;
  int prev_angle_z;
  double prev_coor_x;
  double prev_coor_y;
  double prev_coor_z;

 private slots:
  void on_pushButton_clicked();

  void on_button_scale_down_clicked();

  void on_button_scale_up_clicked();
  void translation();
  void on_label_scale_textEdited(const QString &arg1);

  void on_label_x_move_textEdited(const QString &arg1);

  void on_label_y_move_textEdited(const QString &arg1);

  void on_label_z_move_textEdited(const QString &arg1);

  void on_x_rotation_valueChanged(int value);

  void on_y_rotation_valueChanged(int value);

  void on_z_rotation_valueChanged(int value);

 private:
  data_struct myData;
  float xRot, yRot, zRot;
  QPoint mPos;
  QTimer tmr;
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void draw();
  double scale_num;
  int file_exists;
};
#endif  // WIDGET_H
