/*
Pengu - file: main.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include <QtGui/QApplication>

#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Qt linguistic code loader:

    QTranslator translator;
    qWarning() << translator.load(":/pengu_en");
    a.installTranslator(&translator);

     QPixmap pixmap(":/res/casperpaura.jpg");
     QSplashScreen splash(pixmap);
     splash.show();

    Game w;

     w.show();

    splash.finish(&w);

    return a.exec();
}

