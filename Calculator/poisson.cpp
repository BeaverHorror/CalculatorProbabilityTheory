#include "poisson.h"
#include "ui_poisson.h"

Poisson::Poisson(QWidget *parent) : QDialog(parent), ui(new Ui::Poisson) {
  ui->setupUi(this);

  QPixmap pix(":/new/prefix3/png/9.png");
  int w = ui->label_formula_3->width();
  int h = ui->label_formula_3->height();
  ui->label_formula_3->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

Poisson::~Poisson() { delete ui; }

void Poisson::on_pushButton_decision_2_clicked() {
  error = 0; answer_2_double = 0;
  m_2_int = 0; m1_2_int = 0; m2_2_int = 0;

  n_2_int = ui->spinBox_n_2->value();

  p_2_double = ui->doubleSpinBox_p_2->value();

  m_2_str = ui->lineEdit_sign_2->text();
  if(m_2_str.size() == 0) error = 1;

  if(exarticulation(m_2_str, 1) > n_2_int || exarticulation(m_2_str, 2) > n_2_int || exarticulation(m_2_str, 0) > n_2_int) error = 1;
  if(exarticulation(m_2_str, 2) <  exarticulation(m_2_str, 1)) error = 1;

  if(exarticulation(m_2_str, 7) > 30){
    m1_2_int = exarticulation(m_2_str, 1); m2_2_int = exarticulation(m_2_str, 2); if(m1_2_int > n_2_int || m2_2_int > n_2_int ) error = 1;
     if(error == 0){
    if(exarticulation(m_2_str, 7) == 31) for(int i = m1_2_int+1; i < m2_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 32) for(int i = m1_2_int; i < m2_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 33) for(int i = m1_2_int+1; i <= m2_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 34) for(int i = m1_2_int; i <= m2_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double); }}
  if(exarticulation(m_2_str, 7) < 30){
    m_2_int = exarticulation(m_2_str, 0); if(m_2_int > n_2_int) error = 1;
     if(error == 0){
    if(exarticulation(m_2_str, 7) == 21) for(int i = m_2_int+1; i < n_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 22) for(int i = m_2_int; i < n_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 23) for(int i = m_2_int+1; i <= n_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 24) for(int i = m_2_int; i <= n_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 25) for(int i = 0; i < m_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 26) for(int i = 0; i <= m_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 27) for(int i = 0; i < m_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 28) for(int i = 0; i <= m_2_int; i++) answer_2_double = answer_2_double + poisson(n_2_int, i, p_2_double);
    if(exarticulation(m_2_str, 7) == 11) answer_2_double = poisson(n_2_int, exarticulation(m_2_str, 0), p_2_double);}}

    if(answer_2_double > 1) error = 1;
    if(m_2_int > 12) error = 1;
    if(m1_2_int > 12 || m2_2_int > 12) error = 1;

    if(exarticulation(m_2_str, 9) == 0 && error == 0){
      answer_2_str = "Ответ: "; answer_2_str = answer_2_str.append( QString::number(answer_2_double, 'g', 15));
      if(answer_2_double == 0) answer_2_str = "Вероятность ничтожна";
    }
  if(exarticulation(m_2_str, 9) == 1 || error == 1) answer_2_str = "Error";
  if(answer_2_double == 0) answer_2_str = "Вероятность ничтожна";
  ui->label_answer_2->setText(answer_2_str);
}


// Факториала
int Poisson::factorial(int i){
  if (i){
    int n = 1;
    for(int a = 2; a <= i; a++) n*=a;
    return n;
  }
  else return 1;
}
// Формула Пуассона
double Poisson::poisson(int n, int m, double p){
  return (pow((n * p), m)/factorial(m))*pow(M_E,(-1*(n * p)));
}
// В функцию подаётся строка вида "a < m <= b" и возвращается число
int Poisson::exarticulation(QString str, int num){
  int index_11 = 0; int index_12 = 0; int index_21 = 0; int index_22 = 0; int index_31 = 0; int index_32 = 0;
  int sig1 = 0; int sig2 = 0; int sig3 = 0; int sig4 = 0;
  int index_m; int mod = 0; int error1 = 0;
  QString m1_str = ""; int m1_int = 0;
  QString m2_str = ""; int m2_int = 0;
  QString m_str = ""; int m_int = 0;


  for(int i  = 0; i < str.size(); i++){
    if( str.at(i) == '1' || str.at(i) == '2' || str.at(i) == '3' || str.at(i) == '4' || str.at(i) == '5' || str.at(i) == '>' ||
        str.at(i) == '6' || str.at(i) == '7' || str.at(i) == '8' || str.at(i) == '9' || str.at(i) == '0'|| str.at(i) == '<'||
        str.at(i) == 'm' || str.at(i) == '='){}
    else error1 = 1; }


  for(int i = 0; i < str.size(); i++){
    if(str.at(i) == '<') { sig1++; if(sig1 == 1) index_11 = i; if(sig1 == 2) index_12 = i;}
    if(str.at(i) == '>') { sig2++; if(sig2 == 1) index_21 = i; if(sig2 == 2) index_22 = i; }
    if(str.at(i) == '=') { sig3++; if(sig3 == 1) index_31 = i; if(sig3 == 2) index_32 = i; }
    if(str.at(i) == 'm') { sig4++; if(sig4 == 1) index_m = i; }}

  if(sig1 > 2) error1 = 1;
  if(sig2 > 2) error1 = 1;
  if(sig3 > 2) error1 = 1;
  if(sig4 > 1) error1 = 1;
  if((sig1 + sig2 + sig3) > 4) error1 = 1;
  if((sig1 + sig2 + sig3) > 2 && sig2 > 0) error1 = 1;

  if(sig1 == 2 && sig2 == 0 && sig3 == 0){ for(int i = 0; i < index_11; i++) m1_str.append(str.at(i));
    for(int i = index_12+1; i < str.size(); i++) m2_str.append(str.at(i)); mod = 31; m1_int = m1_str.toInt(); m2_int = m2_str.toInt();}
  if(sig1 == 2 && sig2 == 0 && sig3 == 1 && (index_31 > index_m)){ for(int i = 0; i < index_11; i++) m1_str.append(str.at(i));
    for(int i = index_31+1; i < str.size(); i++)  m2_str.append(str.at(i)); mod = 32; m1_int = m1_str.toInt(); m2_int = m2_str.toInt(); }
  if(sig1 == 2 && sig2 == 0 && sig3 == 1 && (index_31 < index_m)){ for(int i = 0; i < index_11; i++) m1_str.append(str.at(i));
    for(int i = index_12+1; i < str.size(); i++)  m2_str.append(str.at(i)); mod = 33; m1_int = m1_str.toInt(); m2_int = m2_str.toInt();}
  if(sig1 == 2 && sig2 == 0 && sig3 == 2){ for(int i = 0; i < index_11; i++) m1_str.append(str.at(i)); for(int i = index_32+1;
         i < str.size(); i++) m2_str.append(str.at(i)); mod = 34; m1_int = m1_str.toInt(); m2_int = m2_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 0 && index_m != 0){ for(int i = 0; i < index_11; i++) m_str.append(str.at(i)); mod = 21;
    m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 1 && index_m != 0){ for(int i = 0; i < index_11; i++) m_str.append(str.at(i)); mod = 22;
    m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 0 && index_m == 0){ for(int i = 2; i < str.size(); i++) m_str.append(str.at(i)); mod = 23;
    m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 1 && index_m == 0){ for(int i = 3; i < str.size(); i++) m_str.append(str.at(i)); mod = 24;
    m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 0 && index_m == 0){ for(int i = 2; i < str.size(); i++) m_str.append(str.at(i)); mod = 25;
    m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 1 && index_m == 0){ for(int i = 3; i < str.size(); i++) m_str.append(str.at(i)); mod = 26;
    m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 0 && index_m != 0){ for(int i = 0; i < index_21; i++) m_str.append(str.at(i)); mod = 27;
    m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 1 && index_m != 0){ for(int i = 0; i < index_21; i++) m_str.append(str.at(i)); mod = 28;
    m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 0 && sig3 == 0){mod = 11; m_int = str.toInt(); }
  if(num == 0) return m_int; if(num == 1) return m1_int; if(num == 2) return m2_int;
  if(num == 3) return sig1; if(num == 4) return sig2; if(num == 5) return sig3; if(num == 8) return sig4;
  if(num == 6) return str.size(); if(num == 7) return mod; if(num == 9) return error1;}

// Закрытие
void Poisson::close_recieveData(int i){
  if (i == 1){
    QWidget::close();
  }
}


//
void Poisson::xC_int_recieveData   (int i){ xC = i;   location(); }
void Poisson::yC_int_recieveData   (int i){ yC = i;   location(); }
void Poisson::xGC_int_recieveData  (int i){ xGC = i;  location(); }
void Poisson::yGC_int_recieveData  (int i){ yGC = i;  location(); }
void Poisson::xGCW_int_recieveData (int i){ xGCW = i; location(); }
void Poisson::yGCW_int_recieveData (int i){ yGCW = i; location(); }
void Poisson::location(){ (this)->setGeometry(xGCW+370+90,yGCW+270,300,140); }
