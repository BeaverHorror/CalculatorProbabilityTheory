#include "bernoulli.h"
#include "ui_bernoulli.h"

Bernoulli::Bernoulli(QWidget *parent) : QDialog(parent), ui(new Ui::Bernoulli) {
  ui->setupUi(this);
  QPixmap pix(":/new/prefix3/png/7.png");
  int w = ui->label_formula_1->width();
  int h = ui->label_formula_1->height();
  ui->label_formula_1->setPixmap(pix.scaled(w,h, Qt::KeepAspectRatio));
}

Bernoulli::~Bernoulli() { delete ui; }

// Решение
void Bernoulli::on_pushButton_decision_1_clicked() {
  error = 0; sign_str = "";
  answer_1_double = 0; answer_1_str = "";
  m_1_int = 0; m1_1_int = 0; m2_1_int = 0;
  n_1_int = ui->spinBox_n_1->value();
  if(ui->lineEdit_sign->text().toInt() > n_1_int) error = 1;
  p_1_double =ui->doubleSpinBox_p_1->value();
  sign_str = ui->lineEdit_sign->text();
  if(sign_str.size() == 0) error = 1;
  if(exarticulation(sign_str, 2) <  exarticulation(sign_str, 1)) error = 1;
  if(exarticulation(sign_str, 7) > 30){
    m1_1_int = exarticulation(sign_str, 1); m2_1_int = exarticulation(sign_str, 2); if(m1_1_int > n_1_int || m2_1_int > n_1_int ) error = 1;
    if(error == 0){
      if(exarticulation(sign_str, 7) == 31) for(int i = m1_1_int+1; i < m2_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 32) for(int i = m1_1_int; i < m2_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 33) for(int i = m1_1_int+1; i <= m2_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 34) for(int i = m1_1_int; i <= m2_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double); }}
      if(exarticulation(sign_str, 7) < 30){ m_1_int = exarticulation(sign_str, 0); if(m_1_int > n_1_int) error = 1;
    if(error == 0){
      if(exarticulation(sign_str, 7) == 21) for(int i = m_1_int+1; i < n_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 22) for(int i = m_1_int; i < n_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 23) for(int i = m_1_int+1; i <= n_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 24) for(int i = m_1_int; i <= n_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 25) for(int i = 0; i < m_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 26) for(int i = 0; i <= m_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 27) for(int i = 0; i < m_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 28) for(int i = 0; i <= m_1_int; i++) answer_1_double = answer_1_double + bernoulli(n_1_int, i, p_1_double);
      if(exarticulation(sign_str, 7) == 11)  answer_1_double = bernoulli(n_1_int, exarticulation(sign_str, 0), p_1_double);}}
  if(answer_1_double > 1) error = 1;
  if(exarticulation(sign_str, 9) == 0 && error == 0) answer_1_str = "Ответ: "; answer_1_str = answer_1_str.append( QString::number(answer_1_double, 'g', 15));
  if(exarticulation(sign_str, 9) == 1 || error == 1) answer_1_str = "Error";
  ui->label_answer_1->setText(answer_1_str);
}
// Факториала
int Bernoulli::factorial(int i){
  if (i){
    int n = 1;
    for(int a = 2; a <= i; a++) n*=a;
    return n;
  }
  else return 1;
}
// Сочетания без повторений
int Bernoulli::soch(int n, int m){
  return factorial(n) / (factorial(n - m) * factorial(m));
}
// Формула Бернулли
double Bernoulli::bernoulli(int n, int k, double p) {
  return soch(n, k)* pow(p, k)* pow((1 - p), n - k);
}
// Закрытие
void Bernoulli::close_recieveData(int i){
  if (i == 1){
    QWidget::close();
  }
}
// В функцию подаётся строка вида "a < m <= b" и возвращается число
int Bernoulli::exarticulation(QString str, int num){
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
  if(sig1 == 1 && sig2 == 0 && sig3 == 0 && index_m != 0){ for(int i = 0; i < index_11; i++) m_str.append(str.at(i)); mod = 21; m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 1 && index_m != 0){ for(int i = 0; i < index_11; i++) m_str.append(str.at(i)); mod = 22; m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 0 && index_m == 0){ for(int i = 2; i < str.size(); i++) m_str.append(str.at(i)); mod = 23; m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 1 && index_m == 0){ for(int i = 3; i < str.size(); i++) m_str.append(str.at(i)); mod = 24; m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 0 && index_m == 0){ for(int i = 2; i < str.size(); i++) m_str.append(str.at(i)); mod = 25; m_int = m_str.toInt();}
  if(sig1 == 1 && sig2 == 0 && sig3 == 1 && index_m == 0){ for(int i = 3; i < str.size(); i++) m_str.append(str.at(i)); mod = 26; m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 0 && index_m != 0){ for(int i = 0; i < index_21; i++) m_str.append(str.at(i)); mod = 27; m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 1 && sig3 == 1 && index_m != 0){ for(int i = 0; i < index_21; i++) m_str.append(str.at(i)); mod = 28; m_int = m_str.toInt();}
  if(sig1 == 0 && sig2 == 0 && sig3 == 0){mod = 11; m_int = str.toInt(); }
  if(num == 0) return m_int; if(num == 1) return m1_int; if(num == 2) return m2_int;
  if(num == 3) return sig1; if(num == 4) return sig2; if(num == 5) return sig3; if(num == 8) return sig4;
  if(num == 6) return str.size(); if(num == 7) return mod; if(num == 9) return error1;}



void Bernoulli::xC_int_recieveData   (int i){ xC = i;   location(); }
void Bernoulli::yC_int_recieveData   (int i){ yC = i;   location(); }
void Bernoulli::xGC_int_recieveData  (int i){ xGC = i;  location(); }
void Bernoulli::yGC_int_recieveData  (int i){ yGC = i;  location(); }
void Bernoulli::xGCW_int_recieveData (int i){ xGCW = i; location(); }
void Bernoulli::yGCW_int_recieveData (int i){ yGCW = i; location(); }
void Bernoulli::location(){ (this)->setGeometry(xGCW+370+90,yGCW+240+220,300,140); }

