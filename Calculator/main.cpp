#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}



/*
  ui->pushButton_point->setStyleSheet(" QPushButton {font: 12pt 'Mistral'"
                                      "              background-color: rgb(244, 255, 254);"
                                      "              color: rgb(0, 0, 0);"
                                      "              border:1px solid gray"
                                      "              border-left:2px solid gray"
                                      "              border-right:2px solid gray"
                                      "              border-bottom:2px solid gray"
                                      "              border-radius: 5px"
                                      " QPushButton:pressed {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
                                      "                                        stop:0 #f4fffe, stop:1 #c2cac9}");
*/

/* Менять шрифт
int newFontSize = 7;
ui->label->setStyleSheet(QString("font-size: %1px").arg(newFontSize));
*/
