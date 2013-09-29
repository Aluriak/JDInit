#ifndef FENENTITE_H_INCLUDED
#define FENENTITE_H_INCLUDED

#include "main.h"


// cette fenetre s'affiche indépendamment de la fenetre principale. Lorsqu'elle est fermée,
//      elle reçoit le vocabulaire, l'indication si il s'agit d'une modification ou d'une création d'entité, et un pointeur vers son parent
//      elle renvoit à la fenetre principale tout le nécessaire pour modifier ou créer une entité.
class fenEntite : public QDialog {
    Q_OBJECT // macro permettant d'implémenter des slots personalisés

    public:
    // Constructeur
        fenEntite(QString vocab_parent[], bool *tabStat, bool creation, QWidget *parent = NULL); // boléen vrai si l'objectif est de créer une entité

    public slots:
        void configTerminee(); // appelée par le bouton Appliquer, elle émet le signal contenant tout le nécéssaire

    signals:
        void creationTerminee(QString, QString, int, QString, bool*);
        void modifTerminee(QString, QString, int, QString, bool*);

    private:
    // Attributs
        QLineEdit *Nom; // champs pour le nom
        QLineEdit *Fig; // champs pour la figurine
        QDoubleSpinBox *Prio; // champs pour la priorité
        QComboBox *Camps; // champs pour le camps
        QCheckBox *Status[VOCABULATEUR_NB_STATUT]; // champs pour les status
        bool e_Creation;
        // boutons
        QPushButton *Annuler;
        QPushButton *Appliquer;
        // vocabulaire
        QString vocab[VOCABULATEUR_NB_MOT];
};

#endif // FENENTITE_H_INCLUDED




