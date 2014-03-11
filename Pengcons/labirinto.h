/*
Pengu - file: labirinto.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef LABIRINTO_H
#define LABIRINTO_H

#include <stdlib.h>
#include "game.h"

#include "personaggi.h"

class umano;
class ice;
class mostro;
class Game;

class labirinto{

private:

    ice * maze[20][15]; // labirinto di ghiaccioli.

    mostro ** mos; // puntatori di puntatori al tipo mostro. Per l'allocamento dinamico dell'array mostri.

    int num_mos; // contiene il numero di mostri per l'array dinamico.
    int num_mos_now; // indica il numero di mostri in gioco, viene aggiornato ogni volta.

    QString path; // conterrà l'indirizzo del tema.

 public:

    labirinto(); // costruttore.

    ~labirinto();

    void throw_ice(); // funzione che lancia i ghiaccioli.

    void visualizza_lab(umano *, Game*); // visualizza il labirinto.

    bool near_ice(int, int, int); // controlla se il ghiacciolo in questione è vicino ad un altro nella direzione di spinta e lo distrugge.

    void immetti_mostri(int); // pone i mostri sul labirinto.

    void muovi_mostri(labirinto *); // la funzione muove i mostri.

    bool manOn_mostro(umano*); // la funzione controlla che l'utente non sia su un mostro, altrimenti lo uccide. restituisce true se lo ha ucciso.

    bool verifica_pos(int, int, int); // La funzione verifica che la posizione sia libera (spostamento umano) true = libera, false = no.
    // il terzo parametro va da 0 a 3 ed indica la posizione di spinta.

    void iceOn_mostro(); // la funzione controlla che il ghiaccio non sia sopra il mostro, in caso affermativo lo uccide.

    void setOffAll(); // la funzione riporta tutti i just_t dei ghiaccioli a false per permettere il loro spostamento al prossimo richiamo della funzione.

    int return_numMosNow(); // restituisce il valore della variabile relativa.

    bool cntl_mos_pos(int, int); // controlla che il mostro si stia spostando su di una posizione libera.

    void setTheme(int); // imposta il tema.

};

#endif // LABIRINTO_H
