#ifndef ABOUTFEN_H_INCLUDED
#define ABOUTFEN_H_INCLUDED

#include "main.h"
#define PRGM_A_PROPOS "JDInit est un programme implémenté en C++, \n   avec l'aide la bibliothèque Qt. \nJDInit est initialement prévu pour aider les maîtres de jeu à gérer\n   les combats dans les parties de jeu de rôle sur table, \n   tâche qu'il est difficile de maîtriser lorsque les joueurs sont pressés."
#define PRGM_DESC_LICENCE "JDInit est sous la licence copyleft.\nL'auteur se décharge de toute responsabilité\n   concernant l'utilisation de ce programme\n\n"


class AboutFen : public QDialog
{
    public:
        AboutFen(QWidget *parent);

    private:
        QLabel *e_AboutPrgm;
        QLabel *e_Licence;
        QLabel *e_Contact;

        QPushButton *e_AboutQt;
        QPushButton *e_RetourPrgm;

};


#endif // ABOUTFEN_H_INCLUDED
