#include "mychart.h"
#include "ui_mychart.h"
#include <qmath.h>

#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QChartView>

MyChart::MyChart(QWidget *parent) : QMainWindow(parent), ui(new Ui::MyChart) {
  ui->setupUi(this);

  count = 3;
  ui->spinBox_count->setValue(count);
  on_spinBox_count_valueChanged(count);
  on_pushButton_chart_1_clicked();
}

MyChart::~MyChart() { delete ui; }



// Установка графика 1
void MyChart::on_pushButton_chart_1_clicked(){
  // Создаём график
  chrt = new QChart;
  // кривые, отображаемые на графике
  // график координатных прямых
  QLineSeries* series1 = new QLineSeries();
  // кривая 1-го графика
  QLineSeries* series2 = new QLineSeries();
  // куча маленьких кривых образующих 2-й график
  QLineSeries* series11 = new QLineSeries();
  QLineSeries* series12 = new QLineSeries();
  QLineSeries* series13 = new QLineSeries();
  QLineSeries* series14 = new QLineSeries();
  QLineSeries* series15 = new QLineSeries();
  QLineSeries* series16 = new QLineSeries();
  QLineSeries* series17 = new QLineSeries();
  QLineSeries* series18 = new QLineSeries();
  QLineSeries* series19 = new QLineSeries();
  QLineSeries* series20 = new QLineSeries();
  QLineSeries* series21 = new QLineSeries();

  // связь графика с элементом отображения
  ui->vchrt->setChart(chrt);
  // Стиь графика в целом
  QFont font;
  font.setPixelSize(18);
  chrt->setTitleFont(font);
  chrt->setTitleBrush(QBrush(Qt::black));
  chrt->setTitle("график");
  // Стиль 2-го графика
  QPen pen2(QRgb(0x8e3975));
  pen2.setWidth(4);
  series2->setPen(pen2);
  series11->setPen(pen2);
  series12->setPen(pen2);
  series13->setPen(pen2);
  series14->setPen(pen2);
  series15->setPen(pen2);
  series16->setPen(pen2);
  series17->setPen(pen2);
  series18->setPen(pen2);
  series19->setPen(pen2);
  series20->setPen(pen2);
  series21->setPen(pen2);
  // Анимация графика
  chrt->setAnimationOptions(QChart::AllAnimations);
  // ось Х
  QValueAxis *axisX = new QValueAxis;
  axisX->setRange(-10, 10); // диапазон значений на оси
  axisX->setTickCount(21); // число линий сетки
  axisX->setLabelFormat("%.2f"); // формат отображения чисел на оси
  // ось Y
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(0, 1);
  axisY->setTickCount(11);
  axisY->setLabelFormat("%g");

  // Построение Многоугольника распределения
  if(ui->radioButton_1->isChecked()){
    chrt->setTitle("Многоугольник распределения");
    for(int i = 0; i<count; i++) {
      series2->append(x1[i], p[i]);
    }
  }
// Построение Функции распределения F(x)
  if(ui->radioButton_2->isChecked()){
    chrt->setTitle("Функция распределения F(x)");
    for(int i = count; i < 10; i++) x1[i] = x1[count-1];
      series11->append(-10,   0);
      series11->append(x1[0], 0);
      series12->append(x1[0], p[0]);
      series12->append(x1[1], p[0]);
      series13->append(x1[1], p[0]+p[1]);
      series13->append(x1[2], p[0]+p[1]);
      series14->append(x1[2], p[0]+p[1]+p[2]);
      series14->append(x1[3], p[0]+p[1]+p[2]);
      series15->append(x1[3], p[0]+p[1]+p[2]+p[3]);
      series15->append(x1[4], p[0]+p[1]+p[2]+p[3]);
      series16->append(x1[4], p[0]+p[1]+p[2]+p[3]+p[4]);
      series16->append(x1[5], p[0]+p[1]+p[2]+p[3]+p[4]);
      series17->append(x1[5], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]);
      series17->append(x1[6], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]);
      series18->append(x1[6], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]);
      series18->append(x1[7], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]);
      series19->append(x1[7], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]);
      series19->append(x1[8], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]);
      series20->append(x1[8], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]);
      series20->append(x1[9], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]);
      series21->append(x1[8], p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]);
      series21->append(10,    p[0]+p[1]+p[2]+p[3]+p[4]+p[5]+p[6]+p[7]+p[8]+p[9]);
  }
  // связываем график с построенными кривыми
  chrt->addSeries(series1);
  chrt->addSeries(series2);
  chrt->addSeries(series11);
  chrt->addSeries(series12);
  chrt->addSeries(series13);
  chrt->addSeries(series14);
  chrt->addSeries(series15);
  chrt->addSeries(series16);
  chrt->addSeries(series17);
  chrt->addSeries(series18);
  chrt->addSeries(series19);
  chrt->addSeries(series20);
  chrt->addSeries(series21);

  // устанавливаем оси для каждого графика
  chrt->setAxisX(axisX, series1);  chrt->setAxisY(axisY, series1);
  chrt->setAxisX(axisX, series2);  chrt->setAxisY(axisY, series2);
  chrt->setAxisX(axisX, series11); chrt->setAxisY(axisY, series11);
  chrt->setAxisX(axisX, series12); chrt->setAxisY(axisY, series12);
  chrt->setAxisX(axisX, series13); chrt->setAxisY(axisY, series13);
  chrt->setAxisX(axisX, series14); chrt->setAxisY(axisY, series14);
  chrt->setAxisX(axisX, series15); chrt->setAxisY(axisY, series15);
  chrt->setAxisX(axisX, series16); chrt->setAxisY(axisY, series16);
  chrt->setAxisX(axisX, series17); chrt->setAxisY(axisY, series17);
  chrt->setAxisX(axisX, series18); chrt->setAxisY(axisY, series18);
  chrt->setAxisX(axisX, series19); chrt->setAxisY(axisY, series19);
  chrt->setAxisX(axisX, series20); chrt->setAxisY(axisY, series20);
  chrt->setAxisX(axisX, series21); chrt->setAxisY(axisY, series21);

  chrt->legend()->hide();

  // Удаляем поебень на графике
  chrt->legend()->hide();
}



// Решение
void MyChart::on_pushButton_solution_clicked(){
  // 1 задача
  if(ui->radioButton_3->isChecked()){
    resettingData(); // Сброс данных
    saveData();      // Сохранение данных
    ui->label_info->setText("info");
    // Проверка на корректность
    for(int i = 0; i < 10; i++) sum = sum + p[i];
    if(sum <= 0.99 || sum >= 1.01) error = 1;
    // Математическое ожидание
    for(int i = 0; i < count; i++) Mx = Mx + (x1[i]*p[i]);
    // Дисперсия
    for(int i = 0; i < count; i++) Mx2 = Mx2 + (pow(x1[i],2) * p[i]);
    Dx = Mx2 - pow(Mx,2);
    // Среднее квадратичное отклонение
    Bx = pow(Dx,0.5);
    // Функция распределения
    Mx_str = "(";
    Fx_str[0] = "0 при x <= ";
    Fx_str[0] = Fx_str[0].append(QString::number(x1[0], 'g', 5));
    for (int i = 1, j = 2; i < count; i++, j+=2){
      P = P+p[i-1];
      Fx_str[i] = Fx_str[i].append(QString::number(P, 'g', 5));
      Fx_str[i] = Fx_str[i].append(" при ");
      Fx_str[i] = Fx_str[i].append(QString::number(x1[i-1], 'g', 5));
      Fx_str[i] = Fx_str[i].append(" < x <= ");
      Fx_str[i] = Fx_str[i].append(QString::number(x1[i], 'g', 5));
    }
    Fx_str[count] = "1 при x > ";
    Fx_str[count] = Fx_str[count].append(QString::number(x1[count-1], 'g', 5));
    // Установка Данных
    if(error == 0){
      setData();
    }
    if(error == 1){
      resettingData();
      setData();
      ui->label_info->setText("Error");
    }
  }

  // 2 задача
  if(ui->radioButton_4->isChecked()){
    resettingData(); // Сброс данных
    saveData();      // Сохранение данных
    ui->label_info->setText("info");
    // Расчёт вероятностей по формуле Пуассона
    lambda = ui->doubleSpinBox->value();
    for(int i = 0; i < count; i++){
    p[i] = poisson(x1[i], lambda);
    }
    // Математическое ожидание
    for(int i = 0; i < count; i++) Mx = Mx + (x1[i]*p[i]);
    // Дисперсия
    for(int i = 0; i < count; i++) Mx2 = Mx2 + (pow(x1[i],2) * p[i]);
    Dx = Mx2 - pow(Mx,2);
    // Среднее квадратичное отклонение
    Bx = pow(Dx,0.5);
    // Функция распределения
    Mx_str = "(";
    Fx_str[0] = "0 при x <= ";
    Fx_str[0] = Fx_str[0].append(QString::number(x1[0], 'g', 3));
    for (int i = 1, j = 2; i < count; i++, j+=2){
      P = P+p[i-1];
      Fx_str[i] = Fx_str[i].append(QString::number(P, 'g', 3));
      Fx_str[i] = Fx_str[i].append(" при ");
      Fx_str[i] = Fx_str[i].append(QString::number(x1[i-1], 'g', 3));
      Fx_str[i] = Fx_str[i].append(" < x <= ");
      Fx_str[i] = Fx_str[i].append(QString::number(x1[i], 'g', 3));
    }
    Fx_str[count] = "1 при x > ";
    Fx_str[count] = Fx_str[count].append(QString::number(x1[count-1], 'g', 3));
    // Установка Данных
    setData();
  }
}



// Обработка изменения значения кол-ва элементов
void MyChart::on_spinBox_count_valueChanged(int arg1){
  count = arg1;
  saveData();
  ui->label_info->setText("info");

  for(int i = count; i < 10; i++){
    x1[i] = 0;
    p[i] = 0;
  }
  if(arg1 == 1){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(0); ui->spinBox_3->setVisible(0); ui->spinBox_4->setVisible(0); ui->spinBox_5->setVisible(0);
    ui->spinBox_6->setVisible(0); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(0); ui->doubleSpinBox_3->setVisible(0); ui->doubleSpinBox_4->setVisible(0);
    ui->doubleSpinBox_5->setVisible(0); ui->doubleSpinBox_6->setVisible(0); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 2){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(0); ui->spinBox_4->setVisible(0); ui->spinBox_5->setVisible(0);
    ui->spinBox_6->setVisible(0); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(0); ui->doubleSpinBox_4->setVisible(0);
    ui->doubleSpinBox_5->setVisible(0); ui->doubleSpinBox_6->setVisible(0); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 3){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1);  ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(0); ui->spinBox_5->setVisible(0);
    ui->spinBox_6->setVisible(0); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(0);
    ui->doubleSpinBox_5->setVisible(0); ui->doubleSpinBox_6->setVisible(0); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 4){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(0);
    ui->spinBox_6->setVisible(0); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(0); ui->doubleSpinBox_6->setVisible(0); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 5){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(0); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(0); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 6){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(1); ui->spinBox_7->setVisible(0); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(1); ui->doubleSpinBox_7->setVisible(0); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 7){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(1); ui->spinBox_7->setVisible(1); ui->spinBox_8->setVisible(0); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(1); ui->doubleSpinBox_7->setVisible(1); ui->doubleSpinBox_8->setVisible(0);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 8){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(1); ui->spinBox_7->setVisible(1); ui->spinBox_8->setVisible(1); ui->spinBox_9->setVisible(0); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(1); ui->doubleSpinBox_7->setVisible(1); ui->doubleSpinBox_8->setVisible(1);
    ui->doubleSpinBox_9->setVisible(0); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 9){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(1); ui->spinBox_7->setVisible(1); ui->spinBox_8->setVisible(1); ui->spinBox_9->setVisible(1); ui->spinBox_10->setVisible(0);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(1); ui->doubleSpinBox_7->setVisible(1); ui->doubleSpinBox_8->setVisible(1);
    ui->doubleSpinBox_9->setVisible(1); ui->doubleSpinBox_10->setVisible(0); }
  if(arg1 == 10){
    ui->spinBox_1->setVisible(1); ui->spinBox_2->setVisible(1); ui->spinBox_3->setVisible(1); ui->spinBox_4->setVisible(1); ui->spinBox_5->setVisible(1);
    ui->spinBox_6->setVisible(1); ui->spinBox_7->setVisible(1); ui->spinBox_8->setVisible(1); ui->spinBox_9->setVisible(1); ui->spinBox_10->setVisible(1);
    ui->doubleSpinBox_1->setVisible(1); ui->doubleSpinBox_2->setVisible(1); ui->doubleSpinBox_3->setVisible(1); ui->doubleSpinBox_4->setVisible(1);
    ui->doubleSpinBox_5->setVisible(1); ui->doubleSpinBox_6->setVisible(1); ui->doubleSpinBox_7->setVisible(1); ui->doubleSpinBox_8->setVisible(1);
    ui->doubleSpinBox_9->setVisible(1); ui->doubleSpinBox_10->setVisible(1); }
  // Установка значений Xi
  ui->spinBox_1->setValue(x1[0]); ui->spinBox_2->setValue(x1[1]); ui->spinBox_3->setValue(x1[2]); ui->spinBox_4->setValue(x1[3]);
  ui->spinBox_5->setValue(x1[4]); ui->spinBox_6->setValue(x1[5]); ui->spinBox_7->setValue(x1[6]); ui->spinBox_8->setValue(x1[7]);
  ui->spinBox_9->setValue(x1[8]); ui->spinBox_10->setValue(x1[9]);
  // Установка значений Pi
  ui->doubleSpinBox_1->setValue(p[0]); ui->doubleSpinBox_2->setValue(p[1]); ui->doubleSpinBox_3->setValue(p[2]);
  ui->doubleSpinBox_4->setValue(p[3]); ui->doubleSpinBox_5->setValue(p[4]); ui->doubleSpinBox_6->setValue(p[5]);
  ui->doubleSpinBox_7->setValue(p[6]); ui->doubleSpinBox_8->setValue(p[7]); ui->doubleSpinBox_9->setValue(p[8]);
  ui->doubleSpinBox_10->setValue(p[9]);
}



// Сохранение данных
void MyChart::saveData(){
  x1[0] = ui->spinBox_1->value();
  x1[1] = ui->spinBox_2->value();
  x1[2] = ui->spinBox_3->value();
  x1[3] = ui->spinBox_4->value();
  x1[4] = ui->spinBox_5->value();
  x1[5] = ui->spinBox_6->value();
  x1[6] = ui->spinBox_7->value();
  x1[7] = ui->spinBox_8->value();
  x1[8] = ui->spinBox_9->value();
  x1[9] = ui->spinBox_10->value();
  p[0] = ui->doubleSpinBox_1->value();
  p[1] = ui->doubleSpinBox_2->value();
  p[2] = ui->doubleSpinBox_3->value();
  p[3] = ui->doubleSpinBox_4->value();
  p[4] = ui->doubleSpinBox_5->value();
  p[5] = ui->doubleSpinBox_6->value();
  p[6] = ui->doubleSpinBox_7->value();
  p[7] = ui->doubleSpinBox_8->value();
  p[8] = ui->doubleSpinBox_9->value();
  p[9] = ui->doubleSpinBox_10->value();
}



// Установка данных
void MyChart::setData(){
  // Установка значений Xi
  ui->spinBox_1->setValue(x1[0]);
  ui->spinBox_2->setValue(x1[1]);
  ui->spinBox_3->setValue(x1[2]);
  ui->spinBox_4->setValue(x1[3]);
  ui->spinBox_5->setValue(x1[4]);
  ui->spinBox_6->setValue(x1[5]);
  ui->spinBox_7->setValue(x1[6]);
  ui->spinBox_8->setValue(x1[7]);
  ui->spinBox_9->setValue(x1[8]);
  ui->spinBox_10->setValue(x1[9]);
  // Установка значений Pi
  ui->doubleSpinBox_1->setValue(p[0]);
  ui->doubleSpinBox_2->setValue(p[1]);
  ui->doubleSpinBox_3->setValue(p[2]);
  ui->doubleSpinBox_4->setValue(p[3]);
  ui->doubleSpinBox_5->setValue(p[4]);
  ui->doubleSpinBox_6->setValue(p[5]);
  ui->doubleSpinBox_7->setValue(p[6]);
  ui->doubleSpinBox_8->setValue(p[7]);
  ui->doubleSpinBox_9->setValue(p[8]);
  ui->doubleSpinBox_10->setValue(p[9]);
  // Установка параметров функции F(x)
  ui->label_Fx_1->setText(Fx_str[0]);
  ui->label_Fx_2->setText(Fx_str[1]);
  ui->label_Fx_3->setText(Fx_str[2]);
  ui->label_Fx_4->setText(Fx_str[3]);
  ui->label_Fx_5->setText(Fx_str[4]);
  ui->label_Fx_6->setText(Fx_str[5]);
  ui->label_Fx_7->setText(Fx_str[6]);
  ui->label_Fx_8->setText(Fx_str[7]);
  ui->label_Fx_9->setText(Fx_str[8]);
  ui->label_Fx_10->setText(Fx_str[9]);
  ui->label_Fx_11->setText(Fx_str[10]);
  // Установка значения математического ожидания
  ui->label_Mx->setText(QString::number(Mx, 'g', 5));
  // Установка значения дисперсии
  ui->label_Dx->setText(QString::number(Dx, 'g', 5));
  // Установка значения среднего квадратичного отклонения
  ui->label_Bx->setText(QString::number(Bx, 'g', 5));
}



// Сброс данных
void MyChart::resettingData(){
  for(int i = 0; i < 10; i++){ x1[i] = 0; p[i] = 0; }
  for(int i = 0; i < 11; i++) Fx_str[i] = "";
  error = 0;
  Mx = 0;
  Mx2 = 0;
  Dx = 0;
  Bx = 0;
  Mx_str = "";
  P = 0;
  sum = 0;
}



// Факториала
int MyChart::factorial(int i){
  if (i){
    int n = 1;
    for(int a = 2; a <= i; a++) n*=a;
    return n;
  }
  else return 1;
}



// Формула Пуассона
double MyChart::poisson(int m, double p){
  return (pow(p, m)/factorial(m))*pow(M_E,(-1*p));
}



// 1 задача
void MyChart::on_radioButton_3_clicked() {
  if(ui->radioButton_3->isChecked()){
    for(int i = 0; i < 10; i++) p[i] = 0;
  }
  lambda = 0;
  ui->doubleSpinBox->setValue(0);
  ui->doubleSpinBox_1->setEnabled(1);
  ui->doubleSpinBox_2->setEnabled(1);
  ui->doubleSpinBox_3->setEnabled(1);
  ui->doubleSpinBox_4->setEnabled(1);
  ui->doubleSpinBox_5->setEnabled(1);
  ui->doubleSpinBox_6->setEnabled(1);
  ui->doubleSpinBox_7->setEnabled(1);
  ui->doubleSpinBox_8->setEnabled(1);
  ui->doubleSpinBox_9->setEnabled(1);
  ui->doubleSpinBox_10->setEnabled(1);
}



// 2 задача
void MyChart::on_radioButton_4_clicked(){
  if(ui->radioButton_4->isChecked()){
    for(int i = 0; i < 10; i++) p[i] = 0;
  }
  ui->doubleSpinBox_1->setEnabled(0);
  ui->doubleSpinBox_2->setEnabled(0);
  ui->doubleSpinBox_3->setEnabled(0);
  ui->doubleSpinBox_4->setEnabled(0);
  ui->doubleSpinBox_5->setEnabled(0);
  ui->doubleSpinBox_6->setEnabled(0);
  ui->doubleSpinBox_7->setEnabled(0);
  ui->doubleSpinBox_8->setEnabled(0);
  ui->doubleSpinBox_9->setEnabled(0);
  ui->doubleSpinBox_10->setEnabled(0);

  // Установка значений Pi
  ui->doubleSpinBox_1->setValue(0);
  ui->doubleSpinBox_2->setValue(0);
  ui->doubleSpinBox_3->setValue(0);
  ui->doubleSpinBox_4->setValue(0);
  ui->doubleSpinBox_5->setValue(0);
  ui->doubleSpinBox_6->setValue(0);
  ui->doubleSpinBox_7->setValue(0);
  ui->doubleSpinBox_8->setValue(0);
  ui->doubleSpinBox_9->setValue(0);
  ui->doubleSpinBox_10->setValue(0);
}



// Закрытие
void MyChart::close_recieveData(int i){
  if (i == 1){
    QWidget::close();
  }
}




