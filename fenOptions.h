#ifndef FENOPTIONS_H_INCLUDED
#define FENOPTIONS_H_INCLUDED

#include "main.h"


// configure et enregistre la configuration dans FILE_OPTIONS
class fenOptions : public QDialog {
    Q_OBJECT

    public:
    // Constructeur
        fenOptions(QString vocab_parent[], QWidget *parent = NULL);


    public slots:
        void enregistrerConfiguration();        // appelé lorsque le bouton d'enregistrement est cliqué. Ferme la fenêtre et envois le signal de modifs des paramètres de la fenetre


    signals:
    // envois de tous les paramètres attendus par la fenetre mère.
        void envoisParametreParent(bool*);

    private:
    // Attributs
        QCheckBox *e_affFig; // si checké, on affiche les figurines
        QCheckBox *e_affStatut; // si checké, on affiche les statuts
        QCheckBox *e_affCamp; // si checké, on affiche les camps
        QPushButton *e_Quit; // quitter sans rien changer
        QPushButton *e_Save; // quitter et changeant les configs
        // vocabulaire
        QString vocab[VOCABULATEUR_NB_MOT];
        // tableaux des configs
        bool e_opt[OPT_NB_OPTIONS];

    // Méthodes
        void actualisationFichier();            // inscrit dans le fichier FILE_OPTIONS les valeurs de configuration
        void emettreSignal();                   // émet de le signal selon les attributs de la fenetre
        void initialisationQCheckBox();         // gère les QCheckBox en lisant dans le fichier FILE_OPTIONS
        void initialisationTabOpt();            // lit FILE_OPTIONS et en déduit l'intialisation du tableau e_opt
};



#endif // FENOPTIONS_H_INCLUDED
