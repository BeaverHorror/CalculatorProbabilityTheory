#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <QDialog>
#include <QDir>
#include <cmath>

namespace Ui { class Polynomial; }
class Polynomial : public QDialog { Q_OBJECT
public:
  explicit Polynomial(QWidget *parent = nullptr); ~Polynomial();
  int error;
  int sum;
  QString n_3_str;
  int n_3_int;
  QString m_3_str;
  int m_3_int[6];
  QString p_3_str;
  double p_3_double[6];
  double answer_3_double;
  QString answer_3_str;
  int xC, yC, xGC, yGC, xGCW, yGCW;
private slots:
  int factorial(int i);
  double polynomial(int n, int m[6], double p[6]);
  void close_recieveData(int i);
  void on_pushButton_decision_3_clicked();
  void xC_int_recieveData    (int i);
  void yC_int_recieveData  (int i);
  void xGC_int_recieveData (int i);
  void yGC_int_recieveData (int i);
  void xGCW_int_recieveData  (int i);
  void yGCW_int_recieveData(int i);
  void location();
private:
  Ui::Polynomial *ui;
};

#endif // POLYNOMIAL_H
