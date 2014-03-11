/*
Pengu - file: settings.cpp - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#include "settings.h"

settings::settings()
{
    QDialogButtonBox *buttonBox;
    QLabel *label;

    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QComboBox *comboBox;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton;

    this->resize(509, 323);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(150, 280, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    label = new QLabel(this);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(130, 10, 251, 31));

    QFont font;
    font.setFamily(QString::fromUtf8("AlArabiya"));
    font.setPointSize(14);

    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    horizontalSlider = new QSlider(this);
    horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
    horizontalSlider->setGeometry(QRect(30, 250, 160, 17));
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalSlider->setTickPosition(QSlider::TicksBelow);
    horizontalSlider->setTickInterval(50);

    label_2 = new QLabel(this);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(20, 50, 131, 21));

    label_3 = new QLabel(this);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(30, 220, 111, 21));

    label_4 = new QLabel(this);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(290, 50, 201, 161));
    label_4->setFrameShape(QFrame::StyledPanel);
    label_4->setFrameShadow(QFrame::Sunken);
    label_4->setLineWidth(2);

    label_5 = new QLabel(this);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(30, 150, 71, 31));;

    comboBox = new QComboBox(this);
    comboBox->setObjectName(QString::fromUtf8("comboBox"));
    comboBox->setGeometry(QRect(20, 80, 171, 31));

    label_6 = new QLabel(this);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(10, 280, 62, 18));

    label_7 = new QLabel(this);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(180, 280, 71, 18));

    pushButton = new QPushButton(this);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(100, 150, 92, 28));

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(Ok()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(info()));

    QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(speed(int)));

    this->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
    //label->setText(QApplication::translate("Dialog", tr("Impostazioni di Gioco :"), 0, QApplication::UnicodeUTF8));
    label->setText(tr("Impostazioni di Gioco :"));
    label_2->setText(tr("Seleziona tema:"));
    label_3->setText(tr("Velocita' mostri :"));
    label_4->setText(QString());
    label_5->setText(tr("Labirinto :"));

    pushButton->setText(QApplication::translate("Dialog", "Info", 0, QApplication::UnicodeUTF8));

    comboBox->clear();
    comboBox->insertItems(0, QStringList()
                          << QApplication::translate("Dialog", "Default", 0, QApplication::UnicodeUTF8)
                          );

    comboBox->insertItems(1, QStringList()
                          << QApplication::translate("Dialog", "Disney", 0, QApplication::UnicodeUTF8)
                          );

    comboBox->insertItems(2, QStringList()
                          << QApplication::translate("Dialog", "Yogi Bear", 0, QApplication::UnicodeUTF8)
                          );

    comboBox->insertItems(3, QStringList()
                          << QApplication::translate("Dialog", "Flinstones", 0, QApplication::UnicodeUTF8)
                          );

    comboBox->insertItems(4, QStringList()
                          << QApplication::translate("Dialog", "Sylvester & Tweety", 0, QApplication::UnicodeUTF8)
                          );

    comboBox->insertItems(5, QStringList()
                          << QApplication::translate("Dialog", "Looney Tunes", 0, QApplication::UnicodeUTF8)
                          );


    QObject::connect(comboBox, SIGNAL(activated(int)), this, SLOT(themeP(int)));

    label_6->setText(tr("normale"));
    label_7->setText(tr("piu' veloce"));

    QPixmap preview;
    preview.load(":/res/themes/standard/preview.gif");

    label_4->setPixmap(preview);

    vel = 160; // per evitare che se l'utente non la muove assuma valori negativi.

    // caricamento impostazioni selezionate da file::

    //    std::fstream file;

    //    file.open(":/res/config.txt", std::ios::in);

    QFile file("./config.txt");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        file.copy(":/res/config.txt", "./config.txt");
        file.setPermissions(QFile::ReadOwner | QFile::WriteOwner);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
    }

    QTextStream in(&file);
    int themeC, speedC;

    in >> (themeC);
    in >> (speedC);

    comboBox->setCurrentIndex(themeC); // imposta il tema selezionato
    themeP(themeC); // e richiama la funzione per disegnare la preview.

    switch(speedC) { // imposta la slider con la velocità selezionata dall'utente.

    case 160 :
        horizontalSlider->setValue(0);
        break;

    case 110 :
        horizontalSlider->setValue(50);
        break;

    case 60:
        horizontalSlider->setValue(100);
        break;

    }

    file.close();

    // fine caricamento da file.

}

void settings::speed(int c){

    if (c < 40) vel = 160; // la velocità rimane 100.

    if (c > 40 && c < 80) vel = 110; // la velocità diventa 50.

    if (c > 80) vel = 60; // la velocità diventa 25.

}

void settings::setGame(Game * g){
punt = g;
}

void settings::Ok(){ // si applicano le impostazioni.

punt->setSpeed(vel);

punt->setTheme(theme);

save();

this->close();

}

void settings::themeP(int select) {

    QPixmap preview;

    switch (select) {

        case 0: preview.load(":/res/themes/standard/preview.gif");
            theme = 0;
        break;

        case 1: preview.load(":/res/themes/disney/preview.gif");
            theme = 1;
        break;

        case 2: preview.load(":/res/themes/yogi/preview.gif");
            theme = 2;
        break;

        case 3: preview.load(":/res/themes/flinstones/preview.gif");
            theme = 3;
        break;

        case 4: preview.load(":/res/themes/titti/preview.gif");
             theme = 4;
        break;

        case 5: preview.load(":/res/themes/tunes/preview.gif");
             theme = 5;
        break;

    }

    label_4->setPixmap(preview);

}

void settings::info() {
    QMessageBox info;

    info.setText(tr("Per inserire il proprio labirinto personalizzato \ncreare il path /mazes/maze.txt nella cartella dell'eseguibile.\nEditare il file con la seguente convenzione : \n\n'*' - Per i ghiaccioli \n'-' - Per gli spazi bianchi \n'/' - per terminare la riga. \n\nIl numero di caratteri dovra' essere 20 x 15."));
    info.exec();
}

void settings::save() {

//    std::fstream file;

//    file.open("./config.txt", std::ios::out);

    QFile file("./config.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {

        qDebug()<< "Error opening the config file!";
    }

    QTextStream out(&file);

    out << theme;

    out << "\n";

    out << vel;

    file.close();
}
