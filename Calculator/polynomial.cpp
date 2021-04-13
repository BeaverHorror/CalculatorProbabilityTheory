#include "polynomial.h"
#include "ui_polynomial.h"

Polynomial::Polynomial(QWidget *parent) : QDialog(parent), ui(new Ui::Polynomial) {
  ui->setupUi(this);

  QPixmap pix(":/new/prefix3/png/8.png");
  int w = ui->label_formula_2->width();
  int h = ui->label_formula_2->height();
  ui->label_formula_2->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

Polynomial::~Polynomial() { delete ui; }

void Polynomial::on_pushButton_decision_3_clicked(){
  answer_3_double = 0; error = 0; sum = 0;
  n_3_int = ui->spinBox_n_3->value();
  m_3_int[0] = ui->spinBox_m_3_1->value();
  m_3_int[1] = ui->spinBox_m_3_2->value();
  m_3_int[2] = ui->spinBox_m_3_3->value();
  m_3_int[3] = ui->spinBox_m_3_4->value();
  m_3_int[4] = ui->spinBox_m_3_5->value();
  m_3_int[5] = ui->spinBox_m_3_6->value();
  p_3_double[0] = ui->doubleSpinBox_p_3_1->value();
  p_3_double[1] = ui->doubleSpinBox_p_3_2->value();
  p_3_double[2] = ui->doubleSpinBox_p_3_3->value();
  p_3_double[3] = ui->doubleSpinBox_p_3_4->value();
  p_3_double[4] = ui->doubleSpinBox_p_3_5->value();
  p_3_double[5] = ui->doubleSpinBox_p_3_6->value();

  for(int i = 0; i< 6; i++) sum = sum + m_3_int[i];
  if (sum != n_3_int) error = 1;

  answer_3_double = polynomial(n_3_int, m_3_int, p_3_double);

  if (error == 0){
  answer_3_str = QString::number(answer_3_double, 'g', 15);
  ui->label_answer_3->setText(answer_3_str);
  }
  if (error == 1) ui->label_answer_3->setText("Error");
}

// Факториала
int Polynomial::factorial(int i){
  if (i){
    int n = 1;
    for(int a = 2; a <= i; a++) n*=a;
    return n;
  }
  else return 1;
}
// Полиномиальная формула
double Polynomial::polynomial(int n, int m[6], double p[6]){
  int nf = factorial(n);
  int mf = 1; for(int i = 0; i < 6; i++) mf = mf*factorial(m[i]);
  double pf = 1;  for(int i = 0; i < 6; i++) pf = pf * pow(p[i],m[i]);
  return (nf/mf)*pf;
}

// Закрытие
void Polynomial::close_recieveData(int i){
  if (i == 1){
    QWidget::close();
  }
}



//
void Polynomial::xC_int_recieveData   (int i){ xC = i;   location(); }
void Polynomial::yC_int_recieveData   (int i){ yC = i;   location(); }
void Polynomial::xGC_int_recieveData  (int i){ xGC = i;  location(); }
void Polynomial::yGC_int_recieveData  (int i){ yGC = i;  location(); }
void Polynomial::xGCW_int_recieveData (int i){ xGCW = i; location(); }
void Polynomial::yGCW_int_recieveData (int i){ yGCW = i; location(); }
void Polynomial::location(){ (this)->setGeometry(xGCW+370+90,yGCW,300,140); }
