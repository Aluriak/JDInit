#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "main.h"


class fenetre : public QWidget {
    Q_OBJECT // macro permettant d'implémenter des slots personalisés

    public:
    // Constructeur
        fenetre();

    public slots:
        void passageTourSuivant();                          // Gère les conséquences du passage de tour dans la table d'entités
        void definirJoueur();                               // Modifie le pointeur vers le joueur pour qu'il pointe l'entité sélectionnée par w_Selection
        void selectionEntite(QTableWidgetItem*);            // modifie le pointeur de sélection d'entité selon l'item pointé
        void affFenetreCreerEntite();                       // Affiche la fenetre d'ajout d'entité
        void affFenetreModifEntite();                       // Affiche la fenetre de modification d'entité
        void affFenetreOptions();                           // Affiche la fenetre de modification des options
        void ajoutEntite(QString, QString, int, QString, bool*);   // Créé l'entité selon arg() et la place dans la table
        void modifEntite(QString, QString, int, QString, bool*);   // Modifie l'entité sélectionnée selon arg()
        void ajoutGroupeEntite();                           // Ajoute le groupe d'entité décrites dans le fichier FILE_GROUPE
        void supressionEntite();                            // Supression de l'entité sélectionnée
        void OuvertureAPropos();                            // Affiche la boite de dialogue causant du programme
        void reinitialisationPrgm();                        // Vide la table d'entité
        void recevoirConfig(bool*);                         // Reçois la config de la table d'option
        void FinPRGM();                                     // Appelé par le bouton Quit, il gère la mémoire en fin de programme

    private:
    // ATTRIBUTS
    // la table qui contient la liste des entités
        QTableWidget *w_Table;
        std::vector <entite*> liste_Entite;                 // Contient la liste des entités
        entite* w_Joueur;                                   // pointeur vers l'entité dont c'est le tour
        QTableWidgetItem* w_Selection;                      // pointeur vers l'item sélectionné par l'utilisateur
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
    // vocabulaire (déterminé par le vocabulateur)
        QString vocab[VOCABULATEUR_NB_MOT];
    // Options
        bool w_BoolOption[OPT_NB_OPTIONS]; // boléens indiquant les affichages à faire

// METHODES
    // Méthodes de construction
        void constructionBoutons();                 // construit les boutons lors de la création de la fenetre
        void initialisationOptions();               // initialise les boléen d'options en fonction du contenu du fichier FILE_OPTIONS
        void initialisationColonne();               // initialise le vector de colonne en fonction des boléen
    // Méthodes de la fenetre
        void affichageTable();                      // lis la liste d'entité, et les affiche rangées dans la table
        void supprimerElementListeEntite(int);      // supprime l'élément d'ID envoyé en argument dans la liste d'entité, ainsi que la case elle-même
        void correctionVocabulaire();               // remplacement du vocabulaire vide par les noms génériques
        void validiteBouton(bool);                  // Gère la validité de certains boutons suivant le boléen
    // Méthodes du trieur
        void initialisation_Table();                // Initialise la table
        void colorerTable();                        // recolore toutes les lignes de la table suivant le camp de l'entité étudiée
            QColor choixCouleurEntite(QString);     // renvoit la couleur correspondant au camp envoyé en argument
        void triageListeEntite();                   // trie la liste d'entité de la plus à la moins prioritaire
        void remplissageTable();                    // ajoute à la table toutes les entités dans la liste, dans leur ordre d'apparition
    // Méthodes relatives aux entités
        std::string getStatut(entite *ent);         // renvois une chaine contenant les noms des statut exprimé chez l'entité en arg()
};





#endif // FENETRE_H_INCLUDED
