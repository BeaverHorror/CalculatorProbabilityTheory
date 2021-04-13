#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui { class Form; }
class Form : public QWidget { Q_OBJECT
public:
  explicit Form(QWidget *parent = nullptr);
  ~Form();
public slots:
  void number_str_recieveData(QString str);
  void first_str_recieveData(QString str);
  void second_str_recieveData(QString str);
  void result_str_recieveData(QString str);
  void n_str_recieveData(QString str);
  void m_str_recieveData(QString str);
  void operation_str_recieveData(QString str);
  void key_str_recieveData(QString str);
  void p1_str_recieveData(QString str);
  void p2_str_recieveData(QString str);
  void p3_str_recieveData(QString str);
  void p4_str_recieveData(QString str);
  void p5_str_recieveData(QString str);
  void t0_int_recieveData(int i);
  void t1_int_recieveData(int i);
  void t2_int_recieveData(int i);
  void t3_int_recieveData(int i);
  void n_char_recieveData(QString str);
  void m_char_recieveData(QString str);
  void number_double_recieveData(double d);
  void first_double_recieveData(double d);
  void second_double_recieveData(double d);
  void result_double_recieveData(double d);
  void n_double_recieveData(double d);
  void m_double_recieveData(double d);
  void number_size_int_recieveData(int i);
  void first_int_recieveData(int i);
  void result_int_recieveData(int i);
  void n_int_recieveData(int i);
  void m_int_recieveData(int i);
  void mode_int_recieveData(int i);
  void num_int_recieveData(int i);
  void equally_int_recieveData(int i);
  void direction_int_recieveData(int i);
  void zero_int_recieveData(int i);
  void currentPath_recieveData(QString str);
  void combinatorics_name_Path_recieveData(QString str);
private:
  Ui::Form *ui;
};

#endif // FORM_H
