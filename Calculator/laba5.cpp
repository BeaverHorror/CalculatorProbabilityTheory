#include "laba5.h"
#include "ui_laba5.h"
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <QFileInfo>

laba5::laba5(QWidget *parent) :  QMainWindow(parent), ui(new Ui::laba5) {
  ui->setupUi(this); 
  // Работа с директориями и путями
  currentPath = QDir::currentPath();                       // Директория исполняемого файла
  currentPath.replace("/", "\\\\");                        // Заменить символы / на \\
  Data_txt = "\\\\Data.txt";                               //
  Data_txt.prepend(currentPath);                           // Вписать перед именем приложения каталог
  strcpy(Data_txt_char, Data_txt.toUtf8().data());         // Переписать Data_txt (QString) в Data_txt_char (char)
  strcpy(currentPath_char, currentPath.toUtf8().data());   // Переписать currentPath (QString) в currentPath_char (char)
}

laba5::~laba5() { delete ui; }


void laba5::on_pushButton_action_clicked(){
  ui->label->setText("");

  // Создаём объект
  QFile file(Data_txt_char);

  // С помощью метода open() открываем файл в режиме чтения
  if (!file.open(QIODevice::ReadOnly)) {

  }

  // Создаём входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
  QTextStream in(&file);

  // Считываем файл строка за строкой
  while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
    QString line = in.readLine(); // метод readLine() считывает одну строку из потока

  }

  // Закрываем файл
  file.close();


}

