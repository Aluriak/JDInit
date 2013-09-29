#ifndef FENENTITE_H_INCLUDED
#define FENENTITE_H_INCLUDED

#include "main.h"


// cette fenetre s'affiche ind�pendamment de la fenetre principale. Lorsqu'elle est ferm�e,
//      elle re�oit le vocabulaire, l'indication si il s'agit d'une modification ou d'une cr�ation d'entit�, et un pointeur vers son parent
//      elle renvoit � la fenetre principale tout le n�cessaire pour modifier ou cr�er une entit�.
class fenEntite : public QDialog {
    Q_OBJECT // macro permettant d'impl�menter des slots personalis�s

    public:
    // Constructeur
        fenEntite(QString vocab_parent[], bool *tabStat, bool creation, QWidget *parent = NULL); // bol�en vrai si l'objectif est de cr�er une entit�

    public slots:
        void configTerminee(); // appel�e par le bouton Appliquer, elle �met le signal contenant tout le n�c�ssaire

    signals:
        void creationTerminee(QString, QString, int, QString, bool*);
        void modifTerminee(QString, QString, int, QString, bool*);

    private:
    // Attributs
        QLineEdit *Nom; // champs pour le nom
        QLineEdit *Fig; // champs pour la figurine
        QDoubleSpinBox *Prio; // champs pour la priorit�
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




