#ifndef FIFTHLAB_H
#define FIFTHLAB_H

#include <QMainWindow>
#include <QtCharts> // библиотека для построения графиков
#include <QtCharts/QChart>

namespace Ui { class fifthlab; }                                 //
class fifthlab : public QMainWindow { Q_OBJECT                  //
public:                                                        //
  explicit fifthlab(QWidget *parent = nullptr); ~fifthlab();  //
  QString currentPath;                                       // Текущий каталог str
  char currentPath_char[255];                               // Текущий каталог char
  QString Data_txt;                                        // .txt файл данных str
  char Data_txt_char[255];                                // .txt файл данных char
  double d[1000];                                        // Считанные числа
  double d2[1000];                                      //
  QString d_str;                                       // Первичное считывание
  QString d1_str;                                      // Не используется
  QString d2_str;                                      //
  QString di_str[1000];                                //
  int t[1001];                                         // Индексы пробелов
  QString t_str;                                       //
  int count = 0;                                       // Кол-во разных вариантов чисел
  double count2[1000];                                 //
  double count3[1000];                                 //
  QString count2_str;                                  //
  double numberVariant[1000];                          // Числа представленные в подборке
  QString numberVariant_str;                           // Числа представленные в подборке (str)
  int numberSpaces;                                    // Кол-во пробелов
  int num;                                             // Кол-во чисел
  double d_min;                                        //
  double d_max;                                        //
  double d_average;                                   //
  QString row;                                       // Вариационный ряд
  double x_min;                                     //
  double x_max;                                    //
  double y_min;                                   //
  double y_max;                                  //
  int x_cap;                                    //
  int y_cap;                                   //
  QString Fx_str[1001];                       //
  QString Fxt_str;                           //
  QString Fxn_str;                          //
  QString Fxt2_str;                        //
  QString Fxn2_str;                       //
                                         //
  double P;                             //
  double Pch[1001];                    //
  int organize;                       // Упорядочить массив
  double Mx = 0;                     //
  QString Mx_str;                   //
  double Mx2 = 0;                  //
  double Dx = 0;                  //
  double Bx = 0;                 //
  double Sx = 0;                //
  double d_test;               //
  int jay;                     //
  QString text_str;            //
  int SB;                      // Кол-во интервалов
  QString rval_str;            // Считанная строка
  QString rval2_str[100];      // Разбиение на подстроки          //
  QString rval_test;           // Пуско-Наладка                  //
  double rval_min[100];        // Разбиение подстроки на min и max
  double rval_max[100];        // Разбиение подстроки на min и max
  double rval_average[100];    //                             //
  QString rval_min_str[100];   //                            //
  QString rval_max_str[100];   //                           //
  int spSplt1;                 // Кол-во пробелов          //
  int sp1[101];                // Индексы пробелов        //
  int sp2;                     // Индекс тире            //
  double distr[100];           // хранит кол-во чисел в интервале
  char png_name_char[255];                             // Путь до картинки с формулой
  QString png_name;                                   // Путь до картинки с формулой
                                                     //
private slots:                                      //
  void on_pushButton_action_clicked();             // Действие
  void setData();                                 // Установить данные
  void readData();                                // Считать данные
  void convertData();                             // Преобразовать считанные данные
  void calculateData();                           //
  void on_spinBox_1_valueChanged(int arg1);       //
  void on_pushButton_chart_clicked();             //
  void on_checkBox_stateChanged(int arg1);        //
  void on_radioButton_4_clicked();                //
  void on_radioButton_3_clicked();                //
  void on_radioButton_clicked();                  //
  void on_radioButton_Gni_clicked();              //
  void on_radioButton_Gwi_clicked();             //
  void on_radioButton_load_clicked();           //
  void on_radioButton_arm_clicked();           //
  void zeroize();                             //
  void intervals();                          //

  void on_comboBox_formula_activated(int index);

private:
  Ui::fifthlab *ui;
  QChart *chrt;      // график функций
};

#endif // FIFTHLAB_H
