#include "fifthlab.h"
#include "ui_fifthlab.h"
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <qmath.h>
#include <QtWidgets/QGesture>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QChartView>

fifthlab::fifthlab(QWidget *parent) : QMainWindow(parent), ui(new Ui::fifthlab) {
  ui->setupUi(this);
  // Работа с директориями и путями
  currentPath = QDir::currentPath();                       // Директория исполняемого файла
  currentPath.replace("/", "\\\\");                        // Заменить символы / на //
  Data_txt = "\\\\Data.txt";                               //
  Data_txt.prepend(currentPath);                           // Вписать перед именем приложения каталог
  strcpy(Data_txt_char, Data_txt.toUtf8().data());         // Переписать Data_txt (QString) в Data_txt_char (char)
  strcpy(currentPath_char, currentPath.toUtf8().data());   // Переписать currentPath (QString) в currentPath_char (char)
  // Подключение-Включение поебни
  ui->radioButton_3->clicked();
  ui->radioButton_3->setChecked(1);
  ui->radioButton_load->setChecked(1);
  ui->radioButton_load->clicked();
  on_pushButton_chart_clicked();
  // Удаление тупых заголовков
  ui->tableWidget_rows->verticalHeader()->hide();
  ui->tableWidget_rows->horizontalHeader()->hide();
  ui->tableWidget_Fx->verticalHeader()->hide();
  ui->tableWidget_Fx->horizontalHeader()->hide();
  // Вывод первой формулы
  on_comboBox_formula_activated(0);
  //
  ui->tableWidget_rows->setEnabled(1);
  ui->tableWidget_Fx->setEnabled(1);
  ui->textEdit->setEnabled(1);
  ui->textEdit_text->setEnabled(1);
}

fifthlab::~fifthlab() { delete ui; }


// Действие
void fifthlab::on_pushButton_action_clicked() {
  if(ui->radioButton_load->isChecked()) readData(); // Считать данные из файла
  convertData();                                   // Преобразовать данные
  intervals();                                    // Интервалы
  calculateData();                               // Расчёт данных
  on_spinBox_1_valueChanged(1);                 //
  setData();                                   // Установить данные
}


// Считать данные из файла
void fifthlab::readData(){
  d_str = " ";
  // Считать и установить сохранённые результаты
  QFile file(Data_txt_char);
  // Если файл существует считывание и установить данные
  if ((file.exists())&&(file.open(QIODevice::ReadOnly))) {
    // Прочитать первую строку в которой записано кол-во записей
    if(!file.atEnd()) {
      // Читать до конца файла
      d_str = d_str.append(file.readLine());
    }
  }
  file.close();                            // Закрыть файл
  // d_str хранит текст из файла
}


// Преобразовать данные из строки в массив d[] double
void fifthlab::convertData(){

  // Очистить tableWidget
  ui->tableWidget_rows->clear();

  // Обнуление
  numberSpaces = 0; num = 0;

  // Если ручной ввод
  if(ui->radioButton_arm->isChecked()){
    d_str = " ";
    d_str = d_str.append(ui->lineEdit_arm->text());
    d_str.replace("\n", " ");
  }

  // Заменить символы "," на "."
  d_str.replace(",", ".");

  // Кол-во пробелов
  for (int i = 0; i < d_str.size(); i++){
    if(d_str.at(i) == " ") numberSpaces++;
  }
  num = numberSpaces - 1; // Кол-во чисел

  // Ограничение SpinBox
  ui->spinBox_1->setRange(1, num);
  // Обнулить
  for(int i = 0; i < 1001; i++) t[i] = 0;
  for(int i = 0; i < 1000; i++) d[i] = 0;
  for(int i = 0; i < 1000; i++) di_str[i] = "";

  // Перебираем все символы строки в поиске индексов пробелов
  for(int i = 0, j = 0; i < d_str.size(); i++){
    // " " сплиттер - находим индексы пробелов
    if(d_str[i] == ' '){
      t[j] = i;
      j++;
    }
  }

  // Переписываем значения между пробелов, каждое в отдельную переменную
  for(int i = 0; i < num; i++){
    for(int j = t[i]+1; j < t[i+1]; j++) di_str[i].append(d_str.at(j));
  }

  // Преобразуем к типу double
  for(int i = 0; i < num; i++){
    d[i] = di_str[i].toDouble();
  }

  // num          - хранит кол-во чисел
  // numberSpaces - хранит кол-во пробелов
  // di_str[]     - хранит каждое число в виде строки
  // d[]          - хранит каждое число в виде double
}


// Расчёт данных
void fifthlab::calculateData(){
  // Обнуление
  d2_str = ""; count2_str = ""; numberVariant_str = ""; row = "";
  d_average = 0; d_min = 0; d_max = 0; count = 0; P = 0;
  Mx = 0; Dx = 0; Bx = 0; Mx2 = 0; Sx = 0; d_test = 0; jay = 0;
  for (int i = 0; i < 1000; i++) count2[i] = 0;
  for (int i = 0; i < 1000; i++) count3[i] = 0;
  for(int i = 0; i < 11; i++) Fx_str[i] = "";
  for (int i = 0; i < 1001; i++) Pch[i] = 0;

  // Кол-во вариантов чисел
  for (int i = 0; i < num; i++)  {
    int j = 0;
    while (j < i && d[j] != d[i]) ++j;
    count += j == i;
  }

  // Упорядочить по возрастанию данные и переписать в массив d2[] double
  // http://www.itmathrepetitor.ru/qt5-funkcii-dlya-raboty-s-qstring/
  for(int i = 0; i < num; i++) d2[i] = d[i];
  for (int startIndex = 0; startIndex < num-1; ++startIndex) {
    int smallestIndex = startIndex;
    for (int currentIndex = startIndex + 1; currentIndex < num; ++currentIndex) {
      if (d2[currentIndex] < d2[smallestIndex])
        smallestIndex = currentIndex; }
    std::swap(d2[startIndex], d2[smallestIndex]);
  }

  // Вписать отсортированный массив в строку
  for(int i = 0; i < num; i++){
    d2_str = d2_str.append(QString::number(d2[i]));
    d2_str = d2_str.append(" ");
  }

  // Вариационный ряд
  for (int i = 0; i < count; i++){
    d_test = d2[jay];
    numberVariant[i] = d_test;
    while(d2[jay] == d_test){ count2[i]++; jay++; }
  }

  // Статистический раяд
  jay = 0;
  for (int i = 0; i < count; i++){
    d_test = d2[jay];
    numberVariant[i] = d_test;
    while(d2[jay] == d_test){ count3[i]++; jay++; }
  }
  for (int i = 0; i < count; i++) count3[i] = count3[i]/num;


  // Функции распределения F(x) установка параметров функции
  // Интервальная
  if(SB > 0){
    ui->tableWidget_Fx->setRowCount(SB+1);
    Fxt2_str = "при x <= ";
    Fxt2_str = Fxt2_str.append(QString::number(rval_average[0], 'g', 4));
    ui->tableWidget_Fx->setItem(0,0, new QTableWidgetItem("0"));
    ui->tableWidget_Fx->setItem(0,1, new QTableWidgetItem(Fxt2_str));
    for (int i = 1, jay = 2; i < SB; i++, jay+=2){
      P = P+(distr[i-1]/num);
      Pch[i] = P;
      Fxt2_str = "при ";
      Fxt2_str = Fxt2_str.append(QString::number(rval_average[i-1], 'g', 4));
      Fxt2_str = Fxt2_str.append(" < x <= ");
      Fxt2_str = Fxt2_str.append(QString::number(rval_average[i], 'g', 4));
      ui->tableWidget_Fx->setItem(i,0, new QTableWidgetItem(QString::number(Pch[i])));
      ui->tableWidget_Fx->setItem(i,1, new QTableWidgetItem(Fxt2_str));
    }
    Fxt2_str = "при x > ";
    Fxt2_str = Fxt2_str.append(QString::number(rval_average[SB-1], 'g', 4));
    ui->tableWidget_Fx->setItem(SB,0, new QTableWidgetItem("1"));
    ui->tableWidget_Fx->setItem(SB,1, new QTableWidgetItem(Fxt2_str));
  }

  // Не интервальная
  else{
    ui->tableWidget_Fx->setRowCount(count+1);
    Fxt2_str = "при x <= ";
    Fxt2_str = Fxt2_str.append(QString::number(numberVariant[0], 'g', 4));
    ui->tableWidget_Fx->setItem(0,0, new QTableWidgetItem("0"));
    ui->tableWidget_Fx->setItem(0,1, new QTableWidgetItem(Fxt2_str));
    for (int i = 1, jay = 2; i < count; i++, jay+=2){
      P = P+count3[i-1];
      Pch[i] = P;
      Fxt2_str = "при ";
      Fxt2_str = Fxt2_str.append(QString::number(numberVariant[i-1], 'g', 4));
      Fxt2_str = Fxt2_str.append(" < x <= ");
      Fxt2_str = Fxt2_str.append(QString::number(numberVariant[i], 'g', 4));
      ui->tableWidget_Fx->setItem(i,0, new QTableWidgetItem(QString::number(Pch[i])));
      ui->tableWidget_Fx->setItem(i,1, new QTableWidgetItem(Fxt2_str));
    }
    Fxt2_str = "при x > ";
    Fxt2_str = Fxt2_str.append(QString::number(numberVariant[count-1], 'g', 4));
    ui->tableWidget_Fx->setItem(count,0, new QTableWidgetItem("1"));
    ui->tableWidget_Fx->setItem(count,1, new QTableWidgetItem(Fxt2_str));
  }


   // Математическое ожидание
   for(int i = 0; i < count; i++) Mx = Mx + (numberVariant[i]*count3[i]);
   // Дисперсия
   for(int i = 0; i < count; i++) Mx2 = Mx2 + (pow(numberVariant[i],2) * count3[i]);
   Dx = Mx2 - pow(Mx,2);
   // Среднее квадратичное отклонение
   Bx = pow(Dx,0.5);

   // Расчёт минимального максимального и среднего значений
   d_min = d2[0];
   d_max = d2[num-1];
   for(int i = 0; i < num; i++) d_average = d_average + d2[i];
   d_average = d_average/num;

   // Вариационный и статистический ряд переписать в вите строки
   ui->tableWidget_rows->setRowCount(count);
   for (int i = 0; i < count; i++){
     ui->tableWidget_rows->setItem(i,0, new QTableWidgetItem(QString::number(numberVariant[i])));
     ui->tableWidget_rows->setItem(i,1, new QTableWidgetItem(QString::number(count2[i])));
     ui->tableWidget_rows->setItem(i,2, new QTableWidgetItem(QString::number(count3[i])));
   }

  // Здесь считаешь свои непонятные формулы
  //
  //
  //
  //
  //

   // Характиристики в виде строки
   text_str = "Кол-во введённых чисел: ";                           text_str = text_str.append(QString::number(num));       text_str = text_str.append("\n");
   text_str = text_str.append("Кол-во Вариантов: ");                text_str = text_str.append(QString::number(count));     text_str = text_str.append("\n");
   text_str = text_str.append("Минимальное значение: ");            text_str = text_str.append(QString::number(d_min));     text_str = text_str.append("\n");
   text_str = text_str.append("Максимальное значение: ");           text_str = text_str.append(QString::number(d_max));     text_str = text_str.append("\n");
   text_str = text_str.append("Среднее значение: ");                text_str = text_str.append(QString::number(d_average)); text_str = text_str.append("\n");
   text_str = text_str.append("Математическое ожидание: ");         text_str = text_str.append(QString::number(Mx));        text_str = text_str.append("\n");
   text_str = text_str.append("Дисперсия: ");                       text_str = text_str.append(QString::number(Dx));        text_str = text_str.append("\n");
   text_str = text_str.append("Среднее квадратичное отклонение: "); text_str = text_str.append(QString::number(Bx));        text_str = text_str.append("\n");
   text_str = text_str.append("Количество интервалов: ");           text_str = text_str.append(QString::number(SB));        text_str = text_str.append("\n");
// text_str = text_str.append("Сюда выводишь решение: ");           text_str = text_str.append(QString::number(123));       text_str = text_str.append("\n");

   // Mx       - хранит Математическое ожидание
   // Dx       - хранит дисперсию
   // Bx       - хранит среднее квадратичное отклонение
   // Pch[]    - хранит массив значений функции Fx
   // count2[] - хранит массив значений Вариационного ряда
   // count3[] - хранит массив значений Статистического ряда
}


// Установить данные
void fifthlab::setData(){
  if(organize == 0) ui->textEdit->setText(d_str.remove(0,1));
  if(organize == 2) ui->textEdit->setText(d2_str);
  ui->spinBox_1->setValue(1);
  on_spinBox_1_valueChanged(1);
  ui->textEdit_text->setText(text_str);
}


// Вывод числа по индексу
void fifthlab::on_spinBox_1_valueChanged(int arg1) {
  if(organize == 0)ui->doubleSpinBox_1->setValue(d[arg1-1]);
  if(organize == 2)ui->doubleSpinBox_1->setValue(d2[arg1-1]);
}


// Отрисовка графика
void fifthlab::on_pushButton_chart_clicked(){
  // Считать параметры графика
  x_min = ui->doubleSpinBox_x_min->value();
  x_max = ui->doubleSpinBox_x_max->value();
  x_cap = ui->spinBox_x_cap->value();
  y_min = ui->doubleSpinBox_y_min->value();
  y_max = ui->doubleSpinBox_y_max->value();
  y_cap = ui->spinBox_y_cap->value();
  // Создаём график
  chrt = new QChart;
  // кривые, отображаемые на графике
  QLineSeries* series1 = new QLineSeries();
  QLineSeries* series2 = new QLineSeries();
  QLineSeries* series11 = new QLineSeries(); QLineSeries* series12 = new QLineSeries(); QLineSeries* series13 = new QLineSeries();
  QLineSeries* series14 = new QLineSeries(); QLineSeries* series15 = new QLineSeries(); QLineSeries* series16 = new QLineSeries();
  QLineSeries* series17 = new QLineSeries(); QLineSeries* series18 = new QLineSeries(); QLineSeries* series19 = new QLineSeries();
  QLineSeries* series20 = new QLineSeries(); QLineSeries* series21 = new QLineSeries(); QLineSeries* series22 = new QLineSeries();
  QLineSeries* series23 = new QLineSeries(); QLineSeries* series24 = new QLineSeries(); QLineSeries* series25 = new QLineSeries();
  QLineSeries* series26 = new QLineSeries(); QLineSeries* series27 = new QLineSeries(); QLineSeries* series28 = new QLineSeries();
  QLineSeries* series29 = new QLineSeries(); QLineSeries* series30 = new QLineSeries(); QLineSeries* series31 = new QLineSeries();
  QLineSeries* series32 = new QLineSeries(); QLineSeries* series33 = new QLineSeries(); QLineSeries* series34 = new QLineSeries();
  QLineSeries* series35 = new QLineSeries();
  // связь графика с элементом отображения
  ui->vchrt->setChart(chrt);
  // Стиь графика в целом
  QFont font;
  font.setPixelSize(18);
  chrt->setTitleFont(font);
  chrt->setTitleBrush(QBrush(Qt::black));
  chrt->setTitle(" ");
  // Стиль для координатных прямых
  QPen pen(QRgb(0x909090));
  pen.setWidth(2);
  series1->setPen(pen);
  // Стиль 2-го графика
  QPen pen2(QRgb(0x8e3975));
  pen2.setWidth(4);
  series2->setPen(pen2);
  series11->setPen(pen2); series12->setPen(pen2); series13->setPen(pen2); series14->setPen(pen2); series15->setPen(pen2);
  series16->setPen(pen2); series17->setPen(pen2); series18->setPen(pen2); series19->setPen(pen2); series20->setPen(pen2);
  series21->setPen(pen2); series22->setPen(pen2); series23->setPen(pen2); series24->setPen(pen2); series25->setPen(pen2);
  series26->setPen(pen2); series27->setPen(pen2); series28->setPen(pen2); series29->setPen(pen2); series30->setPen(pen2);
  series31->setPen(pen2); series32->setPen(pen2); series33->setPen(pen2); series34->setPen(pen2); series35->setPen(pen2);
  // Анимация графика
  chrt->setAnimationOptions(QChart::AllAnimations);
  // ось Х
  QValueAxis *axisX = new QValueAxis;
  axisX->setRange(x_min, x_max); // диапазон значений на оси
  axisX->setTickCount(x_cap);    // число линий сетки
  axisX->setLabelFormat("%.2f"); // формат отображения чисел на оси
  // ось Y
  QValueAxis *axisY = new QValueAxis;
  axisY->setRange(y_min, y_max);
  axisY->setTickCount(y_cap);
  axisY->setLabelFormat("%g");

  // Полигоны ni
  if(ui->radioButton_3->isChecked()){

    if(SB > 0){
      for(int i = 0; i < SB; i++) {
        series2->append((rval_max[i]+rval_min[i])/2, distr[i]);
      }
    }
    else{
    for(int i = 0; i<count; i++) {
      series2->append(numberVariant[i], count2[i]);
    }
    }
  }

  // Полигоны wi
  if(ui->radioButton->isChecked()){
    if(SB > 0){
      for(int i = 0; i < SB; i++) {
        series2->append((rval_max[i]+rval_min[i])/2, distr[i]/num);
      }
    }
    else{
      for(int i = 0; i<count; i++) {
        series2->append(numberVariant[i], count3[i]);
      }
    }
  }

  // Построение Функции распределения F(x)
  if(ui->radioButton_4->isChecked()){
    if(SB > 0){
      if (SB <= 25){
        for(int i = SB; i < 100; i++) Pch[i] = 1;
        for(int i = SB; i < 100; i++) rval_average[i] = rval_average[SB-1];
        series11->append(x_min           , 0); series11->append(rval_average[0], 0);
        series12->append(rval_average[0], Pch[1]); series12->append(rval_average[1], Pch[1]);
        series13->append(rval_average[1], Pch[2]); series13->append(rval_average[2], Pch[2]);
        series14->append(rval_average[2], Pch[3]);  series14->append(rval_average[3], Pch[3]);
        series15->append(rval_average[3], Pch[4]); series15->append(rval_average[4], Pch[4]);
        series16->append(rval_average[4], Pch[5]); series16->append(rval_average[5], Pch[5]);
        series17->append(rval_average[5], Pch[6]); series17->append(rval_average[6], Pch[6]);
        series18->append(rval_average[6], Pch[7]); series18->append(rval_average[7], Pch[7]);
        series19->append(rval_average[7], Pch[8]); series19->append(rval_average[8], Pch[8]);
        series20->append(rval_average[8], Pch[9]); series20->append(rval_average[9], Pch[9]);
        series21->append(rval_average[9], Pch[10]); series21->append(rval_average[10], Pch[10]);
        series22->append(rval_average[10], Pch[11]); series22->append(rval_average[11], Pch[11]);
        series23->append(rval_average[11], Pch[12]); series23->append(rval_average[12], Pch[12]);
        series24->append(rval_average[12], Pch[13]); series24->append(rval_average[13], Pch[13]);
        series25->append(rval_average[13], Pch[14]); series25->append(rval_average[14], Pch[14]);
        series26->append(rval_average[14], Pch[15]); series26->append(rval_average[15], Pch[15]);
        series27->append(rval_average[15], Pch[16]); series27->append(rval_average[16], Pch[16]);
        series28->append(rval_average[16], Pch[17]); series28->append(rval_average[17], Pch[17]);
        series29->append(rval_average[17], Pch[18]); series29->append(rval_average[18], Pch[18]);
        series30->append(rval_average[18], Pch[19]); series30->append(rval_average[19], Pch[19]);
        series31->append(rval_average[19], Pch[20]); series31->append(rval_average[20], Pch[20]);
        series32->append(rval_average[20], Pch[21]); series32->append(rval_average[21], Pch[21]);
        series33->append(rval_average[21], Pch[22]); series33->append(rval_average[22], Pch[22]);
        series34->append(rval_average[22], Pch[23]); series34->append(rval_average[23], Pch[23]);
        series35->append(rval_average[23], Pch[24]); series35->append(x_max            , Pch[24]);
      }
    }
    else{
      if (count <= 25){
        for(int i = count; i < 1000; i++) Pch[i] = 1;
        for(int i = count; i < 1000; i++) numberVariant[i] = numberVariant[count-1];
        series11->append(x_min           , 0); series11->append(numberVariant[0], 0);
        series12->append(numberVariant[0], Pch[1]); series12->append(numberVariant[1], Pch[1]);
        series13->append(numberVariant[1], Pch[2]); series13->append(numberVariant[2], Pch[2]);
        series14->append(numberVariant[2], Pch[3]);  series14->append(numberVariant[3], Pch[3]);
        series15->append(numberVariant[3], Pch[4]); series15->append(numberVariant[4], Pch[4]);
        series16->append(numberVariant[4], Pch[5]); series16->append(numberVariant[5], Pch[5]);
        series17->append(numberVariant[5], Pch[6]); series17->append(numberVariant[6], Pch[6]);
        series18->append(numberVariant[6], Pch[7]); series18->append(numberVariant[7], Pch[7]);
        series19->append(numberVariant[7], Pch[8]); series19->append(numberVariant[8], Pch[8]);
        series20->append(numberVariant[8], Pch[9]); series20->append(numberVariant[9], Pch[9]);
        series21->append(numberVariant[9], Pch[10]); series21->append(numberVariant[10], Pch[10]);
        series22->append(numberVariant[10], Pch[11]); series22->append(numberVariant[11], Pch[11]);
        series23->append(numberVariant[11], Pch[12]); series23->append(numberVariant[12], Pch[12]);
        series24->append(numberVariant[12], Pch[13]); series24->append(numberVariant[13], Pch[13]);
        series25->append(numberVariant[13], Pch[14]); series25->append(numberVariant[14], Pch[14]);
        series26->append(numberVariant[14], Pch[15]); series26->append(numberVariant[15], Pch[15]);
        series27->append(numberVariant[15], Pch[16]); series27->append(numberVariant[16], Pch[16]);
        series28->append(numberVariant[16], Pch[17]); series28->append(numberVariant[17], Pch[17]);
        series29->append(numberVariant[17], Pch[18]); series29->append(numberVariant[18], Pch[18]);
        series30->append(numberVariant[18], Pch[19]); series30->append(numberVariant[19], Pch[19]);
        series31->append(numberVariant[19], Pch[20]); series31->append(numberVariant[20], Pch[20]);
        series32->append(numberVariant[20], Pch[21]); series32->append(numberVariant[21], Pch[21]);
        series33->append(numberVariant[21], Pch[22]); series33->append(numberVariant[22], Pch[22]);
        series34->append(numberVariant[22], Pch[23]); series34->append(numberVariant[23], Pch[23]);
        series35->append(numberVariant[23], Pch[24]); series35->append(x_max            , Pch[24]);
      }
    }
  }



  // Гистограмма ni
  if(ui->radioButton_Gni->isChecked()){
    for(int i = 0; i<SB; i++) {
        series2->append(rval_min[i], 0);
        series2->append(rval_min[i], distr[i]);
        series2->append(rval_max[i], distr[i]);
        series2->append(rval_max[i], 0);
    }
  }

  // Гистограмма wi
  if(ui->radioButton_Gwi->isChecked()){
    for(int i = 0; i<SB; i++) {
      series2->append(rval_min[i], 0);
      series2->append(rval_min[i], distr[i]/num);
      series2->append(rval_max[i], distr[i]/num);
      series2->append(rval_max[i], 0);
    }
  }

    // связываем график с построенными кривыми
    chrt->addSeries(series1); chrt->addSeries(series2); chrt->addSeries(series11); chrt->addSeries(series12);
    chrt->addSeries(series13); chrt->addSeries(series14); chrt->addSeries(series15); chrt->addSeries(series16);
    chrt->addSeries(series17);  chrt->addSeries(series18); chrt->addSeries(series19); chrt->addSeries(series20);
    chrt->addSeries(series21); chrt->addSeries(series22); chrt->addSeries(series23); chrt->addSeries(series24);
    chrt->addSeries(series25); chrt->addSeries(series26); chrt->addSeries(series27); chrt->addSeries(series28);
    chrt->addSeries(series29); chrt->addSeries(series30); chrt->addSeries(series31); chrt->addSeries(series32);
    chrt->addSeries(series33); chrt->addSeries(series34); chrt->addSeries(series35);

    // устанавливаем оси для каждого графика
    chrt->setAxisX(axisX, series1);  chrt->setAxisY(axisY, series1);  chrt->setAxisX(axisX, series2);  chrt->setAxisY(axisY, series2);
    chrt->setAxisX(axisX, series11); chrt->setAxisY(axisY, series11); chrt->setAxisX(axisX, series12); chrt->setAxisY(axisY, series12);
    chrt->setAxisX(axisX, series13); chrt->setAxisY(axisY, series13); chrt->setAxisX(axisX, series14); chrt->setAxisY(axisY, series14);
    chrt->setAxisX(axisX, series15); chrt->setAxisY(axisY, series15); chrt->setAxisX(axisX, series16); chrt->setAxisY(axisY, series16);
    chrt->setAxisX(axisX, series17); chrt->setAxisY(axisY, series17); chrt->setAxisX(axisX, series18); chrt->setAxisY(axisY, series18);
    chrt->setAxisX(axisX, series19); chrt->setAxisY(axisY, series19); chrt->setAxisX(axisX, series20); chrt->setAxisY(axisY, series20);
    chrt->setAxisX(axisX, series21); chrt->setAxisY(axisY, series21); chrt->setAxisX(axisX, series22); chrt->setAxisY(axisY, series22);
    chrt->setAxisX(axisX, series23); chrt->setAxisY(axisY, series23); chrt->setAxisX(axisX, series24); chrt->setAxisY(axisY, series24);
    chrt->setAxisX(axisX, series25); chrt->setAxisY(axisY, series25); chrt->setAxisX(axisX, series26); chrt->setAxisY(axisY, series26);
    chrt->setAxisX(axisX, series27); chrt->setAxisY(axisY, series27); chrt->setAxisX(axisX, series28); chrt->setAxisY(axisY, series28);
    chrt->setAxisX(axisX, series29); chrt->setAxisY(axisY, series29); chrt->setAxisX(axisX, series30); chrt->setAxisY(axisY, series30);
    chrt->setAxisX(axisX, series31); chrt->setAxisY(axisY, series31); chrt->setAxisX(axisX, series32); chrt->setAxisY(axisY, series32);
    chrt->setAxisX(axisX, series33); chrt->setAxisY(axisY, series33); chrt->setAxisX(axisX, series34); chrt->setAxisY(axisY, series34);
    chrt->setAxisX(axisX, series35); chrt->setAxisY(axisY, series35);

    // Удаляем поебень на графике
    chrt->legend()->hide();
}


// Упорядочить
void fifthlab::on_checkBox_stateChanged(int arg1){
  organize = arg1;
on_pushButton_action_clicked();
}


// Выбор Эмперической функции
void fifthlab::on_radioButton_4_clicked(){
//  y_min = 0;
//  y_max = 1;
//  y_cap = 11;
//  ui->doubleSpinBox_y_min->setValue(y_min);
//  ui->doubleSpinBox_y_max->setValue(y_max);
//  ui->spinBox_y_cap->setValue(y_cap);
}
// Выбор Полигона ni
void fifthlab::on_radioButton_3_clicked(){
//  y_min = 0;
//  y_max = 50;
//  y_cap = 11;
//  ui->doubleSpinBox_y_min->setValue(y_min);
//  ui->doubleSpinBox_y_max->setValue(y_max);
//  ui->spinBox_y_cap->setValue(y_cap);
//  x_min = 0;
//  x_max = 100;
//  x_cap = 11;
//  ui->doubleSpinBox_x_min->setValue(x_min);
//  ui->doubleSpinBox_x_max->setValue(x_max);
//  ui->spinBox_x_cap->setValue(x_cap);
}
// Выбор Полигона wi
void fifthlab::on_radioButton_clicked(){
//  y_min = 0;
//  y_max = 1;
//  y_cap = 11;
//  ui->doubleSpinBox_y_min->setValue(y_min);
//  ui->doubleSpinBox_y_max->setValue(y_max);
//  ui->spinBox_y_cap->setValue(y_cap);
//  x_min = 0;
//  x_max = 100;
//  x_cap = 11;
//  ui->doubleSpinBox_x_min->setValue(x_min);
//  ui->doubleSpinBox_x_max->setValue(x_max);
//  ui->spinBox_x_cap->setValue(x_cap);
}
// Гистограмма ni
void fifthlab::on_radioButton_Gni_clicked(){
//  y_min = 0;
//  y_max = 100;
//  y_cap = 11;
//  ui->doubleSpinBox_y_min->setValue(y_min);
//  ui->doubleSpinBox_y_max->setValue(y_max);
//  ui->spinBox_y_cap->setValue(y_cap);
//  x_min = 0;
//  x_max = 100;
//  x_cap = 11;
//  ui->doubleSpinBox_x_min->setValue(x_min);
//  ui->doubleSpinBox_x_max->setValue(x_max);
//  ui->spinBox_x_cap->setValue(x_cap);
}
// Гистограмма wi
void fifthlab::on_radioButton_Gwi_clicked(){
//  y_min = 0;
//  y_max = 1;
//  y_cap = 11;
//  ui->doubleSpinBox_y_min->setValue(y_min);
//  ui->doubleSpinBox_y_max->setValue(y_max);
//  ui->spinBox_y_cap->setValue(y_cap);
//  x_min = 0;
//  x_max = 100;
//  x_cap = 11;
//  ui->doubleSpinBox_x_min->setValue(x_min);
//  ui->doubleSpinBox_x_max->setValue(x_max);
//  ui->spinBox_x_cap->setValue(x_cap);
}


// Загрузка
void fifthlab::on_radioButton_load_clicked(){
  ui->lineEdit_arm->setEnabled(0);
  zeroize();
}
// Ручник
void fifthlab::on_radioButton_arm_clicked(){
   ui->lineEdit_arm->setEnabled(1);
  zeroize();
}

// Обнуление
void fifthlab::zeroize(){
  d_str = ""; d1_str = ""; d2_str = ""; t_str = ""; count2_str = ""; numberVariant_str = "";
  row = ""; Fxn_str = ""; Fxt_str = ""; Mx_str = ""; text_str = ""; ui->lineEdit_arm->setText("");
  count = 0; numberSpaces = 0; num = 0; d_min = 0; d_max = 0; d_average = 0; P = 0; Mx2 = 0; Mx = 0; Dx = 0; Bx = 0; Sx = 0; d_test = 0; jay = 0;
  for (int i = 0; i < 1000; i++){ d[i] = 0; d2[i] = 0; di_str[i] = ""; count2[i] = 0; count3[i] = 0; numberVariant[i] = 0; }
  for (int i = 0; i < 1001; i++){ Pch[i] = 0; t[i] = 0; Fx_str[i] = ""; rval_test = "";}
  SB = 0; spSplt1 = 0; sp2 = 0; rval_str = "";
  for(int i = 0; i < 10; i++){ rval2_str[i] = ""; rval_min[i] = 0; rval_max[i] = 0; }
  ui->tableWidget_Fx->clear();
  ui->tableWidget_rows->clear();
  ui->tableWidget_Fx->setRowCount(0);
  ui->tableWidget_rows->setRowCount(0);
  ui->doubleSpinBox_1->setValue(0);
  ui->textEdit->setText("");
  ui->textEdit_text->setText("");
  ui->lineEdit_arm->setText("");
  ui->lineEdit_interval->setText("");
  ui->checkBox->setChecked(0);
}


// Интервалы
void fifthlab::intervals(){
  // Обнулить данные
  rval_str = ""; spSplt1 = 0; rval_test = ""; sp2 = 0;
  for(int i = 0; i < 100; i++){rval2_str[i] = ""; rval_min[i] = 0; rval_max[i] = 0; rval_min_str[i] = ""; rval_max_str[i] = "";}
  for(int i = 0; i < 101; i++){ sp1[i] = 0;}
  for(int i = 0; i < 100; i++) distr[i] = 0;

  // Перепишем строку с интервалами
  rval_str = ui->lineEdit_interval->text();

    // Впишем в конце и в начале пробелы если это необходимо
    if(rval_str.at(0) != " ") rval_str.prepend(" ");
    if(rval_str.at(rval_str.size()-1) != " ") rval_str.append(" ");

    // Перебираем все символы строки в поиске индексов пробелов
    for(int i = 0, j = 0; i < rval_str.size(); i++){
      // " " сплиттер - находим индексы пробелов
      if(rval_str[i] == ' '){
        spSplt1++;
        sp1[j] = i;
        j++;
      }
      SB = spSplt1-1; // Кол-во интервалов
    }
    // Переписываем значения между пробелов, каждое в отдельную переменную
    for(int i = 0; i < 100; i++){
      for(int j = sp1[i]+1; j < sp1[i+1]; j++) rval2_str[i].append(rval_str.at(j));
    }

    // Определяем min и max в интервалах
    for(int i = 0; i < SB; i++){
      for(int j = 0; j < rval2_str[i].size(); j++){
        if(rval2_str[i].at(j) == ";") sp2 = j;
      }
      for(int j = 0; j < sp2; j++){
        rval_min_str[i] = rval_min_str[i].append(rval2_str[i].at(j));
      }
      for(int j = sp2+1; j < rval2_str[i].size(); j++){
        rval_max_str[i] = rval_max_str[i].append(rval2_str[i].at(j));
      }
      rval_min[i] = rval_min_str[i].toInt();
      rval_max[i] = rval_max_str[i].toInt();
    }

    // Распределение по интервалам
    for(int i = 0; i < SB; i++){
      for (int j = 0; j < count; j++){
          if (numberVariant[j] >= rval_min[i] && numberVariant[j] <= rval_max[i]){
            distr[i] = distr[i] + count2[j];
          }
      }
    }

    for(int i = 0; i < SB; i++){
      rval_average[i] = (rval_max[i]+rval_min[i])/2;
    }


    // Вывод на экран
    for(int i = 0; i < SB; i++){
      ui->tableWidget_rows->setItem(i,3, new QTableWidgetItem(rval_min_str[i]));
      ui->tableWidget_rows->setItem(i,4, new QTableWidgetItem(rval_max_str[i]));
      ui->tableWidget_rows->setItem(i,5, new QTableWidgetItem(QString::number(rval_average[i])));
      ui->tableWidget_rows->setItem(i,6, new QTableWidgetItem(QString::number(distr[i])));
      ui->tableWidget_rows->setItem(i,7, new QTableWidgetItem(QString::number(distr[i]/num)));
    }
}


// Вывод формул
void fifthlab::on_comboBox_formula_activated(int index){
  if (index == 0) png_name = "\\\\png\\\\31.png";
  if (index == 1) png_name = "\\\\png\\\\32.png";
  if (index == 2) png_name = "\\\\png\\\\33.png";
  if (index == 3) png_name = "\\\\png\\\\34.png";
  // Здесь указываешь формулы которые будешь выводить

  png_name.prepend(currentPath);                           // Вписать перед именем картинки каталог
  strcpy(png_name_char, png_name.toUtf8().data());

  QPixmap pix(png_name_char);
  int w = ui->label_formula->width();
  int h = ui->label_formula->height();
  ui->label_formula->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}
