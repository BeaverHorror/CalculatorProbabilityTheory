#ifndef POISSON_H
#define POISSON_H

#include <QDialog>
#include <QDir>
#include <cmath>

namespace Ui { class Poisson; }
class Poisson : public QDialog { Q_OBJECT
public:
  explicit Poisson(QWidget *parent = nullptr); ~Poisson();
  int error = 0;
  QString n_2_str;  // n
  int n_2_int;
  QString m_2_str;  // m
  int m_2_int;
  QString m1_2_str;  // m
  int m1_2_int;
  QString m2_2_str;  // m
  int m2_2_int;
  QString p_2_str;  // p
  double p_2_double;
  double answer_2_double;
  QString answer_2_str;
  int xC, yC, xGC, yGC, xGCW, yGCW;
private slots:
  void on_pushButton_decision_2_clicked();
  int factorial(int i);
  int exarticulation(QString str, int num);
  double poisson(int n, int m, double p);
  void close_recieveData(int i);
  void xC_int_recieveData    (int i);
  void yC_int_recieveData  (int i);
  void xGC_int_recieveData (int i);
  void yGC_int_recieveData (int i);
  void xGCW_int_recieveData  (int i);
  void yGCW_int_recieveData(int i);
  void location();
private:
  Ui::Poisson *ui;
};

#endif // POISSON_H
