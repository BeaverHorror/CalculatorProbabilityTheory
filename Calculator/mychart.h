#ifndef MYCHART_H
#define MYCHART_H

#include <QMainWindow>
#include <QtCharts> // библиотека для построения графиков
#include <QtCharts/QChart>

namespace Ui { class MyChart; }
class MyChart : public QMainWindow { Q_OBJECT
public:
  explicit MyChart(QWidget *parent = nullptr); ~MyChart();
  // Работа с директориями
  QString currentPath;               // возвращает текущий каталог
  char currentPath_char[255];
  QString png1;
  char png1_char[255];
  int count = 3;
  int error = 0;
  int x1[10];
  int x2[24];
  double sum = 0;
  double p[10];
  double p2[24];
  double P;
  double Mx = 0;
  QString Mx_str;
  double Mx2 = 0;
  double Dx = 0;
  double Bx = 0;
  QString Fx_str[11];
  double lambda;
private slots:
  void on_pushButton_solution_clicked();
  void on_spinBox_count_valueChanged(int arg1);
  void on_pushButton_chart_1_clicked();
  void saveData();                       // Сохранение значений
  void setData();                        // Установка значений
  void resettingData();                  // Сброс данных
  int factorial(int i);
  double poisson(int m, double p);
  void close_recieveData(int i);
  void on_radioButton_4_clicked();
  void on_radioButton_3_clicked();
private:
  Ui::MyChart *ui;
  QChart *chrt;      // график функций
  //QChartView *chrtv;
};

#endif // MYCHART_H
