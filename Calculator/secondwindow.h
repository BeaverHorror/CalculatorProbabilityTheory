#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QDir>

namespace Ui { class SecondWindow; }
class SecondWindow : public QDialog { Q_OBJECT
public:
  explicit SecondWindow(QWidget *parent = nullptr); ~SecondWindow();
  QString currentPath;               // возвращает текущий каталог
  char currentPath_char[255];
  QString png_name;                  // Имя картинки
  char png_name_char[255];
  int xC, yC, xGC, yGC, xGCW, yGCW;
public slots:
  void formula_recieveData (int i);
  void close_recieveData(int i);
  void xC_int_recieveData    (int i);
  void yC_int_recieveData  (int i);
  void xGC_int_recieveData (int i);
  void yGC_int_recieveData (int i);
  void xGCW_int_recieveData  (int i);
  void yGCW_int_recieveData(int i);
  void location();
private:
  Ui::SecondWindow *ui;
};

#endif // SECONDWINDOW_H
