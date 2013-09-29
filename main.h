#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

// =============================
//      BIBLIOTHEQUES
// =============================
// C++
    #include <iostream>
    #include <fstream>
    #include <string>
    #include <vector>
    #include <sstream>
// Qt
    #include <QApplication>
    #include <QObject>
    #include <QWidget>
    #include <QDialog>
    #include <QTableWidget>
    #include <QPushButton>
    #include <QHBoxLayout>
    #include <QVBoxLayout>
    #include <QComboBox>
    #include <QDoubleSpinBox>
    #include <QLineEdit>
    #include <QLabel>
    #include <QGroupBox>
    #include <QCheckBox>
    #include <QPixmap>
    #include <QSplashScreen>



// =============================
//      DEFINES
// =============================
// Fenêtrage
    #define PRGM_NOM "JDInit BETA"
    //#define PRGM_SPLASH_SCREEN "Img/SplashScreen.png"
    #define PRGM_NOM_FEN_ENTITE_CREAT "Création " // le mot qui suit est déterminé par le vocabulaire
    #define PRGM_NOM_FEN_ENTITE_MODIF "Modification "
    #define PRGM_LARGEUR_FENETRE 800
    #define PRGM_HAUTEUR_FENETRE 400
    #define PRGM_LARGEUR_FENETRE_ENTITE 300
    #define PRGM_HAUTEUR_FENETRE_ENTITE 300
    #define PRGM_LARGEUR_FENETRE_APROPOS 400
    #define PRGM_HAUTEUR_FENETRE_APROPOS 300
    #define PRGM_LARGEUR_FENETRE_OPTIONS 350
    #define PRGM_HAUTEUR_FENETRE_OPTIONS 200
// Table d'entités
    #define PRGM_NB_COLONNE_BASE 2
    #define LARGEUR_COLONNE_NOM 160
    #define LARGEUR_COLONNE_FIG 120
    #define LARGEUR_COLONNE_STA 145
    #define LARGEUR_COLONNE_INI 90
    #define LARGEUR_COLONNE_CAM 90
    #define PRGM_BRUSH_ENTITE_JOUEUR Qt::Dense4Pattern
// Vocabulateur
    #define VOCABULATEUR_NB_MOT 22 // nombre de mot de vocabulaire à traiter
    #define VOCABULATEUR_NB_STATUT 12
    #define VOC_ENTITE 0
    #define VOC_NOM 1
    #define VOC_FIGURINE 2
    #define VOC_PRIORITE 3
    #define VOC_CAMP 4
    #define VOC_PJ 5
    #define VOC_ALLIE 6
    #define VOC_ENNEMI 7
    #define VOC_AUTRE 8
    #define VOC_STATUT 9
    #define VOC_STATUT0 10
    #define VOC_STATUT1 11
    #define VOC_STATUT2 12
    #define VOC_STATUT3 13
    #define VOC_STATUT4 14
    #define VOC_STATUT5 15
    #define VOC_STATUT6 16
    #define VOC_STATUT7 17
    #define VOC_STATUT8 18
    #define VOC_STATUT9 19
    #define VOC_STATUT10 20
    #define VOC_STATUT11 21
// Gestion d'options
    #define OPT_NB_OPTIONS 3
    #define OPT_AFF_FIG 0
    #define OPT_AFF_STATUT 1
    #define OPT_AFF_CAMP 2
// Fichiers
    #define FILE_VOCAB "File/Vocabulaire"
    #define FILE_ERR "File/Erreur"
    #define FILE_OPTIONS "File/Config"
    #define FILE_GROUPE "File/Groupe"

// =============================
//      HEADERS
// =============================
#include "fenOptions.h"
#include "entite.h"
#include "vocabulateur.h"
#include "fenetre.h"
#include "fenEntite.h"
#include "AboutFen.h"



// =============================
//      PROTOTYPES
// =============================
// Fonctions annexes (main.cpp)
    QString str2Qstr(std::string str);  // renvois la chaîne sous forme de QString
    int str2num(std::string str);       // renvois le nombre écrit en format ascii-chaîne, ou 0 si c'est pas un nombre
    int pow(int a, int b);              // renvois a^b
    std::string num2str(int nb);        // renvois sous forme de string le nombre envoyé en argument
    std::string qstr2Str(QString str);  // renvois la QString sous forme de string
    void CopieContenuVector(std::vector<entite*> &src, std::vector<entite*> &dest); // copie dans dest les valeur de src
    void FLUX_ERREUR(std::string source, std::string erreur); // inscrit dans le fichier d'erreur les erreurs reçues en argument

#endif // MAIN_H_INCLUDED
