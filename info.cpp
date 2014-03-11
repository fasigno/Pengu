/*
Pengu - file: info.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "info.h"

info::info()
{
    QVBoxLayout * w_dialog = new QVBoxLayout(this);
    QPushButton *close = new QPushButton("OK");
    QLabel * text = new QLabel;

    text->setText(tr("- PENGU - \n\nProgetto d'esame - Programmazione ad oggetti in c++,\ncorso di laurea in ingegneria informatica. \n\n Fabrizio Signoretti, fasigno37@gmail.com \n\nRepository: github.com/fasigno/Pengu \n\nAmbiente: QT Creator - QT 4.8.5.\n\nUnder GPLv3\nParma 2009/2010"));
    w_dialog->addWidget(text);
    w_dialog->addWidget(close);

    QObject::connect(close, SIGNAL(clicked()),
    this, SLOT(quit()));

    setWindowTitle(tr("Info"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());

    setLayout(w_dialog);
}

void info::quit(){
    this->close();
    //this->deleteLater();
}
