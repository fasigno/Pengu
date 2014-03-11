/*
Pengu - file: game.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef GAME_H
#define GAME_H

#include <QtGui/QWidget>
#include <QPixmap>
#include <QLabel>
#include <QTimer>
#include <QObject>

#include "mosDialog.h"
#include "info.h"
#include "Pengcons/labirinto.h"
#include "Pengcons/personaggi.h"

class umano;

class Game : public QWidget
{

Q_OBJECT

QLabel *Maze_v[20][15]; // array per la visualizzazione su form del labirinto.
QTimer *timer; // il timer;

QTimer *tScreen; // timer che disegna lo schermo ogni volta.

QTimer * ready; // esegue il conto alla rovescia prima di far partire i mostri.

QStatusBar *inf; // status bar del gioco.

labirinto *lab; // puntatore a labirinto.
umano *pl; // puntatore ad umano.

int speedMonst; // la variabile indica la velocità del timer dei mostri. Default : 100.

int tema; // contiene il tema scelto dall'utente.

int n; // contiene il numero di mostri allocati all'inizio della partita. Serve per il punteggio finale.

bool finished; // indica se il gioco è concluso (caso in cui il pl venga ucciso, altrimenti esegue codice che non deve fare).

bool pause; // indica se il gioco è stato messo in pausa.

public:
    Game(QWidget *parent = 0);

    void keyPressEvent ( QKeyEvent * event );

    void setMaze(int x, int y, QPixmap*); // imposta l'array di label per la visualizzazione sul form.

    void setMonst(int); // funzione che richiama immetti mostri di labirinto.

    void end(); // funzioni richiamate alla fine del gioco.

    void end_k();

    void deleteObj(); // dealloca le risorse.

    void setSpeed(int); // imposta la velocità dei mostri.

    void setTheme(int); // imposta il tema scelto dall'utente.

    ~Game();

public slots:

    void quit();  // chiude la finestra di gioco.
    void play();  // inizia la partita.
    void info_mess(); // visualizza un messaggio info.

    void tick(); // funzione eseguita dal timer.
    void message(); // visualizza un conto alla rovescia prima di far partire il gioco.

    void view(); // funzione richiamata dal timer per disegnare lo schermo.

    void settingsClick(); // visualizza la finestra delle impostazioni.
};

#endif // GAME_H
