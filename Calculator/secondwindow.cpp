#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) : QDialog(parent), ui(new Ui::SecondWindow) {
  ui->setupUi(this);

}

SecondWindow::~SecondWindow() {  delete ui; }

void SecondWindow::formula_recieveData (int i){
  ui->spinBox_formula->setValue(i);
  currentPath = QDir::currentPath();
  currentPath.replace("/", "\\\\");
  if (i == 1) png_name = "\\\\png\\\\1.png";
  if (i == 2) png_name = "\\\\png\\\\2.png";
  if (i == 3) png_name = "\\\\png\\\\3.png";
  if (i == 4) png_name = "\\\\png\\\\4.png";
  if (i == 5) png_name = "\\\\png\\\\5.png";
  if (i == 6) png_name = "\\\\png\\\\6.png";
  currentPath.append(png_name);
  strcpy(png_name_char, currentPath.toUtf8().data());
  ui->label->setText(png_name_char);
    QPixmap pix(png_name_char);
    int w = ui->label_formula->width();
    int h = ui->label_formula->height();
    ui->label_formula->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
    if (i == 1) ui->label_2->setText("Размещения без повторений");
    if (i == 2) ui->label_2->setText("Размещения с повторениями");
    if (i == 3) ui->label_2->setText("Сочетания без повторений");
    if (i == 4) ui->label_2->setText("Сочетания с повторениями");
    if (i == 5) ui->label_2->setText("Перестановки без повторений");
    if (i == 6) ui->label_2->setText("Перестановки с повторениями");
}



void SecondWindow::close_recieveData(int i){
  if (i == 1){
    QWidget::close();
  }
}



void SecondWindow::xC_int_recieveData   (int i){ xC = i; location(); }
void SecondWindow::yC_int_recieveData   (int i){ yC = i; location(); }
void SecondWindow::xGC_int_recieveData  (int i){ xGC = i; location(); }
void SecondWindow::yGC_int_recieveData  (int i){ yGC = i; location(); }
void SecondWindow::xGCW_int_recieveData (int i){ xGCW = i; location(); }
void SecondWindow::yGCW_int_recieveData (int i){ yGCW = i; location(); }
void SecondWindow::location(){ (this)->setGeometry(xGCW-310,yGCW,300,140); }
