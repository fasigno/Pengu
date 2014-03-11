/*
Pengu - file: mosDialog.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef INSERTNAME_H
#define INSERTNAME_H

#include <QDialog>
#include <QVBoxLayout>
#include <QtGui>

#include "Pengcons/labirinto.h"
#include "Pengcons/personaggi.h"
#include "game.h"

    class QLabel;
    class QLineEdit;
    class QPushButton;
    class labirinto;
    class umano;
    class Game;

class InsertMos : public QDialog
{
Q_OBJECT

int monst; // variabile che memorizza il numero di mostri allocati dall'utente.

QVBoxLayout * w_dialog;

QLineEdit * numMos;

QLabel * text;
QPushButton * ok;

QString numMosText; // variabile che conterrà il numero di mostri da creare.

// puntatore :
Game * game1;

public:

    InsertMos(QWidget* parent=0); // costruttore.

    ~InsertMos(); // distruttore.

public slots:

    void enableFindButton(); // attiva il pulsante ok non appena si inserisce qualcosa nella line edit.

    void clicked_b(); // funzione richiamata al click dell'utente su ok.

    void setPunt(Game *); // passa un puntatore labirinto al dialogo.

};

#endif // INSERTNAME_H
