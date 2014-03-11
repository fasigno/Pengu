/*
Pengu - file: personaggi.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include "personaggi.h"

// inizio costruttori.

personaggi::personaggi(){}

ice::ice():personaggi(){
thrown = false;
just_t = false;
dir = 4; // valore che non significa niente, per evitare problemi. 0 non va bene.
}

mostro::mostro(int x, int y):personaggi() { // nel costruttore vengono passate le posizioni  x,y del mostro appena allocato.

         direction = 0;
         pos_x = x;
         pos_y = y;
}

umano::umano():personaggi(){
    // inizializza la posizione del giocatore umano. Creare un posizionamento random!

pos_x = 1;
pos_y = 1;

}

// fine costruttori.

void umano::move(labirinto * lab, char bt){ // passa il puntatore del labirinto.

    int x1 = 0, y1 = 0;

    switch(bt) {

    case 'A':  // spostamento a sx.

        x1 = pos_x-1;

        if (lab->verifica_pos(x1, pos_y, 0) == true) {pos_x = x1;}

    break;

    case 'D': // spostamento a dx.

        x1 = pos_x+1;

        if (lab->verifica_pos(x1, pos_y, 1) == true) {pos_x = x1;}

    break;

    case 'W': // spostamento a su.

        y1 = pos_y-1;

        if (lab->verifica_pos(pos_x, y1, 2) == true) {pos_y = y1;}

    break;

    case 'S': // spostamento a giù.

        y1 = pos_y+1;

        if (lab->verifica_pos(pos_x, y1, 3) == true) {pos_y = y1;}

    break;

    }

}

int personaggi::return_x(){
return pos_x;
}

int personaggi::return_y(){
return pos_y;
}

void mostro::move(labirinto * lab){ // per il mostro la direzione di spinta contro il ghiacciolo non ha importanza quindi si usa 4 che non permette ai mostri di mangiare i ghiaccioli.
    // ma a me di usare la stessa funzione.

    // legenda variabile direction:
    // assume i valori:
    // 1 = SX, 2 = DX, 3 = SU, 4 = GIù.
    // secondo da dove proviene il mostro.

    // randomizza lo spostamento del mostro.

    srand(time(NULL));

    bool moved= false; // indica se il mostro è stato spostato.
    int pos = 0;

    int times = 0; // conta il numero di volte che si è tentato uno spostamento, dopo 4 tentativi smette.

    while(moved != true) {

        int x1 = 0, y1 = 0;

        switch (direction){

            case 1: // proviene da sx.

                while((pos = rand() % 4) == 0); // non deve simulare lo spostamento a sx.

            break;

            case 2: // proviene da dx.

                while((pos = rand() % 4) == 1); // non deve simulare lo spostamento a dx.

            break;

            case 3: // proviene da su.

                while((pos = rand() % 4) == 2); // non deve simulare lo spostamento su.

            break;

            case 4: // proviene da giu.

                while((pos = rand() % 4) == 3); // non deve simulare lo spostamento giu.

            break;

            default:

                pos = rand() % 4; // simula un numero tra 0 e 3. che indica le direzioni spostamento giù, su, dx, sx.

            break;

        }

        // pos = rand() % 4; // simula un numero tra 0 e 3. che indica le direzioni spostamento giù, su, dx, sx.

        times++;

        switch(pos){

        case(0):  // spostamento sx.

            x1 = pos_x-1;

            if (lab->verifica_pos(x1, pos_y, 4) == true) {pos_x = x1; direction = 2; moved = true;}

            break;

        case(1):  // spostamento dx.

            x1 = pos_x+1;

            if (lab->verifica_pos(x1, pos_y, 4) == true) {pos_x = x1; direction = 1; moved = true;}

            break;

        case(2):  // spostamento su.

            y1 = pos_y-1;

            if (lab->verifica_pos(pos_x, y1, 4) == true) {pos_y = y1; direction = 4; moved = true;}

            break;

        case(3):  // spostamento giù.

            y1 = pos_y+1;

            if (lab->verifica_pos(pos_x, y1, 4) == true) {pos_y = y1; direction = 3; moved = true;}

            break;

        } // fine switch.

        if (times >= 4){ direction = 4; break;} // se è stato provato lo spostamento 4 volte (o più) smette.


    } // fine while.

}

void personaggi::destroy(){

delete this;

}


bool ice::return_thrown() {

return thrown;

}

int ice::return_dir() {

return dir;

}

void personaggi::set_x(int x){

pos_x = x;

}

void personaggi::set_y(int y){

pos_y = y;

}

void ice::setOn_throw(int dir1){ // parametro direzione di lancio.

    thrown = true;
    dir = dir1;

}

void ice::setOff_throw(){

    thrown = false;
    dir = 4; // valore insignificante.

}

bool ice::return_justT(){

    return just_t;
}

void ice::setOff_justT(){ // imposta il valore a false.

    just_t = false;
}

void ice::setOn_justT(){

just_t = true;

}
