#ifndef ABOUTFEN_H_INCLUDED
#define ABOUTFEN_H_INCLUDED

#include "main.h"
#define PRGM_A_PROPOS "JDInit est un programme impl�ment� en C++, \n   avec l'aide la biblioth�que Qt. \nJDInit est initialement pr�vu pour aider les ma�tres de jeu � g�rer\n   les combats dans les parties de jeu de r�le sur table, \n   t�che qu'il est difficile de ma�triser lorsque les joueurs sont press�s."
#define PRGM_DESC_LICENCE "JDInit est sous la licence copyleft.\nL'auteur se d�charge de toute responsabilit�\n   concernant l'utilisation de ce programme\n\n"


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
