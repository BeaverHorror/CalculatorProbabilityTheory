#ifndef CHART_H
#define CHART_H

#include <QDialog>

namespace Ui {
class Chart;
}

class Chart : public QDialog
{
  Q_OBJECT

public:
  explicit Chart(QWidget *parent = nullptr);
  ~Chart();

private:
  Ui::Chart *ui;
};

#endif // CHART_H
