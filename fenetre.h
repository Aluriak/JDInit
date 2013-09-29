#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "main.h"


class fenetre : public QWidget {
    Q_OBJECT // macro permettant d'impl�menter des slots personalis�s

    public:
    // Constructeur
        fenetre();

    public slots:
        void passageTourSuivant();                          // G�re les cons�quences du passage de tour dans la table d'entit�s
        void definirJoueur();                               // Modifie le pointeur vers le joueur pour qu'il pointe l'entit� s�lectionn�e par w_Selection
        void selectionEntite(QTableWidgetItem*);            // modifie le pointeur de s�lection d'entit� selon l'item point�
        void affFenetreCreerEntite();                       // Affiche la fenetre d'ajout d'entit�
        void affFenetreModifEntite();                       // Affiche la fenetre de modification d'entit�
        void affFenetreOptions();                           // Affiche la fenetre de modification des options
        void ajoutEntite(QString, QString, int, QString, bool*);   // Cr�� l'entit� selon arg() et la place dans la table
        void modifEntite(QString, QString, int, QString, bool*);   // Modifie l'entit� s�lectionn�e selon arg()
        void ajoutGroupeEntite();                           // Ajoute le groupe d'entit� d�crites dans le fichier FILE_GROUPE
        void supressionEntite();                            // Supression de l'entit� s�lectionn�e
        void OuvertureAPropos();                            // Affiche la boite de dialogue causant du programme
        void reinitialisationPrgm();                        // Vide la table d'entit�
        void recevoirConfig(bool*);                         // Re�ois la config de la table d'option
        void FinPRGM();                                     // Appel� par le bouton Quit, il g�re la m�moire en fin de programme

    private:
    // ATTRIBUTS
    // la table qui contient la liste des entit�s
        QTableWidget *w_Table;
        std::vector <entite*> liste_Entite;                 // Contient la liste des entit�s
        entite* w_Joueur;                                   // pointeur vers l'entit� dont c'est le tour
        QTableWidgetItem* w_Selection;                      // pointeur vers l'item s�lectionn� par l'utilisateur
        std::vector<std::string> w_Colonnes;                // Liste des colonnes composants la table
    // boutons
        QPushButton *w_Quit;
        QPushButton *w_APropos;
        QPushButton *w_Options;
        QPushButton *w_Reset;
        QPushButton *w_PassageTour;
        QPushButton *w_DefJoueur;
        QPushButton *w_NouvEntite;
        QPushButton *w_ChargerGroupe;
        QPushButton *w_EditEntite;
        QPushButton *w_SuprEntite;
    // vocabulaire (d�termin� par le vocabulateur)
        QString vocab[VOCABULATEUR_NB_MOT];
    // Options
        bool w_BoolOption[OPT_NB_OPTIONS]; // bol�ens indiquant les affichages � faire

// METHODES
    // M�thodes de construction
        void constructionBoutons();                 // construit les boutons lors de la cr�ation de la fenetre
        void initialisationOptions();               // initialise les bol�en d'options en fonction du contenu du fichier FILE_OPTIONS
        void initialisationColonne();               // initialise le vector de colonne en fonction des bol�en
    // M�thodes de la fenetre
        void affichageTable();                      // lis la liste d'entit�, et les affiche rang�es dans la table
        void supprimerElementListeEntite(int);      // supprime l'�l�ment d'ID envoy� en argument dans la liste d'entit�, ainsi que la case elle-m�me
        void correctionVocabulaire();               // remplacement du vocabulaire vide par les noms g�n�riques
        void validiteBouton(bool);                  // G�re la validit� de certains boutons suivant le bol�en
    // M�thodes du trieur
        void initialisation_Table();                // Initialise la table
        void colorerTable();                        // recolore toutes les lignes de la table suivant le camp de l'entit� �tudi�e
            QColor choixCouleurEntite(QString);     // renvoit la couleur correspondant au camp envoy� en argument
        void triageListeEntite();                   // trie la liste d'entit� de la plus � la moins prioritaire
        void remplissageTable();                    // ajoute � la table toutes les entit�s dans la liste, dans leur ordre d'apparition
    // M�thodes relatives aux entit�s
        std::string getStatut(entite *ent);         // renvois une chaine contenant les noms des statut exprim� chez l'entit� en arg()
};





#endif // FENETRE_H_INCLUDED
