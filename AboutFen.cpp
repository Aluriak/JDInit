#include "main.h"

using namespace std;




// ==============================================
//              CONSTRUCTEUR
// ==============================================
AboutFen::AboutFen(QWidget *parent = 0) : QDialog(parent)
{
    setGeometry(0,0,PRGM_LARGEUR_FENETRE_APROPOS, PRGM_HAUTEUR_FENETRE_APROPOS);
    setWindowTitle("A propos de JDInit");

    // label de présentation du programme
    // création des string
    string str("JDInit est un programme implémenté en C++ par Lucas Bourneuf, \n   avec l'aide de la bibliothèque Qt.\n");
    str += "JDInit est initialement prévu pour aider les maîtres de jeu à gérer\n";
    str += "   les combats dans les parties de jeu de rôle sur table, \n   notamment lors de la délicate détermination de l'initiative.";
    string str2("JDInit est sous la licence copyleft.\nN'hésitez pas à prendre contact par mail pour communiquer\n");
    str2 += "   vos retours et idées.\nL'auteur se décharge de toute responsabilités\n";
    str2 += "   concernant l'utilisation de ce programme.\n\n";

    e_AboutPrgm = new QLabel(str2Qstr(str), this);
    e_Licence = new QLabel(str2Qstr(str2), this);
    e_Contact = new QLabel("\nContact : reselsif@gmx.com", this);


    // boutons
    e_AboutQt = new QPushButton("A propos de Qt", this);
    e_RetourPrgm = new QPushButton("Retour", this);


    // PLACEMENT DES WIDGETS
    QVBoxLayout *LayTextes = new QVBoxLayout; // layout contenant les textes
        LayTextes->addWidget(e_AboutPrgm);
        LayTextes->addWidget(e_Licence);
        LayTextes->addWidget(e_Contact);
        QGroupBox *groupeTextes = new QGroupBox(this);
            groupeTextes->setLayout(LayTextes);

    QHBoxLayout *LayBouton = new QHBoxLayout;
        LayBouton->addWidget(e_AboutQt);
        LayBouton->addWidget(e_RetourPrgm);
        QGroupBox *groupeBouton = new QGroupBox(this);
            groupeBouton->setLayout(LayBouton);

    // Gestion de LayPrinc
    QVBoxLayout *LayPrinc = new QVBoxLayout(this); // layout principal
        LayPrinc->addWidget(groupeTextes);
        LayPrinc->addWidget(groupeBouton);

    // connections
    QObject::connect(e_AboutQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    QObject::connect(e_RetourPrgm, SIGNAL(clicked()), this, SLOT(accept()));
}


