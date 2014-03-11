/*
Pengu - file: personaggi.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef PERSONAGGI_H
#define PERSONAGGI_H

#include "labirinto.h"

class labirinto;

class personaggi{ // classe personaggi generica

protected:

         int pos_x, pos_y;

public:

    personaggi(); // costruttore.

    void move();

    void destroy(); // comune agli altri oggetti derivati.

    void set_x(int); // non servono per ice.

    void set_y(int); // non servono per ice.

    int return_x(); // restituisce la coordinata x dell'oggetto.

    int return_y(); // restituisce la coordinata y dell'oggetto.

};

class umano: public personaggi{

private:

public:

    umano();  // costruttore.

    void move(labirinto *, char);

};

class mostro: public personaggi{

private:

    int direction; // indica da dove proviene il mostro durante lo spostamento per evitare che torni indietro.

public:

    mostro(int, int);  // costruttore con passaggio di x e y pos iniziali.

    void move(labirinto *);

};

class ice: public personaggi{

private:

    bool thrown; // indica se il ghiacciolo è stato lanciato.

    int dir; // indica la direzione di lancio. 0,1,2,3

    bool just_t; // la variabile indica se il ghiacciolo è stato appena lanciato e quindi non c'è bisogno di spostarlo una seconda volta.

public:

    ice(); // costruttore.

    bool return_justT(); // restituisce il valore di just_t

    void setOff_justT(); // imposta il valore di just_t a false.

    void setOn_justT(); // imposta il valore a true.

    void move();

    bool return_thrown();

    int return_dir();

    void setOn_throw(int); // inizia il lancio del ghiacciolo, viene passato come parametro la direzione di spinta.

    void setOff_throw(); // ferma il lancio del ghiacciolo.

};

#endif // PERSONAGGI_H
