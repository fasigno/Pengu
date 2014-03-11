/*
Pengu - file: labirinto.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <ctime>

#include "labirinto.h"
#include "game.h"

labirinto::labirinto(){

    QFile lab("./mazes/maze.txt");

    if (!lab.open(QIODevice::ReadOnly | QIODevice::Text)) {

        lab.setFileName(":/res/maze.txt");
        lab.open(QIODevice::ReadOnly | QIODevice::Text);
    }

    int i=0, j=0;

    while(!lab.atEnd()){

          QByteArray a = lab.readLine();

          while(a[j] != '/') {

              if (a[j] == '*') {maze[j][i] = new ice; // si alloca un nuovo oggetto ghiacciolo nell'array.

              } else if (a[j] == '-') {maze[j][i] = NULL;}  // altrimenti il puntatore non punta a nulla.

              j++;

          }

          i++; j=0;

    }

    lab.close();

    path = "standard"; // inizializzazione tema.


    //Old code::

    //std::fstream lab;

    //     lab.open("./mazes/maze.txt", std::ios::in);

    //     if (lab.fail()) {
    //        lab.open(":/res/maze.txt", std::ios::in);
    //     }

    //char a[23] = ""; // carattere di appoggio stringa stile c.

    //                 lab.getline(a, 23); //  21 caratteri più terminatore.

    //             while(a[j] != '/') {

    //                 if (a[j] == '*') {maze[j][i] = new ice; // si alloca un nuovo oggetto ghiacciolo nell'array.

    //                 } else if (a[j] == '-') {maze[j][i] = NULL;}  // altrimenti il puntatore non punta a nulla.

    //                j++;

    //             }

    //             i++; j=0;

    //    }

    //lab.close();



} // fine costruttore.

void labirinto::visualizza_lab(umano *pl, Game *w){ // passaggi del puntatore giocatore umano.

    // inizio caricamento array di caratteri di supporto.

    char maze_app[20][15]; // array di caratteri di appoggio per il disegno a schermo.

    // inizializzazione maze_app:

         for(int i=0; i < 15; i++)
         for(int j=0; j < 20; j++){

          maze_app[j][i] = ' ';


         }

    // fine inizializzazione.

         for(int i=0; i < 15; i++){
             for(int j=0; j < 20; j++)

             {
                 if (maze[j][i] != NULL) {
                     maze_app[j][i] = '*';
                 }

             }
         }


    if (pl != NULL) {
    maze_app[pl->return_x()][pl->return_y()] = 'A'; // pone il giocatore.
    }

    for(int i=0; i < num_mos; i++){

        if (mos[i] != NULL) // controllo per evitare il segmentation fault.
        maze_app[mos[i]->return_x()][mos[i]->return_y()] = 'Y'; // disegna il mostro.

    }


    // fine caricamento array di caratteri.


    // visualizzazione array partendo da quello di caratteri caratteri fino al form.

        QPixmap *image_i = new QPixmap(":/res/themes/" + path + "/ice.gif"); // immagine ghiaccioli.
        QPixmap *image_b = new QPixmap(":/res/themes/" + path + "/blank.gif"); // immagine vuota.
        QPixmap *image_f = new QPixmap(":/res/themes/" + path + "/casp.gif"); // immagine fantasmi.
        QPixmap *image_p = new QPixmap(":/res/themes/" + path + "/pengu.gif"); // immagine pinguino.

    for(int i=0; i < 15; i++)
         for(int j=0; j < 20; j++){

             switch(maze_app[j][i]){

             case '*':

                 w->setMaze(j, i, image_i);

                 break;

             case ' ':

                 w->setMaze(j, i, image_b);

                 break;

             case 'A':

                 w->setMaze(j, i, image_p);

                 break;

             case 'Y':

                 w->setMaze(j, i, image_f);

                 break;

            } // fine switch.

     } // fine ciclo for.


} // fine metodo.

void labirinto::immetti_mostri(int num){
    // la posizione dei mostri é casuale!

    int x = 0, y = 0;

    mos = new mostro*[num];

    // inizializzazione array mos.

        for(int i=0; i < num; i++){

            mos[i] = NULL;

        }

    // fine inizializzazione array mos.

    num_mos = num; // variabile di appoggio per tutti i membri della classe.
    num_mos_now = num; // variabile che indica quanti mostri ci sono ancora vivi.

    srand(time(NULL));

    for(int i=0; i < num; i++){

    // codice di creazione mostri.

        while(true) {

        // simulazione coordinate mostri.

        x = rand() % 21; // simula un numero tra 0 e 20.
        y = rand() % 16; // simula un numero tra 0 e 15.

        bool busy = false; // variabile booleana che indica se la posizione in questione è occupata da altri mostri.
        // true = occupata.

        // controllo che la posizione non sia occupata da altri mostri.

        for(int i=0; i<num; i++){

            if(mos[i] != NULL && mos[i]->return_x() == x && mos[i]->return_y() == y) busy = true;

        }

        if (busy == false && x != 1 && y != 1 && maze[x][y] == NULL) break; // se la posizione nel labirinto è vuota e non è occupata dal player viene creato il mostro in quelle coordinate.

        }

        mos[i] = new mostro(x,y);

    }


}

void labirinto::muovi_mostri(labirinto * lab){ // fare un controllo sulla sovrapposizione dei mostri.

     for(int i=0; i<num_mos; i++){

         if (mos[i] != NULL) mos[i]->move(lab);

     }

}


bool labirinto::near_ice(int x, int y, int dir){ // coordinate occupate dal ghiacciolo. Dir : direzione di spinta.
    // la funzione restituisce true se il ghiacciolo viene distrutto.

        switch(dir){ // ottimizzare assolutamente togliendo un case.

        case(0):  // spostamento sx.

            // se c'è un ghiacciolo alla sx.

            if (maze[x-1][y] != NULL) {maze[x][y]->destroy(); maze[x][y] = NULL; return true;}

            break;

        case(1):  // spostamento dx.

            if (maze[x+1][y] != NULL) {maze[x][y]->destroy(); maze[x][y] = NULL; return true;}

            break;

        case(2):  // spostamento su.

            if (maze[x][y-1] != NULL) {maze[x][y]->destroy(); maze[x][y] = NULL; return true;}

            break;

        case(3):  // spostamento giù.

            if (maze[x][y+1] != NULL) {maze[x][y]->destroy(); maze[x][y] = NULL; return true;}

            break;

        case(4): // eventuale spinta del mostro.

            return true; // serve per evitare che lo spostamento dei mostri fermi i ghiaccioli lanciati!!!

            break;
        }

return false;

}

bool labirinto::cntl_mos_pos(int x, int y){

    for(int i = 0; i < num_mos; i++) {
    if(mos[i] != NULL && mos[i]->return_x() == x && mos[i]->return_y() == y) return false;
    }

    return true;

}

bool labirinto::verifica_pos(int x, int y, int dir){ // migliorare la sintassi.

    if (0 <= x && x <= 20 && 0 <= y && y <= 15){ // controllo che non vada fuori dall'array.

        if (maze[x][y] == NULL) { // se il posto non è occupato da nessuno, va bene per l'utente, ma non per il mostro che può sovrapporsi ad altri mostri.

            // 4 è la direzione di spostamento del mostro, che non ha alcun significato ma verrà usata qui per indicare che lo spostamento è del mostro.
            if (dir == 4 && cntl_mos_pos(x, y) == false){ // richiamo funzione controllo pos mostro non sovrapposta.

            return false; // posizione occupata

            } else {return true;} // se la posizione è libera e non è un mostro a spostarsi viene restituito true.

        } else if(1<=x && x<=18 && 1<=y && y <= 13) {  // controllo che evita il segmentation fault.

            // se la posizione è occupata da un ghiacciolo, questo viene o lanciato o distrutto.

                            if (near_ice(x,y,dir) != true){ // se il ghiacciolo non è stato distrutto perchè non adiacente ad altro, verrà lanciato.

                                 maze[x][y]->setOn_throw(dir); // viene impostato il lancio del ghiacciolo.

                            } // fine if ghiacciolo lanciato.


         } else {return false;} // fine controllo segmentation fault.


    } // fine if generale controllo coordinate.

    return false;

} // fine metodo verifica_pos().

bool labirinto::manOn_mostro(umano* pl){
       // controllo se posizione occupata da mostro:

        for (int i =0; i< num_mos; i++)
            if (mos[i] != NULL && mos[i]->return_x() == pl->return_x() && mos[i]->return_y() == pl->return_y()) {

                pl->destroy();
                pl = NULL; // perchè non funziona ? lo ridefinisco null nel game.cpp

                return true;

            }

        return false;
}

void labirinto::throw_ice(){

       for(int i=0; i < 15; i++){
           for(int j=0; j < 20; j++){

               if(maze[j][i] != NULL && maze[j][i]->return_thrown() == true && maze[j][i]->return_justT() == false){ // se il ghiacciolo esiste ed è stato lanciato.

                   int x1=0, y1=0;

                   switch(maze[j][i]->return_dir()){ // si prosegue nel lancio, conoscendo la sua direzione. (si spostano i puntatori)

                       case(0): // spostamento a sx.

                       x1 = j-1;

                       if (x1 > 0 && maze[x1][i] == NULL) {maze[x1][i] = maze[j][i]; maze[j][i] = NULL; maze[x1][i]->setOn_justT();} else {maze[j][i]->setOff_throw();}

                       break;

                       case(1): // spostamento a dx.

                       x1 = j+1;

                       if (x1 < 19 && maze[x1][i] == NULL) {maze[x1][i] = maze[j][i]; maze[j][i] = NULL; maze[x1][i]->setOn_justT();} else {maze[j][i]->setOff_throw();}

                       break;

                       case(2): // spostamento su.

                       y1 = i-1;

                       if (y1 > 0 && maze[j][y1] == NULL) {maze[j][y1] = maze[j][i]; maze[j][i] = NULL; maze[j][y1]->setOn_justT();} else {maze[j][i]->setOff_throw();}

                       break;

                       case(3): // spostamento giù.

                       y1 = i+1;

                       if (y1 < 14 && maze[j][y1] == NULL) {maze[j][y1] = maze[j][i]; maze[j][i] = NULL; maze[j][y1]->setOn_justT();} else {maze[j][i]->setOff_throw();}

                       break;


                   } // fine switch.


               } // fine if lancio ghiacciolo.

           } // fine secondo ciclo for annidato.



       } // fine primo ciclo for.

       setOffAll();

} // fine metodo throw_ice().


void labirinto::iceOn_mostro(){

    for (int i=0; i< num_mos; i++) {

        for(int j=0; j < 15; j++){
            for(int k=0; k < 20; k++){

                // se c'è il ghiacciolo e il mostro e le sue coordinate sono coincidenti con il mostro, il mostro viene ucciso.
                if (maze[k][j] != NULL && mos[i] != NULL && mos[i]->return_x() == k && mos[i]->return_y() == j) {

                    mos[i]->destroy();
                    mos[i] = NULL;

                    num_mos_now--;

                }

            }
        }
    }


} // fine iceOnmostro().

labirinto::~labirinto(){ // distruttore.

    delete [] mos;

}

void labirinto::setOffAll(){ // riporta a false tutti i ghiaccioli lanciati.

      for(int j=0; j < 15; j++)
            for(int k=0; k < 20; k++){

       if (maze[k][j] != NULL) maze[k][j]->setOff_justT();

      }

}

int labirinto::return_numMosNow() {
return num_mos_now;
}

void labirinto::setTheme(int t) {

    switch(t) {

    case 0: path = "standard";
        break;

    case 1: path = "disney";
        break;

    case 2: path = "yogi";
        break;

    case 3: path = "flinstones";
        break;

    case 4: path = "titti";
        break;

    case 5: path = "tunes";
        break;

    }


}
