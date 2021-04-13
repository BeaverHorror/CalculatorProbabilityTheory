#ifndef BERNOULLI_H
#define BERNOULLI_H

#include <QDialog>
#include <QDir>
#include <cmath>

namespace Ui { class Bernoulli; }
class Bernoulli : public QDialog {  Q_OBJECT
public:
  explicit Bernoulli(QWidget *parent = nullptr); ~Bernoulli();
  int error = 0;
  QString sign_str;      // Введённая строка
  int sign1 = 0;         // Кол-во знаков '<'
  int sign1_index_1 = 0; // Индекс первого знака '<'
  int sign1_index_2 = 0; // Индекс второго знака '<'
  int sign2 = 0;         // Кол-во знаков '>'
  int sign2_index_1 = 0; // Индекс первого знака '>'
  int sign2_index_2 = 0; // Индекс второго знака '>'
  int sign3 = 0;         // Кол-во знаков '='
  int sign3_index_1 = 0; // Индекс первого знака '='
  int sign3_index_2 = 0; // Индекс второго знака '='
  int sign4_index_m = 0;
  QString n_1_str;  // n
  int n_1_int;
  int mode = 0;
  QString m_1_str;  // m
  int m_1_int;
  QString m1_1_str; // a
  int m1_1_int;
  QString m2_1_str; // b
  int m2_1_int;
  QString p_1_str;  // p
  double p_1_double;
  double answer_1_double;
  QString answer_1_str;
  int xC, yC, xGC, yGC, xGCW, yGCW;
private slots:
  int factorial(int i);
  int soch(int n, int m);
  double bernoulli(int n, int k, double p);
  int exarticulation(QString str, int num);
  void close_recieveData(int i);
  void on_pushButton_decision_1_clicked();
  void xC_int_recieveData    (int i);
  void yC_int_recieveData  (int i);
  void xGC_int_recieveData (int i);
  void yGC_int_recieveData (int i);
  void xGCW_int_recieveData  (int i);
  void yGCW_int_recieveData(int i);
  void location();
private:
  Ui::Bernoulli *ui;
};

#endif // BERNOULLI_H
