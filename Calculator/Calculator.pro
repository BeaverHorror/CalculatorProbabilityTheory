#-------------------------------------------------
#
# Project created by QtCreator 2020-04-02T00:21:26
#
#-------------------------------------------------
#-------------------------------------------------
#qt charts простой график средствами qt creator
#Как создать простой график функции с помощью инструментов qt creator?
#создаём новое приложение qt widgets
#подключаем модуль Charts в файле проекта
#Подключаем библиотеку QtCharts.
#Создаём объект QChart (в моём примере объект создаётся через указатель)
#На форма добавляем объект qtwidget и переопределяем его как QChartView
#В тексте программы записываем следующий код
#связываем объект QChart с объектом отображения QChartView
#Создаём и настраиваем оси x и y. В частности диапазон, число линий сетки, и формат отображения чисел.
#Создаём необходимые зависимости с помощью объектов QLineSeries.
#Прикрепляет эти зависимости к графику.
#Устанавливаем оси x и y для графика для каждой зависимости отдельно.
#-------------------------------------------------

QT       += core gui
QT       += core gui charts
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Calculator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bernoulli.cpp \
        fifthlab.cpp \
        form.cpp \
        main.cpp \
        mainwindow.cpp \
        mychart.cpp \
        poisson.cpp \
        polynomial.cpp \
        qcustomplot.cpp \
        secondwindow.cpp

HEADERS += \
        bernoulli.h \
        fifthlab.h \
        form.h \
        mainwindow.h \
        mychart.h \
        poisson.h \
        polynomial.h \
        qcustomplot.h \
        secondwindow.h

FORMS += \
        bernoulli.ui \
        fifthlab.ui \
        form.ui \
        mainwindow.ui \
        mychart.ui \
        poisson.ui \
        polynomial.ui \
        secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    other.qrc
