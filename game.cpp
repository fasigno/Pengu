/*
Pengu - file: game.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include <QtGui/QApplication>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QGridLayout>
#include <QMenuBar>
#include <QMessageBox>
#include <QTimer>

#include "game.h"
#include "settings.h"

Game::Game(QWidget *parent)
    : QWidget(parent)
{

//QRect frect = frameGeometry();
//frect.moveCenter(QDesktopWidget().screenGeometry().center());
//move(frect.topLeft());

//    QRect gry = geometry();
//    gry.moveCenter(qApp->desktop()->availableGeometry().center());
//    setGeometry(gry);

 speedMonst = 160; // inizializzazione velocità mostri di default.
 lab = NULL;
 pl = NULL;
 finished = false;
 pause = false;

 QMenuBar *menu_bar = new QMenuBar; // Menù bar della finestra principale.
 QGridLayout * mainLayout = new QGridLayout; // layout della finestra su una grid.
 inf = new QStatusBar; // status bar del form

 mainLayout->setVerticalSpacing(0);
 mainLayout->setHorizontalSpacing(0);

 // disegno griglia di label.

for(int j=0; j < 15; j++)
     for(int i =0; i < 20; i++) {

        Maze_v[i][j] = new QLabel;

        Maze_v[i][j]->setFixedSize(40,40);

        mainLayout->addWidget(Maze_v[i][j], j, i);

     }

 // fine disegno griglia di label.

 inf->showMessage(tr("Benvenuto in Pengu!  -  File -> Play = Per eseguire una nuova partita.")); // clear message per cancellare.
 inf->setSizeGripEnabled(false); // viene disattivata la possibilità di modificarla cliccando il bordo.
 inf->adjustSize();

 // Menù bar configurazione.

 QMenu *menu_file = menu_bar->addMenu(tr("&File"));
 QAction *action_play = menu_file->addAction(tr("Play"));

 QMenu *menu_help = menu_bar->addMenu(tr("&?"));

 QAction *action_sett = menu_file->addAction(tr("Impostazioni"));

 QAction *action_exit = menu_file->addAction(tr("&Esci"));
 QAction *action_info = menu_help->addAction(tr("&Info"));

 QObject::connect(action_exit, SIGNAL(activated()),
                  this, SLOT(quit()));

 QObject::connect(action_play, SIGNAL(activated()),
                  this, SLOT(play()));

 QObject::connect(action_sett, SIGNAL(activated()),
                  this, SLOT(settingsClick()));

 menu_file->addSeparator();

 QObject::connect(action_info, SIGNAL(activated()),
                  this, SLOT(info_mess()));

 // Menù bar fine configurazione.

 QVBoxLayout *Layout = new QVBoxLayout(this); // indica il layout definitivo del form che include gli altri.
 Layout->addWidget(menu_bar);
 Layout->addLayout(mainLayout);
 Layout->addWidget(inf);

 this->setLayout(Layout); // viene impostato il layout predefinito per il form.
 // adatta la finestra secondo i widget, sia in altezza che in larghezza.
 setFixedHeight(sizeHint().height());
 setFixedWidth(sizeHint().width());

 timer = new QTimer;

 connect(timer, SIGNAL(timeout()),
         this, SLOT(tick()));

 ready = new QTimer;

 connect(ready, SIGNAL(timeout()),
         this, SLOT(message()));

 tScreen = new QTimer;

 connect(tScreen, SIGNAL(timeout()),
         this, SLOT(view()));


 // caricamento impostazioni da file esterno.

 settings dag;
 dag.setGame(this);

 dag.Ok();

 dag.deleteLater();

 // fine caricamento impostazioni da file.

 // servirebbe per la tastiera.
 this->setFocusPolicy(Qt::TabFocus);

}

Game::~Game() {}

void Game::play(){ // esegue il gioco.

    // allocamento oggetti principali.
    lab = new labirinto;
    pl = new umano;

    lab->setTheme(tema);

    finished = false;

    // richiesta inserimento numero mostri:
    InsertMos diag; diag.setPunt(this); diag.exec();

}

void Game::quit(){this->close();}

void Game::info_mess(){

info *diag = new info;
diag->show();
}

void Game::setMaze(int x, int y, QPixmap *image){ // imposta l'array di label per la visualizzazione sul form.
    Maze_v[x][y]->setPixmap(*image);
}

void Game::tick(){

    if(lab->return_numMosNow() != 0){ // finchè il puntatore del player non viene deallocato oppure finchè ci sono mostri.

        if (lab->manOn_mostro(pl) == true){timer->stop(); tScreen->stop(); end_k(); finished = true;} // controlla se il player è catturato da un mostro e conclude il gioco.

            if (finished == false) {

        lab->throw_ice();

        lab->iceOn_mostro();

        lab->muovi_mostri(lab);

        if (lab->manOn_mostro(pl) == true){timer->stop(); tScreen->stop(); end_k(); finished = true;} // controlla se il player è catturato da un mostro e conclude il gioco.

            }

        if (finished == false) lab->iceOn_mostro();

    } else {

        // ferma il timer.
        timer->stop();

        tScreen->stop();

        end();

    }


}

void Game::end(){ // fine gioco vincendo.

    QString text;
    QMessageBox dialog;

    QTextStream(&text) << "Hai vinto!\nIl tuo punteggio finale e' :\n\nMostri : " <<  n << " X 100 = " << (n * 100) << "\nVittoria : + 100 - Totale = " << (n * 100 + 100);

    dialog.setText(text);
    dialog.exec();

    deleteObj(); // si deallocano le risorse.
}

void Game::end_k(){ // fine gioco ucciso.

    int num;

    num = lab->return_numMosNow(); // n° di mostri presenti al momento in gioco.

    QString text;
    QMessageBox dialog;

    QTextStream(&text) << "Sei Stato ucciso!!! \nIl tuo punteggio finale e' :\n\nMostri : " <<  (n-num) << " X 100 = " << ((n-num) * 100) << "\nUccisione : - 50 - Totale = " << ((n-num) * 100 - 50);

    dialog.setText(text);
    dialog.exec();

    pl = NULL;

    deleteObj(); // si deallocano le risorse.
}

// funzione che preleva i tasti premuti dall'utente.
void Game::keyPressEvent ( QKeyEvent * event ){

    // this->keyPressEvent(event);

    char bt = ' '; // carattere che conterrà la direzione di spostamento del giocatore umano.

    switch (event->key()) {
    case Qt::Key_Left:

        bt = 'A';

        if (pause != true)
        pl->move(lab, bt);

        break;

    case Qt::Key_Right:

        bt = 'D';

        if (pause != true)
        pl->move(lab, bt);

        break;

    case Qt::Key_Down:

        bt = 'S';

        if (pause != true)
        pl->move(lab, bt);

        break;

    case Qt::Key_Up:

        bt = 'W';

        if (pause != true)
        pl->move(lab, bt);

        break;

    case Qt::Key_P: // tasto pausa.

        if (pause == false){ timer->stop(); pause = true; inf->showMessage("Pausa !");} else
        { inf->showMessage("Go !"); timer->start(); pause = false;}

        break;

    default:
            event->ignore();
            break;
    }

    // controllo che il personaggio non sia su un mostro dopo lo spostamento.
    if (lab->manOn_mostro(pl) == true){timer->stop(); tScreen->stop(); end_k(); finished = true;}

}

void Game::setMonst(int num){ // num è il numero di mostri da creare.

        n = num;

        lab->immetti_mostri(num);
        lab->visualizza_lab(pl, this);

        message();

        ready->start(1000); // fa partire il timer che visualizza un conto alla rovescia.

}

void Game::message(){

    inf->clearMessage();

    static int i = 0;

    i++;

    inf->showMessage("Tieniti pronto ! - Assicurati che la finestra sia selezionata.");

    QString path; // contiene il percorso delle immagini dei numeri.

    QPixmap *image = new QPixmap; // immagine numero.

    switch(i){

    case 1:

        path = ":/res/images/3.gif";

        break;

    case 2:

        path = ":/res/images/2.gif";

        break;


    case 3:

        path = ":/res/images/1.gif";

        break;

    case 4:

        path = ":/res/images/go.gif";

        ready->stop();

        i=0; // si reinizializza in modo che, se si fa ripartire la partita, il timer funziona ancora.

        inf->showMessage("Go ! - Premi P per la pausa.", 2000);

        timer->start(speedMonst); // velocità mostri default : 100 ms.

        tScreen->start(25); // 25 per far visualizzare go, poi nella funzione torna a 0.

        break;

    }

    image->load(path);

    Maze_v[10][7]->setPixmap(*image);

}

void Game::deleteObj(){ // dealloca le risorse.

   inf->showMessage("Fine - Per incominciare una nuova partita selezionare File -> Play");

   if (lab != NULL) { delete lab; lab = NULL;}
   if (pl != NULL) { delete pl; pl = NULL; }

}

void Game::settingsClick(){
settings dag;
dag.setGame(this);

dag.exec();
}

void Game::setSpeed(int vel){ // imposta la velocità dei mostri.
speedMonst = vel;
}

void Game::view() { // qui si ridisegna lo schermo.

tScreen->setInterval(0);

lab->visualizza_lab(pl, this);

}

void Game::setTheme(int t) {
    tema = t;
}
