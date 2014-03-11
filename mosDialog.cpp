/*
Pengu - file: mosDialog.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include "mosDialog.h"

InsertMos::InsertMos(QWidget * parent) : QDialog(parent) // costruttore.
{
numMosText="";

monst = 0;

w_dialog = new QVBoxLayout(this);

text = new QLabel(tr("Inserisci il numero di mostri con cui giocare :"));
numMos = new QLineEdit;
text->setBuddy(numMos);

ok = new QPushButton("Ok");
ok->setDefault(true);
ok->setEnabled(false);

w_dialog->addWidget(text);
w_dialog->addWidget(numMos);
w_dialog->addWidget(ok);

connect(numMos, SIGNAL(textChanged(const QString &)),
this, SLOT(enableFindButton()));

connect(ok, SIGNAL(clicked()),
this, SLOT(clicked_b()));

  setLayout(w_dialog);
  setWindowTitle(tr("Creazione mostri avversari"));
  setFixedHeight(sizeHint().height());
  setFixedWidth(sizeHint().width());

}

InsertMos::~InsertMos(){} // distruttore.

void InsertMos::enableFindButton(){
    ok->setEnabled(true);
}

void InsertMos::clicked_b(){

    numMosText = numMos->text(); // prelievo del numero.

    // conversione del numero in intero:
    bool conv = true; //variabile che indica se la conversione va a buon fine.

    monst = numMosText.toInt(&conv, 10);

    if (conv == true){ // se la conversione è andata a buon fine:

        game1->setMonst(monst);

    }

    this->close();
    // this->deleteLater();

}

void InsertMos::setPunt(Game * punt) {
    game1 = punt;
}
