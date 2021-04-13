#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) : QDialog(parent), ui(new Ui::Chart) {
  ui->setupUi(this);
}

Chart::~Chart()
{
  delete ui;
}
