/*
Pengu - file: info.h - Compiler: QT Creator - QT 4.8.5.
Exam project - "Programmazione ad oggetti in c++", degree course in software engineering.
Fabrizio Signoretti, fasigno37@gmai.com

Under GPLv3.
*/

#ifndef INFO_H
#define INFO_H

#include <QDialog>

class info : public QDialog
{
Q_OBJECT
public:
    info();

public slots:
    void quit();
};

#endif // INFO_H
