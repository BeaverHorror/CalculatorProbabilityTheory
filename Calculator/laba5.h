#ifndef LABA5_H
#define LABA5_H

#include <QMainWindow>

namespace Ui { class laba5; }
class laba5 : public QMainWindow { Q_OBJECT
public:
  explicit laba5(QWidget *parent = nullptr); ~laba5();
  QString currentPath;               // Текущий каталог
  char currentPath_char[255];        //
  QString Data_txt;                  //
  char Data_txt_char[255];           //
  double d[100];                     //
  QString d_str;                     //
private slots:
  void on_pushButton_action_clicked();

private:
  Ui::laba5 *ui;
};

#endif // LABA5_H
