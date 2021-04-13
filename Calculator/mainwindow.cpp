#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secondwindow.h"
#include "bernoulli.h"
#include "polynomial.h"
#include "QtGui"
#include <QtCore/QCoreApplication>
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <cstring>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);

  on_pushButton_AC_clicked(); // Обнулить всё (место для оптимизации)

  // Работа с директориями и путями
  currentPath = QDir::currentPath();                                   // Директория исполняемого файла
  currentPath.replace("/", "\\\\");                                    // Заменить символы / на \\

  combinatorics_name = "\\\\combinatorics.exe";                        // Имя приложения комбинаторики
  combinatorics_name.prepend(currentPath);                             // Вписать перед именем приложения каталог
  tasks_name = "\\\\laba1.exe";                                        // Имя приложения 1 лабы
  tasks_name.prepend(currentPath);                                     // Вписать перед именем приложения каталог
  laba2_name = "\\\\laba2.exe";                                        // Имя приложения 2 лабы
  laba2_name.prepend(currentPath);                                     // Вписать перед именем приложения каталог
  laba3_name = "\\\\laba3.exe";                                        // Имя приложения 3 лабы
  laba3_name.prepend(currentPath);                                     // Вписать перед именем приложения каталог

  strcpy(combinatorics_name_char, combinatorics_name.toUtf8().data()); // Переписать combinatorics_name (QString) в combinatorics_name_char (char)
  strcpy(tasks_name_char, tasks_name.toUtf8().data());                 // Переписать tasks_name (QString) в tasks_name_char (char)
  strcpy(laba2_name_char, laba2_name.toUtf8().data());                 // Переписать laba2_name (QString) в laba2_name_char (char)
  strcpy(laba3_name_char, laba3_name.toUtf8().data());                 // Переписать laba3_name (QString) в laba3_name_char (char)
  strcpy(currentPath_char, currentPath.toUtf8().data());               // Переписать currentPath (QString) в currentPath_char (char)

  ui->label_currentPath->setText(currentPath_char);                    // Вписать в поле label_currentPath currentPath_char
  ui->label_combinatorics_name->setText(combinatorics_name_char);      // Вписать в поле label_name combinatorics_name_char

  // Связь форм
  window    = new SecondWindow(this);
  twoform   = new Bernoulli(this);
  zibenform = new Polynomial(this);
  ailform   = new Poisson(this);
  lulyform  = new MyChart(this);
  myform    = new Form();
  aits      = new fifthlab();

  connect(ui->pushButton_VP, SIGNAL(clicked()),                 myform, SLOT   (show()));
  connect(this, SIGNAL(formula_Data                 (int)),     window, SLOT   (formula_recieveData              (int)));
  connect(this, SIGNAL(close_Data                   (int)),     window, SLOT   (close_recieveData                (int)));
  connect(this, SIGNAL(xC_int_Data                  (int)),     window, SLOT   (xC_int_recieveData               (int)));
  connect(this, SIGNAL(yC_int_Data                  (int)),     window, SLOT   (yC_int_recieveData               (int)));
  connect(this, SIGNAL(xGC_int_Data                 (int)),     window, SLOT   (xGC_int_recieveData              (int)));
  connect(this, SIGNAL(yGC_int_Data                 (int)),     window, SLOT   (yGC_int_recieveData              (int)));
  connect(this, SIGNAL(xGCW_int_Data                (int)),     window, SLOT   (xGCW_int_recieveData             (int)));
  connect(this, SIGNAL(yGCW_int_Data                (int)),     window, SLOT   (yGCW_int_recieveData             (int)));
  connect(this, SIGNAL(xC_int_B_Data                (int)),     twoform, SLOT  (xC_int_recieveData               (int)));
  connect(this, SIGNAL(yC_int_B_Data                (int)),     twoform, SLOT  (yC_int_recieveData               (int)));
  connect(this, SIGNAL(xGC_int_B_Data               (int)),     twoform, SLOT  (xGC_int_recieveData              (int)));
  connect(this, SIGNAL(yGC_int_B_Data               (int)),     twoform, SLOT  (yGC_int_recieveData              (int)));
  connect(this, SIGNAL(xGCW_int_B_Data              (int)),     twoform, SLOT  (xGCW_int_recieveData             (int)));
  connect(this, SIGNAL(yGCW_int_B_Data              (int)),     twoform, SLOT  (yGCW_int_recieveData             (int)));
  connect(this, SIGNAL(xC_int_Po_Data               (int)),     zibenform, SLOT  (xC_int_recieveData             (int)));
  connect(this, SIGNAL(yC_int_Po_Data               (int)),     zibenform, SLOT  (yC_int_recieveData             (int)));
  connect(this, SIGNAL(xGC_int_Po_Data              (int)),     zibenform, SLOT  (xGC_int_recieveData            (int)));
  connect(this, SIGNAL(yGC_int_Po_Data              (int)),     zibenform, SLOT  (yGC_int_recieveData            (int)));
  connect(this, SIGNAL(xGCW_int_Po_Data             (int)),     zibenform, SLOT  (xGCW_int_recieveData           (int)));
  connect(this, SIGNAL(yGCW_int_Po_Data             (int)),     zibenform, SLOT  (yGCW_int_recieveData           (int)));
  connect(this, SIGNAL(xC_int_Py_Data               (int)),     ailform, SLOT  (xC_int_recieveData               (int)));
  connect(this, SIGNAL(yC_int_Py_Data               (int)),     ailform, SLOT  (yC_int_recieveData               (int)));
  connect(this, SIGNAL(xGC_int_Py_Data              (int)),     ailform, SLOT  (xGC_int_recieveData              (int)));
  connect(this, SIGNAL(yGC_int_Py_Data              (int)),     ailform, SLOT  (yGC_int_recieveData              (int)));
  connect(this, SIGNAL(xGCW_int_Py_Data             (int)),     ailform, SLOT  (xGCW_int_recieveData             (int)));
  connect(this, SIGNAL(yGCW_int_Py_Data             (int)),     ailform, SLOT  (yGCW_int_recieveData             (int)));
  connect(this, SIGNAL(close_Data                   (int)),     twoform, SLOT  (close_recieveData                (int)));
  connect(this, SIGNAL(close_Data                   (int)),     zibenform, SLOT(close_recieveData                (int)));
  connect(this, SIGNAL(close_Data                   (int)),     ailform, SLOT  (close_recieveData                (int)));
  connect(this, SIGNAL(close_Data                   (int)),     lulyform, SLOT (close_recieveData                (int)));
  connect(this, SIGNAL(number_str_Data              (QString)), myform, SLOT(number_str_recieveData              (QString)));
  connect(this, SIGNAL(first_str_Data               (QString)), myform, SLOT(first_str_recieveData               (QString)));
  connect(this, SIGNAL(second_str_Data              (QString)), myform, SLOT(second_str_recieveData              (QString)));
  connect(this, SIGNAL(result_str_Data              (QString)), myform, SLOT(result_str_recieveData              (QString)));
  connect(this, SIGNAL(n_str_Data                   (QString)), myform, SLOT(n_str_recieveData                   (QString)));
  connect(this, SIGNAL(m_str_Data                   (QString)), myform, SLOT(m_str_recieveData                   (QString)));
  connect(this, SIGNAL(operation_str_Data           (QString)), myform, SLOT(operation_str_recieveData           (QString)));
  connect(this, SIGNAL(key_str_Data                 (QString)), myform, SLOT(key_str_recieveData                 (QString)));
  connect(this, SIGNAL(p1_str_Data                  (QString)), myform, SLOT(p1_str_recieveData                  (QString)));
  connect(this, SIGNAL(p2_str_Data                  (QString)), myform, SLOT(p2_str_recieveData                  (QString)));
  connect(this, SIGNAL(p3_str_Data                  (QString)), myform, SLOT(p3_str_recieveData                  (QString)));
  connect(this, SIGNAL(p4_str_Data                  (QString)), myform, SLOT(p4_str_recieveData                  (QString)));
  connect(this, SIGNAL(p5_str_Data                  (QString)), myform, SLOT(p5_str_recieveData                  (QString)));
  connect(this, SIGNAL(t0_int_Data                  (int)),     myform, SLOT(t0_int_recieveData                  (int)));
  connect(this, SIGNAL(t1_int_Data                  (int)),     myform, SLOT(t1_int_recieveData                  (int)));
  connect(this, SIGNAL(t2_int_Data                  (int)),     myform, SLOT(t2_int_recieveData                  (int)));
  connect(this, SIGNAL(t3_int_Data                  (int)),     myform, SLOT(t3_int_recieveData                  (int)));
  connect(this, SIGNAL(n_char_Data                  (QString)), myform, SLOT(n_char_recieveData                  (QString)));
  connect(this, SIGNAL(m_char_Data                  (QString)), myform, SLOT(m_char_recieveData                  (QString)));
  connect(this, SIGNAL(number_double_Data           (double)),  myform, SLOT(number_double_recieveData           (double)));
  connect(this, SIGNAL(first_double_Data            (double)),  myform, SLOT(first_double_recieveData            (double)));
  connect(this, SIGNAL(second_double_Data           (double)),  myform, SLOT(second_double_recieveData           (double)));
  connect(this, SIGNAL(result_double_Data           (double)),  myform, SLOT(result_double_recieveData           (double)));
  connect(this, SIGNAL(n_double_Data                (double)),  myform, SLOT(n_double_recieveData                (double)));
  connect(this, SIGNAL(m_double_Data                (double)),  myform, SLOT(m_double_recieveData                (double)));
  connect(this, SIGNAL(number_size_int_Data         (int)),     myform, SLOT(number_size_int_recieveData         (int)));
  connect(this, SIGNAL(first_int_Data               (int)),     myform, SLOT(first_int_recieveData               (int)));
  connect(this, SIGNAL(result_int_Data              (int)),     myform, SLOT(result_int_recieveData              (int)));
  connect(this, SIGNAL(n_int_Data                   (int)),     myform, SLOT(n_int_recieveData                   (int)));
  connect(this, SIGNAL(m_int_Data                   (int)),     myform, SLOT(m_int_recieveData                   (int)));
  connect(this, SIGNAL(mode_int_Data                (int)),     myform, SLOT(mode_int_recieveData                (int)));
  connect(this, SIGNAL(num_int_Data                 (int)),     myform, SLOT(num_int_recieveData                 (int)));
  connect(this, SIGNAL(equally_int_Data             (int)),     myform, SLOT(equally_int_recieveData             (int)));
  connect(this, SIGNAL(direction_int_Data           (int)),     myform, SLOT(direction_int_recieveData           (int)));
  connect(this, SIGNAL(zero_int_Data                (int)),     myform, SLOT(zero_int_recieveData                (int)));
  connect(this, SIGNAL(currentPath_Data             (QString)), myform, SLOT(currentPath_recieveData             (QString)));
  connect(this, SIGNAL(combinatorics_name_Path_Data (QString)), myform, SLOT(combinatorics_name_Path_recieveData (QString)));

  connect(ui->pushButtonA,  SIGNAL(clicked()),this,SLOT(Placements_without_repetition()));
  connect(ui->pushButton_A, SIGNAL(clicked()),this,SLOT(Placements_with_repetition()));
  connect(ui->pushButtonC,  SIGNAL(clicked()),this,SLOT(Combinations_without_repetition()));
  connect(ui->pushButton_C, SIGNAL(clicked()),this,SLOT(Combinations_with_repetition()));
  connect(ui->pushButtonP,  SIGNAL(clicked()),this,SLOT(Permutations_without_repetitions()));
  connect(ui->pushButton_P, SIGNAL(clicked()),this,SLOT(Permutations_with_repetitions()));
  connect(ui->pushButton_0, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_1, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_2, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_3, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_4, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_5, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_6, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_7, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_8, SIGNAL(clicked()),this,SLOT(creating_the_number()));
  connect(ui->pushButton_9, SIGNAL(clicked()),this,SLOT(creating_the_number()));

  qApp->installEventFilter(this); // Ловим все события

  adjustment();  // Вывод параметров
}

MainWindow::~MainWindow() { delete ui; }

// Комбинаторика
// Размещения без повторений
void MainWindow::Placements_without_repetition(){
  simplification_of_the_combinatorics();
  num = 1;
  ui->label_board->setText("   A");
  ui->label_board_->setVisible(false);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}
// Размещения с повторениями
void MainWindow::Placements_with_repetition(){
  simplification_of_the_combinatorics();
  num = 2;
  ui->label_board->setText("   A");
  ui->label_board_->setVisible(true);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}
// Сочетания без повторений
void MainWindow::Combinations_without_repetition(){
  simplification_of_the_combinatorics();
  num = 3;
  ui->label_board->setText("   C");
  ui->label_board_->setVisible(false);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}
// Сочетания с повторениями
void MainWindow::Combinations_with_repetition(){
  simplification_of_the_combinatorics();
  num = 4;
  ui->label_board->setText("   C");
  ui->label_board_->setVisible(true);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}
// Перестановки без повторений
void MainWindow::Permutations_without_repetitions(){
  simplification_of_the_combinatorics();
  num = 5;
  ui->label_board->setText("   P");
  ui->label_board_m->setText("");
  ui->label_board_->setVisible(false);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}
// Перестановки с повторениями
void MainWindow::Permutations_with_repetitions(){
  simplification_of_the_combinatorics();
  num = 6;
  ui->label_board->setText("   P");
  ui->label_board_m->setText("");
  ui->label_board_->setVisible(true);
  // Передача номера операции комбинаторики
  ui->spinBox_formula->setValue(num);
  emit formula_Data(num);
  secondwindow(); // Открыть окно
  adjustment(); // Вывод параметров
}

// Упростить операции комбинаторики
void MainWindow::simplification_of_the_combinatorics(){
  on_pushButton_AC_clicked();
  ui->label_board_n->setText("0");
  ui->label_board_m->setText("0");
  direction = 1;
  ui->label_info->setText("Введите n");
  operation_str = "A";
}

// n
void MainWindow::on_pushButton_n_clicked(){
  if(operation_str == "A"){
    direction = 1;
    ui->label_info->setText("Введите n");
    ui->label->setText("0");
  }
  adjustment(); // Вывод параметров 
}
// m
void MainWindow::on_pushButton_m_clicked(){
  if(operation_str == "A" && num != 5 && num !=6){
    direction = 2;
    ui->label_info->setText("Введите m");
    ui->label->setText("0");
  }
  if(num == 6){
    direction = 2;
    ui->label_info->setText("Через точку");
    ui->label->setText("0");
  }
  adjustment(); // Вывод параметров
}





// Все события приходят сюда
bool MainWindow::eventFilter(QObject *watched, QEvent *event){

  // Глобальные координаты окна
  xGCW = (this)->geometry().x(); // Координаты left-top главного окна приложения
  yGCW = (this)->geometry().y(); // Координаты left-top главного окна приложения

  // Отслеживаем события мыши
  if(event->type() == QEvent::MouseMove){
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

    xC = mouseEvent->x();        // Координаты курсора на теле виджета
    yC = mouseEvent->y();        // Координаты курсора на теле виджета
    xGC = mouseEvent->globalX(); // Глобальные координаты курсора
    yGC = mouseEvent->globalY(); // Глобальные координаты курсора

  }

  QObject::eventFilter(watched, event);
}





// Обработка событий нажатия клавиш
void MainWindow::keyPressEvent(QKeyEvent *event) {
  QTextCodec *russiancodec = QTextCodec::codecForName("Cp1251");            // Указал кодировку для коректного отображения букв
  QTextCodec::setCodecForLocale (russiancodec);

  //ui->label_key->setText(event->text());                                    // Отображаем наши события о нажатиях клавиш в (label_key)
  emit key_str_Data(ui->label_key->text());                                 // вызываем сигнал, в котором передаём данные в другое окно

  if (event->key() == Qt::Key_Enter) ui->pushButton_result->clicked();      // Enter     - Получение результата
  if (event->text() == '=') ui->pushButton_result->clicked();               // =         - Получение результата
  if (event->key() == Qt::Key_Return) ui->pushButton_result->clicked();     // Return    - Получение результата
  if (event->key() == Qt::Key_Delete) ui->pushButton_AC->clicked();         // Delete    - Обнуление
  if (event->key() == Qt::Key_Escape) close();                              // Escape    - Закрыть приложение
  if (event->key() == Qt::Key_Backspace) ui->pushButton_CE->clicked();      // Backspace - Частичное удаление
  if (event->key() == Qt::Key_Control) ui->pushButton_negation->clicked();  //
  if (event->text() == 'p') ui->pushButton_VP->clicked();
  if (event->text() == 'P') ui->pushButton_VP->clicked();
  if (event->text() == 'm') ui->pushButton_m->clicked();
  if (event->text() == 'M') ui->pushButton_m->clicked();
  if (event->text() == 'n') ui->pushButton_n->clicked();
  if (event->text() == 'N') ui->pushButton_n->clicked();
  if (event->text() == '.') ui->pushButton_point->clicked();
  if (event->text() == ',') ui->pushButton_point->clicked();
  if (event->text() == '+') ui->pushButton_plus->clicked();
  if (event->text() == '-') ui->pushButton_minus->clicked();
  if (event->text() == '*') ui->pushButton_multiply->clicked();
  if (event->text() == '/') ui->pushButton_share->clicked();
  if (event->text() == '!') ui->pushButton_factorial->clicked();
  if (event->text() == '^') ui->pushButton_degree->clicked();
  if (event->text() == 'w') ui->pushButton_RNU->clicked();
  if (event->text() == 'W') ui->pushButton_RNU->clicked();
  if (event->text() == 's') ui->pushButton_RND->clicked();
  if (event->text() == 'S') ui->pushButton_RND->clicked();
  if (event->text() == '0') ui->pushButton_0->clicked();
  if (event->text() == '1') ui->pushButton_1->clicked();
  if (event->text() == '2') ui->pushButton_2->clicked();
  if (event->text() == '3') ui->pushButton_3->clicked();
  if (event->text() == '4') ui->pushButton_4->clicked();
  if (event->text() == '5') ui->pushButton_5->clicked();
  if (event->text() == '6') ui->pushButton_6->clicked();
  if (event->text() == '7') ui->pushButton_7->clicked();
  if (event->text() == '8') ui->pushButton_8->clicked();
  if (event->text() == '9') ui->pushButton_9->clicked();
}



// Создание числа
void MainWindow::creating_the_number()
{
  // Ликвидация последствий вывода ошибки
  if (ui->label->text() == "Error") ui->label->setText("");
  ui->textBrowser->setText(""); // Отчистить поле больших чисел

  if (equally == 1 || mode == 2)on_pushButton_AC_clicked();      // Если после получения результата (в том числе Факториал) пользователь сразу ввёл цифру всё обнулится
  QPushButton *button = (QPushButton *)sender();                 // Указывает на нажатую кнопку
  // ////////////////////////////////////////////////////////////  // Ввод n (комбинаторика)
  if(operation_str == "A" && direction == 1){
    ui->label->setText("0");                                     // Если n > 999 в (label) выводится ошибка, этой операцией мы убираем сообщение об этой ошибке
    n = (ui->label_board_n->text() + button->text()).toDouble(); // Текущее число равно последовательности нажатых цифр (double)
    n_str = QString::number(n, 'g', 15);                         // Перепишим его как строку для последующего вывода в (label)
    ui->label_board_n->setText(n_str);                           // Вывод в (label)
    n = floor(n);                                                // Округлим до меньшего
    int_n = static_cast<int>(n);                                 // Переписать значение n (double) в n (int)
    itoa(int_n, n_char, 10);
    if (n > 999){                                                // Если n > 999
      reset_n();                                                 // Частичное удаление (обнулить n)
      ui->label_board_n->setText("0");
      ui->label->setText("Error");                               // Вывести сообщение об ошибке в (label)
    }
  }
  // ////////////////////////////////////////////////////////////  // Ввод m (комбинаторика)
  else if(operation_str == "A" && direction == 2  && num != 6){
    ui->label->setText("0");                                     // Если m > 999 в (label) выводится ошибка, этой операцией мы убираем сообщение об этой ошибке
    m = (ui->label_board_m->text() + button->text()).toDouble(); // Текущее число равно последовательности нажатых цифр
    m_str = QString::number(m, 'g', 15);                         // Перепишим его как строку для последующего вывода в (label)
    ui->label_board_m->setText(m_str);                           // Вывод в (label)
    m = floor(m);                                                // Округлим до меньшего
    int_m = static_cast<int>(m);                                 // Переписать значение m (double) в m (int)
    itoa(int_m, m_char, 10);
    if (m > 999){                                                // Если n > 999
      reset_m();                                                 // Частичное удаление (обнулить m)
      ui->label_board_m->setText("0");
      ui->label->setText("Error");                               // Вывести сообщение об ошибке в (label)
    }
  }
  // Ввод параметров при Перестановках с повторениями
  else if(operation_str == "A" && direction == 2  && num == 6){
    if (ui->label->text() == "0") ui->label->setText("");
    number_str = (ui->label->text() + button->text());
    ui->label->setText(number_str);
    number = number_str.toDouble();                                        // number (double) равен последовательности нажатых цифр
    ui->label->setText(number_str);                                        // Вывод number_str (QString) в (label)
    // В случае слишком длинного ввода
    if (number_str.size() > 16){
      on_pushButton_AC_clicked();                                          // Обнулить данные
      ui->label->setText("Error");                                         // Вывести сообщение об ошибке в (label)
    }
  }
  // ////////////////////////////////////////////////////////////  // Ввод number
  else{
    // Если введена цифра
    if (button->text() == '0' || button->text() == '1' || button->text() == '2' ||
        button->text() == '3' || button->text() == '4' || button->text() == '5' ||
        button->text() == '6' || button->text() == '7' || button->text() == '8' ||
        button->text() == '9') {
      // Если текущее число равно 0
      if (ui->label->text() == "0") ui->label->setText("");
      number_str = (ui->label->text() + button->text());
    }
    ui->label->setText(number_str);
    number = number_str.toDouble();                                        // number (double) равен последовательности нажатых цифр
    ui->label->setText(number_str);                                        // Вывод number_str (QString) в (label)

    // В случае слишком большого (малого) результата
    if (number > 999998846140417 || number < -999998846140417 || number_str.size() > 16){
      on_pushButton_AC_clicked();                                          // Обнулить данные
      ui->label->setText("Error");                                         // Вывести сообщение об ошибке в (label)
    }
  }
  // ////////////////////////////////////////////////////////////  //
  zero = 0;
  equally = 0;                                                   // Последним действием не было получение результата
  mode = 0;                                                      // Обнуление (Арифметические операции)
  adjustment();                                                  // Вывод параметров
}



// Точка
void MainWindow::on_pushButton_point_clicked(){
  // Ликвидация последствий вывода ошибки
  if (ui->label->text() == "Error") ui->label->setText("0");

  if (operation_str != "A" && mode != 10){
    if(!ui->label->text().contains('.')){
      ui->label->setText(ui->label->text() + ".");
      number_str = ui->label->text();
    }
  }
  if (operation_str == "A" && direction == 2  && num == 6){
    // Если предыдущий символ не был точкой
      if(number_str[number_str.size()-1] != '.')
    {
      number_of_points = 0;                                                                   // Обнуление кол-ва точек
      for(int i = 0; i < number_str.size(); i++) if(number_str[i] == '.') number_of_points++; // Подсчёт кол-ва точек
      // Допустимо только 4 точки
      if(number_of_points < 4) {
        ui->label->setText(ui->label->text() + ".");
        number_str = ui->label->text();
      }
    }
  }
  equally = 0;  // Последним действием не было получение результата
  adjustment(); // Вывод параметров
}





// ////////////////////////////////////////////// Операции с двумя числами ( + - * / )
// Операция сложения
void MainWindow::on_pushButton_plus_clicked(){
  if(operation_str != "A"){
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
  operation_str = "+";
  Arithmetic_simplification();
  }
}
// Операция вычитания и ввод отрицательных чисел
void MainWindow::on_pushButton_minus_clicked(){
  if(operation_str != "A"){
  if(operation_str != "A" && !ui->label->text().contains('-') && number == 0){
    mode = 10; // обозначение отрицания
    number_str = "";
    ui->label->setText(number_str);
    ui->label->setText(ui->label->text() + "-");
  }
  else {
    if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
    operation_str = "-";
    Arithmetic_simplification();
  }
  adjustment(); // Вывод параметров
  }
}
// Операция умножения
void MainWindow::on_pushButton_multiply_clicked(){
  if(operation_str != "A"){
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
  operation_str = "x";
  Arithmetic_simplification();
  }
}
// Операция деления
void MainWindow::on_pushButton_share_clicked(){
  if(operation_str != "A"){
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
  operation_str = "/";
  Arithmetic_simplification();
  }
}
// Операция Возведения в степень n
void MainWindow::on_pushButton_degree_clicked(){
  if(operation_str != "A"){
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
  operation_str = "^";
  Arithmetic_simplification();
  }
}
// Корень n степени
void MainWindow::on_pushButton_root_clicked(){
  if(operation_str != "A"){
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√") Arithmetic_simplification_2();
  operation_str = "√";
  Arithmetic_simplification();
  }
}
// Упрощение Арифетических операций (с двумя числами)
void MainWindow::Arithmetic_simplification(){
  ui->textBrowser->setText("");                // Отчистить поле больших чисел
  mode = 0;                                    // Номер операции
  zero = 0;
  if (equally == 1 ) number = result;          // Если после получения результата пользователь сразу ввёл операцию результат прошлой операции перепишется в первое число
  reset_second();                              // Обнулить second
  equally = 0;                                 // Последним действием не было получение результата
  if (number != 0) first = number;             // Сохранить первое число в переменной (first)
  first_str = QString::number(first, 'g', 15); // Перепишем первое число как строку для последующего вывода в (label_first)
  int_first = static_cast<int>(first);         // Переписать значение first (double) в int_first (int)
  ui->label_first->setText(first_str);         // Вывод первого числа в (label_first)
  ui->label_operation->setText(operation_str); // Вывод знака операции в (label_operation)
  ui->label_info->setText("");                 // Обнулить инфо поле
  number = 0;                                  // Обнулить общее число
  number_str = "";                             // Обнулить общее число
  ui->label->setText("0");                     // Обнулить главное поле (label)
  adjustment();                                // Вывод параметров
}
void MainWindow::Arithmetic_simplification_2(){
  on_pushButton_result_clicked();
  ui->textBrowser->setText(""); // Отчистить поле больших чисел
  first = number;
  int_first = static_cast<int>(first);
  first_str = QString::number(first, 'g', 15);
  reset_number();
}


// Операция нахождения факториала
void MainWindow::on_pushButton_factorial_clicked(){
  if(operation_str != "A"){
    operation_str = "!"; mode = 2;                 // Номер операции
    One_operation_simplification();                // Вывод начальных параметров и установка номера операции
    if (number > -1 && number < 256){
      if (first > 17 && first < 256) {
        number_str = factorial_test(number_str.toInt());
        ui->textBrowser->setText(number_str);
        ui->label->setText("");
      }
      if(first > -1 && first < 18){                  // Проверка на возможность проведения операции, double не всесилен максимум можно найти факториал 12
        first = floor(first);                        // Округление в сторону меньшего
        int_first = static_cast<int>(first);         // Переписать значение first (double) в int_first (int)
        first_str = factorial_test(int_first);       //
        first = first_str.toDouble();
        One_operation_simplification_2();            // Установка результата
      }
    }
    else{
      on_pushButton_AC_clicked();
      ui->label->setText("Error");
    }
  }
  adjustment();                                     // Вывод параметров
}
// Возведение в квадрат
void MainWindow::on_pushButton_degree_2_clicked(){
  if(operation_str != "A"){
    operation_str = "^2"; mode = 3;             //
    One_operation_simplification();             //
    first = first*first;                        //
    One_operation_simplification_2();           //
  }
}
// Нахождение квадратного корня
void MainWindow::on_pushButton_root_2_clicked(){
  if(operation_str != "A"){
    operation_str = ""; mode = 3;               //
    One_operation_simplification();             //
    second = 2;
    first = qPow (first, 1/second);             //
    One_operation_simplification_2();           //
  }
}
// Операция округления числа до большего целого (инкремент)
void MainWindow::on_pushButton_RNU_clicked(){
  if(operation_str != "A"){
  operation_str = "↑"; mode = 3;                 // Номер операции
  One_operation_simplification();                // Вывод начальных параметров и установка номера операции
  first = floor(first)+1;                        // Округление в сторону большего
  One_operation_simplification_2();              // Установка результата
}
}
// Операция округления числа до меньшего целого (декремент)
void MainWindow::on_pushButton_RND_clicked(){
  if(operation_str != "A"){
  operation_str = "↓"; mode = 3;                 // Номер операции
  One_operation_simplification();               // Вывод начальных параметров и установка номера операции
  first = ceil(first)-1;                        // Округление в сторону меньшего
  One_operation_simplification_2();             // Установка результата
}
}
// Операция инверсии
void MainWindow::on_pushButton_negation_clicked(){
  if (operation_str != "A" && number != 0){
    number = number * -1;
    result = number;
    number_str = QString::number(number, 'g', 15);
    result_str = number_str;
    ui->label->setText(number_str);
    adjustment();
  }
}
// Упростить операции с одним числом
void MainWindow::One_operation_simplification(){
  equally = 0;                                                           // Последним действием не было получение результата
  first = number;                                                        // Первое число равно введённому в поле ввода (label)
  first_str = QString::number(first, 'g', 15);                           // Перепишем первое число как строку для последующего вывода в (label_first)
  ui->label_first->setText(first_str);                                   // Вывод первого числа в (label_first)
  ui->label_operation->setText(operation_str);                           // Вывод знака операции в (label_operation)
  reset_second();
}
void MainWindow::One_operation_simplification_2(){
  ui->textBrowser->setText(""); // Отчистить поле больших чисел
  first_str = QString::number(first, 'g', 15);                           // Перепишем первое число как строку для последующего вывода в (label_first)
  ui->label->setText(first_str);                                         // Вывод первого числа в (label_first)
  number = first;                                                        // Перепишем в общее число(number) значение результата
  number_str = QString::number(number, 'g', 15);                         // Перепишим его как строку для последующего вывода в (label)
  int_first = static_cast<int>(first);
  result = first;
  int_result = static_cast<int>(result);                                 // Переписать значение result (double) в int_result (int)
  result_str = QString::number(result, 'g', 15);                         // Переписать значение result (double) в result_str (QString)
  ui->label_info->setText("");                                           // Обнулить инфо поле
  if (number > 999998846140417 || number < -999998846140417){            // Накладываем ограничение макс - 16 разрядов
    on_pushButton_AC_clicked();                                          // Обнулить данные
    ui->label->setText("Error");                                         // Вывести сообщение об ошибке в (label)
  }
  zero = 0;
  adjustment();                                                          // Вывод параметров
}



// Операция Получения результата
void MainWindow::on_pushButton_result_clicked(){

  ui->textBrowser->setText(""); // Отчистить поле больших чисел
  // Работа над вторым числом
  if (operation_str != "A") {
    second = number;                                                                                         // Сохранить второе число в переменной (second)
    second_str = QString::number(second, 'g', 15);                                                           // Перепишем второе число как строку для последующего вывода в (label_second)
    ui->label_second->setText(second_str);                                                                   // Вывод первого числа в (label_second)
  }

  // Работа с арифметическими операциями
  if(operation_str == "+" || operation_str == "-" || operation_str == "x" || operation_str == "/" || operation_str == "^" || operation_str == "√"){
    // Сложение
    if (operation_str == "+") {
      result = first + second;
    }
    // Вычитание
    if (operation_str == "-") {
      result = first - second;
    }
    // Умножение
    if (operation_str == "x") {
      result = first * second;
    }
    // Возведение в степень
    if (operation_str == "^") {
      result = qPow (first, second);
    }
    // Корень n степени
    if (operation_str == "√") {
      result = qPow (first, 1/second);
    }
    // Деление
    if (operation_str == "/"){
      if (second > 0.0000000000001 || second < -0.0000000000001) {
        result = first / second;
      }
      // При делении на 0
      else{
        error = 1;
      }
    }
  }

  // Работа с операциями комбинаторики
  if (operation_str == "A"){
    itoa(num, num_char, 10); // Приведём номер операции к передаче

    // Размещения без повторений
    if (num == 1){
      if (int_n >= int_m){
        if(int_n < 13 && int_m < 13) {
          int_result = factorial(int_n) / factorial(int_n - int_m);
        }
        else other_application(); // Вызов приложения для больших чисел
      }
      else {
        reset_n();
        reset_m();
        error = 1;
      }
    }
    // Размещение с повторением
    if (num == 2) {      
      int_result = qPow (int_n, int_m);
      if (int_result < 0){
        int_result = 0;
        other_application(); // Вызов приложения для больших чисел
      }
    }
    // Сочетание без повторений
    if (num == 3){
      if (int_n < 13 && int_m < 13){
        int_result = factorial(int_n) / (factorial(int_n - int_m) * factorial(int_m));
      }
      else other_application(); // Вызов приложения для больших чисел
    }
    // Сочетания с повторениями
    if (num == 4){
      if (int_n < 13 && int_m < 13 && (int_n + int_m < 14)){
        int_result = factorial((int_n + int_m) - 1) / (factorial(int_n - 1) * factorial(int_m));
      }
      else other_application(); // Вызов приложения для больших чисел
    }
    // Перестановки без повторений
    if (num == 5){
      if (n > 0 && n <13) int_result = factorial(int_n);
      else {
        char *args[] = {combinatorics_name_char, num_char, n_char, 0};
        _chdir (currentPath_char);
        spawnv(P_WAIT,args[0], args);
        on_pushButton_AC_clicked();
      }
    }
    // Перестановки с повторениями
    if (num == 6){
      // Перебираем все символы строки в поиске индексов точек
      int j = 0;
      for(int i = 0; i < number_str.size(); i++){
        // "." сплиттер - находим индексы точек
        if(number_str[i] == '.'){
          if (j == 0) t[0] = i;
          if (j == 1) t[1] = i;
          if (j == 2) t[2] = i;
          if (j == 3) t[3] = i;
          j++;
      }
    }
    // Переписываем значения между точек, каждое в отдельную переменную
    for(int i = 0; i < t[0]; i++) p1_str.append(number_str.at(i));
    for(int i = t[0]+1; i < t[1]; i++) p2_str.append(number_str.at(i));
    for(int i = t[1]+1; i < t[2]; i++) p3_str.append(number_str.at(i));
    for(int i = t[2]+1; i < t[3]; i++) p4_str.append(number_str.at(i));
    for(int i = t[3]+1; i < number_str.size(); i++) p5_str.append(number_str.at(i));
    // Конвертируем в Char
    strcpy(p1_char, p1_str.toUtf8().data());
    strcpy(p2_char, p2_str.toUtf8().data());
    strcpy(p3_char, p3_str.toUtf8().data());
    strcpy(p4_char, p4_str.toUtf8().data());
    strcpy(p5_char, p5_str.toUtf8().data());
    // Вызываем приложение для расчёта
    char *args[] = {combinatorics_name_char, num_char, n_char,p1_char,p2_char,p3_char,p4_char,p5_char, 0};
    _chdir (currentPath_char);
    spawnv(P_WAIT,args[0], args);
    on_pushButton_AC_clicked();
    }
    result = static_cast<double>(int_result);                                                                // Переписать значение int_result (int) в result (double)
    adjustment();
  }

  if (operation_str == "") on_pushButton_AC_clicked();                                                       // Обнулить если не выбрана операция и нажата кнопка равно

  operation_str = "";                                                                                        // Порядок власть имущих переменных
  int_first = static_cast<int>(first);                                                                       // Переписать значение first (double) в int_first (int)
  int_result = static_cast<int>(result);                                                                     // Переписать значение result (double) в int_result (int)
  result_str = QString::number(result, 'g', 14);                                                             // Переписать значение result (double) в result_str (QString)
  number = result;                                                                                           // Переписать значение result (double) в number (double)
  number_str = QString::number(number, 'g', 14);                                                             // Переписать значение number (double) в number_str (QString)
  ui->label->setText(number_str);                                                                            // Вывод результата (number_str) в (label)
  ui->label_info->setText("");                                                                               // Обнулить инфо поле (label_info)
  equally = 1;                                                                                               // Последним действием было получение результата
  // В случае слишком большого результата или деления на 0
  if (number > 999998846140417 || number < -999998846140417 || error == 1 || number_str.size() > 16){        //
    on_pushButton_AC_clicked();                                                                              // Обнулить данные
    ui->label->setText("Error");                                                                             // Вывести сообщение об ошибке в (label)
  }
  adjustment();                                                                                              // Вывод параметров
}



// Обнулить переменные
void MainWindow::on_pushButton_AC_clicked()
{
  if(operation_str != 'A') emit close_Data(1); // Передача приказа о закрытии

  num = 0;               // Обнулить Номер операции комбинаторики
  mode = 0;              // Обнулить Номер операции
  equally = 0;           // Обнулить Операция получения результата
  direction = 0;         // Обнулить Направление
  error = 0;
  data_output = 0;       // Вывод информации только один раз
  zero = 0;
  number_of_points = 0;  // Обнулить кол-во точек

  reset_number();        // Обнулить number
  reset_first();         // Обнулить first
  reset_second();        // Обнулить second
  reset_result();        // Обнулить result
  reset_n();             // Обнулить n
  reset_m();             // Обнулить m
  reset_operation_str(); // Обнулить operation_str

  ui->label_board_->setVisible(false);
  ui->label_board->setText("   A");
  ui->label_info->setText("");

  // Перестановки с повторениями
  reset_t();      // Обнулить t (хранит индекс точек)
  reset_p_str();  // Обнулить  p_str (хранит значения между точек)
  reset_p_char(); // Обнулить  p_char (хранит значения между точек)

  ui->textBrowser->setText(""); // Отчистить поле больших чисел

  adjustment();                               // Вывод параметров
}
// Обнулить number
void MainWindow::reset_number(){
  number = 0;                                 // Обнулить общее число
  number_str = "";                            // Обнулить общее число
  ui->label->setText("0");                    // Обнулить главное поле (label)
}
// Обнулить first
void MainWindow::reset_first(){
  first = 0;                                  // Обнулить первое число
  int_first = 0;                              // Обнулить первое число
  first_str = "";                             // Обнулить первое число
  ui->label_first->setText("");               // Обнулить поле (label_first)
}
// Обнулить second
void MainWindow::reset_second(){
  second = 0;                                 // Обнулить второе число
  second_str = "";                            // Обнулить второе число
  ui->label_second->setText("");              // Обнулить поле (label_second)
}
// Обнулить n
void MainWindow::reset_n(){
  n = 0;                                      // Обнулить n
  int_n = 0;                                  // Обнулить n
  n_str = "";                                 // Обнулить n
  ui->label_board_n->setText("n");            // Обнулить поле (label_board_n)
  for (int i = 0; i < 4; i++) n_char[i] = '0';
}
// Обнулить m
void MainWindow::reset_m(){
  m = 0;                                      // Обнулить m
  int_m = 0;                                  // Обнулить m
  m_str = "";                                 // Обнулить m
  ui->label_board_m->setText("m");            // Обнулить поле (label_board_m)
  for (int i = 0; i < 4; i++) m_char[i] = '0';
}
// Обнулить result
void MainWindow::reset_result(){
  result = 0;                                 // Обнулить результат
  int_result = 0;                             // Обнулить результат
  result_str = "0";                           // Обнулить результат
}
// Обнулить operation_str
void MainWindow::reset_operation_str(){
  operation_str = "";                         // Обнулить знак операции operation_str (double)
  ui->label_operation->setText("");           // Обнулить знак операции (label_operation)
}
// Обнулить t (хранит индекс точек)
void MainWindow::reset_t(){
  for (int i = 0; i < 255; i++) t[i] = 0;
  ui->spinBox_t0->setValue(0);
  ui->spinBox_t1->setValue(0);
  ui->spinBox_t2->setValue(0);
  ui->spinBox_t3->setValue(0);
}
// Обнулить  p_str (хранит значения между точек)
void MainWindow::reset_p_str(){
  p1_str = "";
  p2_str = "";
  p3_str = "";
  p4_str = "";
  p5_str = "";
  ui->label_p1->setText("");
  ui->label_p2->setText("");
  ui->label_p3->setText("");
  ui->label_p4->setText("");
  ui->label_p5->setText("");
}
// Обнулить  p_char (хранит значения между точек)
void MainWindow::reset_p_char(){
  for(int i = 0; i < 255; i++) p1_char[i] = '0';
  for(int i = 0; i < 255; i++) p2_char[i] = '0';
  for(int i = 0; i < 255; i++) p3_char[i] = '0';
  for(int i = 0; i < 255; i++) p4_char[i] = '0';
  for(int i = 0; i < 255; i++) p5_char[i] = '0';
}


// Частичное удаление
void MainWindow::on_pushButton_CE_clicked(){
  if (direction == 0){
    number_str.chop(1);
    number = number_str.toDouble();
    ui->label->setText(number_str);

    if(mode != 0 || equally == 1){
      reset_first();         // Обнулить first
      reset_operation_str(); // Обнулить operation_str
    }

    reset_second();        // Обнулить second
    reset_result();        // Обнулить result

    if (number_str.size() == 0){
      ui->label->setText("0");
      zero++;
      if (zero == 2) on_pushButton_AC_clicked();
    }
  }

  if(direction == 1) {
    ui->label->setText("0");
    n_str.chop(1);
    n = n_str.toDouble();
    int_n = static_cast<int>(n);
    ui->label_board_n->setText(n_str);
    if (n_str.size() == 0) ui->label_board_n->setText("0");
  }
  if(direction == 2 && num != 6) {
    ui->label->setText("0");
    m_str.chop(1);
    m = m_str.toDouble();
    int_m = static_cast<int>(m);
    ui->label_board_m->setText(m_str);
    if (m_str.size() == 0) ui->label_board_m->setText("0");
  }
  // Перестановки с повторениями
  if(direction == 2 && num == 6) {
    number_str.chop(1);
    number = number_str.toDouble();
    ui->label->setText(number_str);
    if(number_str == "") ui->label->setText("0");
  }
  equally = 0;  // Последним действием не было получение результата
  adjustment(); // Вывод параметров
}


// Функция вычисления факториала
int MainWindow::factorial(int i){
  int n = 1;
  for(int a = 2; a <= i; a++)
    n*=a;
  return n;
}


// Пуско-Наладка
void MainWindow::adjustment(){
  // Установка параметров в текщей форме
  ui->spinBox_int_result->setValue(int_result);
  ui->doubleSpinBox_result->setValue(result);
  ui->label_result_str->setText(result_str);
  ui->spinBox_int_n->setValue(int_n);
  ui->doubleSpinBox_n->setValue(n);
  ui->label_n_str->setText(n_str);
  ui->label_n_char->setText(n_char);
  ui->spinBox_int_m->setValue(int_m);
  ui->doubleSpinBox_m->setValue(m);
  ui->label_m_str->setText(m_str);
  ui->label_m_char->setText(m_char);
  ui->spinBox_int_first->setValue(int_first);
  ui->doubleSpinBox_first->setValue(first);
  ui->label_first_str->setText(first_str);
  ui->doubleSpinBox_second->setValue(second);
  ui->label_second_str->setText(second_str);
  number_size = number_str.size();
  ui->doubleSpinBox_number->setValue(number);
  ui->label_number_str->setText(number_str);
  ui->spinBox_number_size->setValue(number_size);
  ui->spinBox_num->setValue(num);
  ui->spinBox_mode->setValue(mode);
  ui->spinBox_equally->setValue(equally);
  ui->spinBox_direction->setValue(direction);
  ui->spinBox_int_m->setValue(int_m);
  ui->doubleSpinBox_result->setValue(result);
  ui->doubleSpinBox_n->setValue(n);
  ui->doubleSpinBox_m->setValue(m);
  ui->doubleSpinBox_first->setValue(first);
  ui->doubleSpinBox_second->setValue(second);
  ui->doubleSpinBox_number->setValue(number);
  ui->label_operation_str->setText(operation_str);
  ui->spinBox_zero->setValue(zero);
  // Перестановки с повторениями
  ui->label_p1->setText(p1_str);
  ui->label_p2->setText(p2_str);
  ui->label_p3->setText(p3_str);
  ui->label_p4->setText(p4_str);
  ui->label_p5->setText(p5_str);
  ui->spinBox_t0->setValue(t[0]);
  ui->spinBox_t1->setValue(t[1]);
  ui->spinBox_t2->setValue(t[2]);
  ui->spinBox_t3->setValue(t[3]);
  // Подготовка для передачи параметров другой форме
  emit number_str_Data    (ui->label_number_str->text());
  emit first_str_Data     (ui->label_first_str->text());
  emit second_str_Data    (ui->label_second_str->text());
  emit result_str_Data    (ui->label_result_str->text());
  emit n_str_Data         (ui->label_n_str->text());
  emit m_str_Data         (ui->label_m_str->text());
  emit operation_str_Data (ui->label_operation_str->text());
  emit key_str_Data       (ui->label_key->text());
  emit p1_str_Data(p1_str);     // Перестановки с повторениями
  emit p2_str_Data(p2_str);     // Перестановки с повторениями
  emit p3_str_Data(p3_str);     // Перестановки с повторениями
  emit p4_str_Data(p4_str);     // Перестановки с повторениями
  emit p5_str_Data(p5_str);     // Перестановки с повторениями
  emit t0_int_Data(t[0]);       // Перестановки с повторениями
  emit t1_int_Data(t[1]);       // Перестановки с повторениями
  emit t2_int_Data(t[2]);       // Перестановки с повторениями
  emit t3_int_Data(t[3]);       // Перестановки с повторениями
  emit n_char_Data(ui->label_n_char->text());
  emit m_char_Data(ui->label_m_char->text());
  emit number_double_Data(ui->doubleSpinBox_number->value());
  emit first_double_Data(ui->doubleSpinBox_first->value());
  emit second_double_Data(ui->doubleSpinBox_second->value());
  emit result_double_Data(ui->doubleSpinBox_result->value());
  emit n_double_Data(ui->doubleSpinBox_n->value());
  emit m_double_Data(ui->doubleSpinBox_m->value());
  emit number_size_int_Data(ui->spinBox_number_size->value());
  emit first_int_Data(ui->spinBox_int_first->value());
  emit result_int_Data(ui->spinBox_int_result->value());
  emit n_int_Data(ui->spinBox_int_n->value());
  emit m_int_Data(ui->spinBox_int_m->value());
  emit mode_int_Data(ui->spinBox_mode->value());
  emit num_int_Data(ui->spinBox_num->value());
  emit equally_int_Data(ui->spinBox_equally->value());
  emit direction_int_Data(ui->spinBox_direction->value());
  emit zero_int_Data(ui->spinBox_zero->value());
  emit currentPath_Data(ui->label_currentPath->text());
  emit combinatorics_name_Path_Data(ui->label_combinatorics_name->text());
}


// Пуско-Наладка
void MainWindow::on_pushButton_clicked(){

}


// Находим Факториал n и записываем значение в строку
QString MainWindow::factorial_test(int n){
  int res[512];
  int carry = 0;
  int resSize;
  QString str;
  if (n < 256 && n >= 0) {
    for (int i = 0; i < 512; i++) res[i] = 0;
    res[0] = 1;
    resSize = 1;
    for(int x = 2;x<=n;x++){
      for(int i=0; i<resSize; i++) {
        int prod = res[i]*x+carry;
        res[i]= prod % 10;
        carry = prod/10;
      }
      while(carry) {
        res[resSize]= carry % 10;
        carry = carry/10;
        resSize++;
      }
    }
    str = bigLine(res);
    return str;
  }
}
// Преобразуем массив int I[512] в строку
QString MainWindow::bigLine(int I[512]){
  double d;
  QString str;
  QString result_str = "";
  // Перепишем значение из массива I[512] (int) в строку str (QString)
  for (int i = 512; i > 0; i--){
    d = static_cast<double>(I[i-1]);
    str = str.append(QString::number(d, 'g'));
  }
  // Отсеем нули
  for(int i = 0, j = 0; i < 512; i++){
    if (str[i] != "0") j++;
    if (str[i] == "0" && j == 0) str[i] = ' ';
  }
  // Избавимся от пустых символов
  for(int i = 0; i < 512; i++) if (str[i] != ' ') result_str.append(str[i]);
  return result_str;
}


// Пролистать влево результат
void MainWindow::on_pushButton_left_clicked(){

}
// Пролистать вправо результат
void MainWindow::on_pushButton_right_clicked(){

}


// Вызов окна для вывода формулы
void MainWindow::secondwindow(){
  emit xC_int_Data(xC); emit yC_int_Data(yC);
  emit xGC_int_Data(xGC); emit yGC_int_Data(yGC);
  emit xGCW_int_Data(xGCW); emit yGCW_int_Data(yGCW);
  window->show();
}
 // Формула Бернулли
void MainWindow::on_pushButton_bernoulle_clicked(){
  emit xC_int_B_Data(xC); emit yC_int_B_Data(yC);
  emit xGC_int_B_Data(xGC); emit yGC_int_B_Data(yGC);
  emit xGCW_int_B_Data(xGCW); emit yGCW_int_B_Data(yGCW);
  twoform->show();
}
// Полиномиальная Формула
void MainWindow::on_pushButton_polynomial_clicked(){
  emit xC_int_Po_Data(xC); emit yC_int_Po_Data(yC);
  emit xGC_int_Po_Data(xGC); emit yGC_int_Po_Data(yGC);
  emit xGCW_int_Po_Data(xGCW); emit yGCW_int_Po_Data(yGCW);
  zibenform->show();
}
// Формула Пуассона
void MainWindow::on_pushButton_poisson_clicked(){
  emit xC_int_Py_Data(xC); emit yC_int_Py_Data(yC);
  emit xGC_int_Py_Data(xGC); emit yGC_int_Py_Data(yGC);
  emit xGCW_int_Py_Data(xGCW); emit yGCW_int_Py_Data(yGCW);
  ailform->show();
}
// Вызов приложения для расчёта комбинаторики
void MainWindow::other_application(){
  char *args[] = {combinatorics_name_char, num_char, n_char, m_char,  0};
  _chdir (currentPath_char);
  spawnv(P_WAIT,args[0], args);
  on_pushButton_AC_clicked();
}
// Вызов программы 1 лабы
void MainWindow::on_pushButton_tasks_clicked(){
  char *args[] = {tasks_name_char,  0};
  _chdir (currentPath_char);
  spawnv(P_WAIT,args[0], args);
  adjustment();
}
// Вызов программы 2 лабы
void MainWindow::on_pushButton_tasks_2_clicked(){
  char *args[] = {laba2_name_char,  0};
  _chdir (currentPath_char);
  spawnv(P_WAIT,args[0], args);
  adjustment();
}
// Вызов программы 3 лабы
void MainWindow::on_pushButton_tasks_3_clicked(){
  char *args[] = {laba3_name_char,  0};
  _chdir (currentPath_char);
  spawnv(P_WAIT,args[0], args);
  adjustment();
}
// Вызов программы 4 лабы
void MainWindow::on_pushButton_tasks_4_clicked(){
  lulyform->show();
}
// Вызов программы 5 лабы
void MainWindow::on_pushButton_tasks_5_clicked(){
  aits->show();
}

/*
Злобный повар Константин в пищу подложил стрихнин.
Очень вкусный был обед – дверь открылась на тот свет.
Трупы кучами лежат, человек сто пятьдесят.
Аппетитный был стрихнин, в нем – бесценный витамин!
*/


