#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "form.h"
#include "secondwindow.h"
#include "bernoulli.h"
#include "polynomial.h"
#include "poisson.h"
#include "mychart.h"
#include "fifthlab.h"
#include <QString>
#include <cmath>
#include <qmath.h>
#include <stdio.h>
#include <stdlib.h>

namespace Ui { class MainWindow; }
class MainWindow : public QMainWindow { Q_OBJECT
public:
  int  mode        = 0;              // Номер операции
  int  num         = 0;              // Номер операции комбинаторики
  int  equally     = 0;              // Операция получения результата
  int  direction   = 0;              // Направление
  int  error       = 0;              //
  int  zero        = 0;              //
  int  data_output = 0;              // Вывод информации только один раз
  char num_char[2];                  //
  double n = 0;                      // n
  int int_n = 0;                     // n
  QString n_str;                     // n
  char n_char[4];                    //
  double m = 0;                      // m
  int int_m = 0;                     // m
  QString m_str;                     // m
  char m_char[4];                    //
  double number = 0;                 // Общее число
  QString number_str = "0";          // Общее число
  int number_size = 0;               // Кол-во символов
  double first = 0;                  // Первое число
  int int_first = 0;                 // Первое число
  QString first_str;                 // Первое число
  double second = 0;                 // Второе число
  QString second_str;                // Второе число
  double result = 0;                 // Результат
  int int_result = 0;                // Результат
  QString result_str;                // Результат
  QString operation_str;             // Операция записанная как строка
  int p[10];                         // Передача параметров
  QString currentPath;               // возвращает текущий каталог
  char currentPath_char[255];        //
  QString combinatorics_name;        // имя приложения комбинаторики
  char combinatorics_name_char[255]; //
  QString tasks_name;                // имя приложения задач
  char tasks_name_char[255];         //
  QString laba2_name;                // имя приложения задач
  char laba2_name_char[255];         //
  QString laba3_name;                // имя приложения задач
  char laba3_name_char[255];
  // Перестановки с повторениями
  char p1_char[255] = "0";                                                           //
  char p2_char[255] = "0";                                                          //
  char p3_char[255] = "0";                                                         //
  char p4_char[255] = "0";                                                        //
  char p5_char[255] = "0";                                                       //
  QString p1_str = "";                                                          //
  QString p2_str = "";                                                         //
  QString p3_str = "";                                                        //
  QString p4_str = "";                                                       //
  QString p5_str = "";                                                      //
  int t[255];               // индекс точки                                //
  int number_of_points = 0; // Кол-во точек                               //
  QString absPath;          // возвращаем абсолютный путь, включающий имя файла
  QString baseName;         // возвращаем базовое имя: имя файла без пути
  QString compBaseName;     // возвращаем полное базовое имя: все символы в файле до последней точки (но не включая её)
  QString fileName;         // возвращаем имя файла, которое является базовым именем + расширение
  QString suffix;           // возвращаем расширение файла, которое состоит из всех символов в файле после последнего символа точки (но не включая её)
  QString compSuffix;       // возвращаем расширение файла, которое состоит из всех символов в файле после первого символа точки (но не включая её) 
  int xC, yC, xGC, yGC, xGCW, yGCW;                                //
                                                                  //
  explicit MainWindow(QWidget *parent = nullptr); ~MainWindow(); //
  // Передача данных другой форме                               //
signals:                                                       //
  void number_str_Data(QString str);                          //
  void first_str_Data(QString str);                          //
  void second_str_Data(QString str);                        //
  void result_str_Data(QString str);                       //
  void n_str_Data(QString str);                           //
  void m_str_Data(QString str);                          //
  void operation_str_Data(QString str);                 //
  void key_str_Data(QString str);                      //
  void p1_str_Data(QString str);                      // Перестановки с повторениями
  void p2_str_Data(QString str);                     // Перестановки с повторениями
  void p3_str_Data(QString str);                    // Перестановки с повторениями
  void p4_str_Data(QString str);                   // Перестановки с повторениями
  void p5_str_Data(QString str);                  // Перестановки с повторениями
  void t0_int_Data(int i);                       // Перестановки с повторениями индекс первой точки
  void t1_int_Data(int i);                      // Перестановки с повторениями индекс второй точки
  void t2_int_Data(int i);                     // Перестановки с повторениями индекс третей точки
  void t3_int_Data(int i);                    // Перестановки с повторениями индекс второй точки
  void xC_int_Data(int i);                   // Передача координта курсора на теле виджета   // Для окна формул
  void yC_int_Data(int i);                  // Передача координта курсора на теле виджета
  void xGC_int_Data(int i);                // Передача глобальных координта курсора
  void yGC_int_Data(int i);               // Передача глобальных координта курсора
  void xGCW_int_Data(int i);              // Передача координтат главного окна
  void yGCW_int_Data(int i);              // Передача координтат главного окна
  void xC_int_B_Data(int i);              // Передача координта курсора на теле виджета   // Для окна формулы Бернулли
  void yC_int_B_Data(int i);              // Передача координта курсора на теле виджета
  void xGC_int_B_Data(int i);             // Передача глобальных координта курсора
  void yGC_int_B_Data(int i);             // Передача глобальных координта курсора
  void xGCW_int_B_Data(int i);            // Передача координтат главного окна
  void yGCW_int_B_Data(int i);            // Передача координтат главного окна
  void xC_int_Py_Data(int i);             // Передача координта курсора на теле виджета   // Для окна формулы Пуассона
  void yC_int_Py_Data(int i);             // Передача координта курсора на теле виджета
  void xGC_int_Py_Data(int i);            // Передача глобальных координта курсора
  void yGC_int_Py_Data(int i);            // Передача глобальных координта курсора
  void xGCW_int_Py_Data(int i);           // Передача координтат главного окна
  void yGCW_int_Py_Data(int i);           // Передача координтат главного окна
  void xC_int_Po_Data(int i);             // Передача координта курсора на теле виджета   // Для окна Полиномиальной формулы
  void yC_int_Po_Data(int i);             // Передача координта курсора на теле виджета
  void xGC_int_Po_Data(int i);            // Передача глобальных координта курсора
  void yGC_int_Po_Data(int i);            // Передача глобальных координта курсора
  void xGCW_int_Po_Data(int i);           // Передача координтат главного окна
  void yGCW_int_Po_Data(int i);           // Передача координтат главного окна
  void n_char_Data(QString str);          //
  void m_char_Data(QString str);           //
  void number_double_Data(double d);        //
  void first_double_Data(double d);          //
  void second_double_Data(double d);          //
  void result_double_Data(double d);           //
  void n_double_Data(double d);                  //
  void m_double_Data(double d);                   //
  void number_size_int_Data(int i);               //
  void first_int_Data(int i);                     //
  void result_int_Data(int i);                    //
  void n_int_Data(int i);                         //
  void m_int_Data(int i);                         //
  void mode_int_Data(int i);                      //
  void num_int_Data(int i);                       //
  void equally_int_Data(int i);                   //
  void direction_int_Data(int i);                 //
  void zero_int_Data(int i);                      //
  void currentPath_Data(QString str);             //
  void combinatorics_name_Path_Data(QString str); //
  void formula_Data(int i);                      // Передача номера операции комбинаторики
  void close_Data(int i);                       // Передача приказа о закрытии
private slots:                                  //
  void Placements_without_repetition();         // нажатие Размещения без повторений
  void Placements_with_repetition();            // нажатие Размещения c повтореними
  void Combinations_without_repetition();       // нажатие Сочетания без повторений
  void Combinations_with_repetition();          // нажатие Сочетания с повторениями
  void Permutations_without_repetitions();      // нажатие Перестановки без повторений
  void Permutations_with_repetitions();         // нажатие Перестановки с повторениями
  void on_pushButton_point_clicked();           // нажатие Точка
  void on_pushButton_negation_clicked();        // нажатие Инверсия
  void creating_the_number();                   // Создание числа
  void on_pushButton_AC_clicked();             // Обнуление переменных
  void on_pushButton_CE_clicked();            // Частичное удаление
  void reset_number();                       //
  void reset_first();                       //
  void reset_second();                     //
  void reset_result();                    //
  void reset_operation_str();            //
  void reset_n();                        //
  void reset_m();                         //
  void reset_t();                          //
  void reset_p_str();                       //
  void reset_p_char();                       //
  void on_pushButton_plus_clicked();          // Операция сложения
  void on_pushButton_minus_clicked();          // Операция вычитания
  void on_pushButton_multiply_clicked();        // Операция умножения
  void on_pushButton_share_clicked();           // Операция деления
  void on_pushButton_degree_clicked();          //
  void on_pushButton_root_clicked();            //
  void on_pushButton_root_2_clicked();          // Нахождение квадратного корня
  void on_pushButton_degree_2_clicked();        // Нахождение квадрата числа
  void on_pushButton_factorial_clicked();       // Операция нахождения факториала
  void on_pushButton_result_clicked();          // Результат операции
  int factorial(int i);                         // Функция вычисления факториала
  void Arithmetic_simplification();             // Упростить арифметические операции
  void Arithmetic_simplification_2();           // Упростить арифметические операции
  void One_operation_simplification();          // Упростить операции с одним числом
  void One_operation_simplification_2();        // Упростить операции с одним числом
  void simplification_of_the_combinatorics();   // Упростить операции комбинаторики
  void on_pushButton_n_clicked();               // n
  void on_pushButton_m_clicked();               // m
  void on_pushButton_RNU_clicked();             // Округление вверх (инкремент)
  void on_pushButton_RND_clicked();             // Округление вниз (декремент)
  void adjustment();                            // Вывод параметров
  void other_application();                     // Вызов приложения для расчёта комбинаторики
  void on_pushButton_clicked();                 // Пуско-Наладка
  void on_pushButton_tasks_clicked();           // Вызов приложения для решения задач
  void on_pushButton_left_clicked();            // Пролистать влево результат
  void on_pushButton_right_clicked();           // Пролистать вправо результат
  void secondwindow();                          //
  QString factorial_test(int n);                // Блок непосредственного вычисления больших факториалов
  QString bigLine(int I[500]);                  // Передаём массив int[500] и забираем строку в которую он переписан
  void on_pushButton_bernoulle_clicked();       //
  void on_pushButton_polynomial_clicked();      //
  void on_pushButton_poisson_clicked();         //
  void on_pushButton_tasks_2_clicked();        //
  void on_pushButton_tasks_3_clicked();       //
  void on_pushButton_tasks_4_clicked();      //
  void on_pushButton_tasks_5_clicked();     // 
protected:
  bool eventFilter(QObject *watched, QEvent *event); // Ловим события
  void keyPressEvent(QKeyEvent *event);              // Ловим события нажатия клавиш
private:                                   //
  Ui::MainWindow *ui;                     //
  Form *myform;                          //
  SecondWindow *window;                 //
  Bernoulli *twoform;                  //
  Polynomial *zibenform;              //
  Poisson *ailform;                  //
  MyChart *lulyform;                //
  fifthlab *aits;                  //
};                                //
                                 //
#endif // MAINWINDOW_H          //
