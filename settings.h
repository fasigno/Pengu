/*
Pengu - file: settings.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QtGui>

#include "game.h"

class Game;

class settings : public QDialog
{
Q_OBJECT

    QSlider *horizontalSlider;
    QLabel *label_4;
    Game *punt;

    int vel; // variabile temporanea che tiene il tempo di velocità mostri.
    int theme; // variabile che indica il tema selezionato dall'utente.

public:
    settings();
    void setGame(Game *); // imposta il puntatore a Game.

    void save(); // salva le impostazioni su file.

public slots:

    void speed(int); // cambia la velocità dei mostri.
    void Ok(); // click su ok;
    void info();

    void themeP(int); // quando si clicca sul comboBox appare la preview sulla label del tema.

};

#endif // SETTINGS_H
