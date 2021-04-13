#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
}
Form::~Form() { delete ui; }

void Form::number_str_recieveData(QString str){
  ui->label_number_str->setText(str);
}
void Form::first_str_recieveData(QString str){
  ui->label_first_str->setText(str);
}
void Form::second_str_recieveData(QString str){
  ui->label_second_str->setText(str);
}
void Form::result_str_recieveData(QString str){
  ui->label_result_str->setText(str);
}
void Form::n_str_recieveData(QString str){
  ui->label_n_str->setText(str);
}
void Form::m_str_recieveData(QString str){
  ui->label_m_str->setText(str);
}
void Form::operation_str_recieveData(QString str){
  ui->label_operation_str->setText(str);
}
void Form::key_str_recieveData(QString str){
  ui->label_key->setText(str);
}

void Form::p1_str_recieveData(QString str){
  ui->label_p1->setText(str);
}
void Form::p2_str_recieveData(QString str){
  ui->label_p2->setText(str);
}
void Form::p3_str_recieveData(QString str){
  ui->label_p3->setText(str);
}
void Form::p4_str_recieveData(QString str){
  ui->label_p4->setText(str);
}
void Form::p5_str_recieveData(QString str){
  ui->label_p5->setText(str);
}
void Form::t0_int_recieveData(int i){
  ui->spinBox_t0->setValue(i);
}
void Form::t1_int_recieveData(int i){
  ui->spinBox_t1->setValue(i);
}
void Form::t2_int_recieveData(int i){
  ui->spinBox_t2->setValue(i);
}
void Form::t3_int_recieveData(int i){
  ui->spinBox_t3->setValue(i);
}

void Form::n_char_recieveData(QString str){
  ui->label_n_char->setText(str);
}
void Form::m_char_recieveData(QString str){
  ui->label_m_char->setText(str);
}

void Form::number_double_recieveData(double d){
  ui->doubleSpinBox_number->setValue(d);
}
void Form::first_double_recieveData(double d){
  ui->doubleSpinBox_first->setValue(d);
}
void Form::second_double_recieveData(double d){
  ui->doubleSpinBox_second->setValue(d);
}
void Form::result_double_recieveData(double d){
  ui->doubleSpinBox_result->setValue(d);
}
void Form::n_double_recieveData(double d){
  ui->doubleSpinBox_n->setValue(d);
}
void Form::m_double_recieveData(double d){
  ui->doubleSpinBox_m->setValue(d);
}

void Form::number_size_int_recieveData(int i){
  ui->spinBox_number_size->setValue(i);
}
void Form::first_int_recieveData(int i){
  ui->spinBox_int_first->setValue(i);
}
void Form::result_int_recieveData(int i){
  ui->spinBox_int_result->setValue(i);
}
void Form::n_int_recieveData(int i){
  ui->spinBox_int_n->setValue(i);
}
void Form::m_int_recieveData(int i){
  ui->spinBox_int_m->setValue(i);
}
void Form::mode_int_recieveData(int i){
  ui->spinBox_mode->setValue(i);
}
void Form::num_int_recieveData(int i){
  ui->spinBox_num->setValue(i);
}
void Form::equally_int_recieveData(int i){
  ui->spinBox_equally->setValue(i);
}
void Form::direction_int_recieveData(int i){
  ui->spinBox_direction->setValue(i);
}
void Form::zero_int_recieveData(int i){
  ui->spinBox_zero->setValue(i);
}

void Form::currentPath_recieveData(QString str){
  ui->label_currentPath->setText(str);
}
void Form::combinatorics_name_Path_recieveData(QString str){
  ui->label_combinatorics_name->setText(str);
}
