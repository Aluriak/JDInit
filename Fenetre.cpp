#include "main.h"

using namespace std;




// ==============================================
//              CONSTRUCTEUR
// ==============================================
fenetre::fenetre() {
    setWindowTitle(PRGM_NOM); // titre de la fenetre
    setGeometry(0,0,PRGM_LARGEUR_FENETRE, PRGM_HAUTEUR_FENETRE); // dimension de la fenetre.

    // initialisation du vocabulaire
    vocabulateur vocabulaire;
        for(int i = 0; i < VOCABULATEUR_NB_MOT; i++)
            vocab[i] = str2Qstr(vocabulaire.getVocab(i));
    // on v�rifie maintenant ce qu'on obtient : le vocabulateur renvoie des cha�nes vides s'il ne lit rien !
    //      Dans ce cas, on remplace par le nom g�n�rique
    correctionVocabulaire();

    // TABLE
    initialisationOptions(); // lecture des options
    initialisationColonne(); // calcul du nombre de colonne en fonction des options

    w_Table = new QTableWidget(0, w_Colonnes.size(), this); // 0 lignes et 3 colonnes
        w_Table->setSelectionBehavior(QAbstractItemView::SelectRows); // l'utilisateur ne peut s�lectionner que les lignes
        // mettre la table dans un conteneur
        QVBoxLayout *LayTable = new QVBoxLayout;
            LayTable->addWidget(w_Table);
        QGroupBox *groupeTable = new QGroupBox("Table des " + vocab[VOC_ENTITE] + "s", this);
            groupeTable->setLayout(LayTable);

    initialisation_Table(); // initialisation de la table selon le fichier FILE_OPTIONS

    // liste d'entit�s
    w_Joueur = NULL; // entit� qui commence : aucune pour le moment
    w_Selection = NULL; // Aucune ligne n'est s�lectionn�e au tout d�but
    affichageTable();

    // QPUSHBUTTONS
    constructionBoutons();

    // LAYOUTS
    QHBoxLayout *LayFen = new QHBoxLayout(this); // layout principal de fen�tre

    QVBoxLayout *LayButtonDroit = new QVBoxLayout; // Layout contenant les layouts contenant les boutons � droite
        QVBoxLayout *LayButtonDroitEntite = new QVBoxLayout; // Layout contenant les boutons � droite relatifs � l'entit�
            LayButtonDroitEntite->addWidget(w_NouvEntite);
            LayButtonDroitEntite->addWidget(w_ChargerGroupe);
            LayButtonDroitEntite->addWidget(w_EditEntite);
            LayButtonDroitEntite->addWidget(w_SuprEntite);
        QVBoxLayout *LayButtonDroitTour = new QVBoxLayout; // Layout contenant les boutons � droite relatifs aux tours de jeu
            LayButtonDroitTour->addWidget(w_DefJoueur);
            LayButtonDroitTour->addWidget(w_PassageTour);
        // introductions des layouts
        LayButtonDroit->addLayout(LayButtonDroitEntite);
        LayButtonDroit->addLayout(LayButtonDroitTour);
            QGroupBox *groupeBoutonDroit = new QGroupBox("Gestion des " + vocab[VOC_ENTITE] + "s", this);
                groupeBoutonDroit->setLayout(LayButtonDroit);

    QHBoxLayout *LayButtonPrgm = new QHBoxLayout; // Layout contenant les boutons relatifs au programme
        LayButtonPrgm->addWidget(w_Quit);
        LayButtonPrgm->addWidget(w_APropos);
        LayButtonPrgm->addWidget(w_Options);
        LayButtonPrgm->addWidget(w_Reset);
        QGroupBox *groupeBoutonPrgm = new QGroupBox("Programme", this);
            groupeBoutonPrgm->setLayout(LayButtonPrgm);

    QVBoxLayout *LayPartieGauche = new QVBoxLayout; // Layout contenant la table et les boutons de droite
        LayPartieGauche->addWidget(groupeTable);
        LayPartieGauche->addWidget(groupeBoutonPrgm);

    // Remplissage du layout principal
    LayFen->addLayout(LayPartieGauche);
    LayFen->addWidget(groupeBoutonDroit);



    // CONNEXIONS
    // boutons PRGM
    QObject::connect(w_Quit, SIGNAL(clicked()), this, SLOT(FinPRGM())); // quitter avec gestion m�moire li�e
    QObject::connect(w_APropos, SIGNAL(clicked()), this, SLOT(OuvertureAPropos())); // d�clencher l'ouverture d'une boite de dialogue � propos du programme
    QObject::connect(w_Reset, SIGNAL(clicked()), this, SLOT(reinitialisationPrgm())); // d�clencher la vidange de la table
    QObject::connect(w_Options, SIGNAL(clicked()), this, SLOT(affFenetreOptions())); // d�clencher l'ouverture de la fenetre d'options
    // boutons volet droit
    QObject::connect(w_NouvEntite, SIGNAL(clicked()), this, SLOT(affFenetreCreerEntite())); // affichage de la fenetre de cr�ation
    QObject::connect(w_ChargerGroupe, SIGNAL(clicked()), this, SLOT(ajoutGroupeEntite())); // chargement des entit�s de groupe
    QObject::connect(w_EditEntite, SIGNAL(clicked()), this, SLOT(affFenetreModifEntite())); // affichage de la fenetre d'�dition
    QObject::connect(w_SuprEntite, SIGNAL(clicked()), this, SLOT(supressionEntite())); // amor�age de la suppression d'entit� s�lectionn�e
    QObject::connect(w_PassageTour, SIGNAL(clicked()), this, SLOT(passageTourSuivant())); // amor�age de la suppression d'entit� s�lectionn�e
    QObject::connect(w_DefJoueur, SIGNAL(clicked()), this, SLOT(definirJoueur())); // amor�age de la suppression d'entit� s�lectionn�e
    // lorsque l'on clique sur un item de la table, on le s�lectionne
    QObject::connect(w_Table, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(selectionEntite(QTableWidgetItem*)));
}


// construit les boutons lors de la cr�ation de la fenetre
void fenetre::constructionBoutons() {
    w_Quit = new QPushButton("Quitter", this);
        w_Quit->setToolTip("Ferme JDInit");
    w_APropos = new QPushButton("A Propos", this);
        w_APropos->setToolTip("Ouvre une fen�tre d'information sur JDInit");
    w_Options = new QPushButton("Options", this);
        w_Options->setToolTip("Ouvre une fen�tre de configuration de JDInit");
    w_Reset = new QPushButton("R�initialiser", this);
        w_Reset->setToolTip("Supprime l'ensemble des " + vocab[VOC_ENTITE] + " de la table");
    w_PassageTour = new QPushButton("Joueur suivant", this);
        w_PassageTour->setToolTip("Fait �voluer le marqueur dans la table jusqu'au prochain joueur");
    w_DefJoueur = new QPushButton("D�finir comme joueur", this);
        w_DefJoueur->setToolTip("D�finition de " + vocab[VOC_ENTITE] + " comme joueur");
    w_NouvEntite = new QPushButton("Ajouter " + vocab[VOC_ENTITE] + "s", this);
        w_NouvEntite->setToolTip("Ouvre la fenetre d'ajout de " + vocab[VOC_ENTITE]);
    w_ChargerGroupe = new QPushButton("Ajouter groupe", this);
        w_ChargerGroupe->setToolTip("Ajoute dans la table les " + vocab[VOC_ENTITE] + "s contenu dans le fichier Groupe.Alk");
    w_EditEntite = new QPushButton("Editer", this);
        w_EditEntite->setToolTip("Ouvre la fenetre de modification de " + vocab[VOC_ENTITE]);
    w_SuprEntite = new QPushButton("Supprimer", this);
        w_SuprEntite->setToolTip("Suppression de " + vocab[VOC_ENTITE]);

    // Parce qu'aucune ligne n'est s�lectionn�e au d�but
    w_EditEntite->setEnabled(false);
    w_SuprEntite->setEnabled(false);
    w_DefJoueur->setEnabled(false);
    w_PassageTour->setEnabled(false); // et qu'il n'y a pas d'entit� pr�d�finie
}


// initialise les bol�en d'options en fonction du contenu du fichier FILE_OPTIONS
void fenetre::initialisationOptions() {
    string ligne = "";
    int compteur = 0;
    // lecture du fichier pour savoir lesquels sont activ�s/d�sactiv�s
    ifstream opt(FILE_OPTIONS);
    // gestion erreur d'ouverture
    if(!opt) {
        FLUX_ERREUR("GESTION D'OPTIONS", "Erreur d'ouverture du fichier File/Config.Alk en lecture.");
        return;
    }
    // lecture du fichier
    while(getline(opt, ligne)) {
        if(ligne.size() == 1) {
            // on met une valeur �gale � 0 ou 1 (avec le d�calage en ASCII)
            if((ligne[0] - 48) == 0)
                w_BoolOption[compteur] = false;
            else
                w_BoolOption[compteur] = true;
        }
        else { // arriv�s l�, c'est que la ligne �tait plus longue que pr�vus. Le fichiers a �t� �dit� ou �cras� par autre chose que le programme.
            FLUX_ERREUR("GESTION D'OPTIONS", "Fichier File/Config.Alk Corrompu.");
            w_BoolOption[compteur] = false;
        }
        compteur++;
    }
    opt.close(); // fermeture du fichier
}

// initialise le vector de colonne en fonction des bol�en
void fenetre::initialisationColonne() {
    w_Colonnes.push_back(qstr2Str(vocab[VOC_NOM]));             // cr�ation de la colonne pour le nom, obligatoire
    if(w_BoolOption[OPT_AFF_FIG])                               // si c'est demand�, on met la colonne figurine
        w_Colonnes.push_back(qstr2Str(vocab[VOC_FIGURINE]));
    w_Colonnes.push_back(qstr2Str(vocab[VOC_PRIORITE]));         // on met la colonne de priorit�
    if(w_BoolOption[OPT_AFF_STATUT])                            // si c'est demand�, on met la colonne statut
        w_Colonnes.push_back(qstr2Str(vocab[VOC_STATUT]));
    if(w_BoolOption[OPT_AFF_CAMP])                              // si c'est demand�, on met la colonne camp
        w_Colonnes.push_back(qstr2Str(vocab[VOC_CAMP]));
}





// =============================
//      SLOTS
// =============================
// cr�� l'entit� selon arg() et la place dans la table
void fenetre::ajoutEntite(QString nom, QString fig, int prio, QString camps, bool* opt) {
    // cr�ation d'une nouvelle entit�
    liste_Entite.push_back(new entite(qstr2Str(nom), qstr2Str(fig), prio, qstr2Str(camps), opt));
    // test pour savoir si cette entit� est la premi�re, et donc l'entit� � qui c'est le tour
    if(liste_Entite.size() == 1) w_Joueur = liste_Entite[0];
    // le bouton pour passer au tour suivant peut �tre actif
    if(liste_Entite.size() > 1) w_PassageTour->setEnabled(true);
    // puis affichage de la table
    affichageTable();
}


// modifie l'entit� s�lectionn�e selon arg()
void fenetre::modifEntite(QString nom, QString fig, int prio, QString camps, bool* opt) {
    // protection contre la non s�lection
    if(w_Selection == NULL) return;
    // localisation de l'entit� s�lectionn�e
    int ligne = w_Selection->row();
    // protection contre la non s�lection : si la ligne s�lectionn�e est la premi�re, ou n'est pas dans la table
    if(ligne <= 0)     return;
    entite *etude = liste_Entite[ligne-1];
    // modification des attributs, si quelque chose est chang�
    if(nom != "Inchang�")   etude->SetNom(qstr2Str(nom));
    if(fig != "Inchang�")   etude->SetFigurine(qstr2Str(fig));
    if(prio != -1)          etude->SetPriorite(prio);
    if(camps != "Inchang�") etude->SetCamps(qstr2Str(camps));
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        etude->SetStatut(i,opt[i]); // modif de la valeur de statut
    // puis affichage de la table
    affichageTable();
}

// Ajoute le groupe d'entit� d�crites dans le fichier FILE_GROUPE
void fenetre::ajoutGroupeEntite() {
    ifstream grp(FILE_GROUPE);
    // gestion erreur
    if(!grp) {
        FLUX_ERREUR("AJOUT DU GROUPE", "Erreur d'ouverture du fichier File/Groupe.Alk en lecture.");
        return;
    }
    int compteur = 0;
    string ligne(""), mot(""), nom(""), fig("");

    // lecture totale du fichier
    while(getline(grp, ligne)) {
        // parcours de la ligne
        for(unsigned int i = 0; i < ligne.size(); i++) {
            if(ligne[i] == ':') {
                // si on est au premier champ (compteur � 0)
                if(compteur == 0)
                    nom = mot; // attribution de l'expression lue au nom
                else
                    fig = mot; // attribution de l'expression lue � la figurine
                mot = "";   // on vide l'expression en cours
                compteur++;
            }
            else
                mot += ligne[i]; // on ajoute le caract�re lu.
        }
        // la ligne est parcourue : il ne reste plus qu'� cr�er l'entit� correspondante.
        bool opt[VOCABULATEUR_NB_STATUT]; // cr�ation et initialisation du tableau
        for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++) opt[i] = 0;
        liste_Entite.push_back(new entite(nom, fig, 0, qstr2Str(vocab[VOC_PJ]), opt));
        // les variables sont remises � z�ro. sinon c'est le dawa.
        compteur = 0;
        fig = nom = mot = "";
    }
    // enfin, affichage de la table
    affichageTable();
}


// Supression de l'entit� s�lectionn�e
void fenetre::supressionEntite() {
    // protection contre la non s�lection
    if(w_Selection == NULL) return;
    int ligne = w_Selection->row();
    // protection contre la non s�lection : si la ligne s�lectionn�e est la premi�re, ou n'est pas dans la table
    if(ligne <= 0)     return;
    bool pasBouger = false; // vrai si la ligne supprim�e est celle de l'entit� joueuse

    // si l'entit� qu'on supprime est celle � qui c'�tait le tour
    if(w_Joueur == liste_Entite[ligne-1]) {
        // ET qu'il ne s'agit pas de la derni�re ligne
        if((unsigned int)ligne < liste_Entite.size())
            pasBouger = true;
        else if(liste_Entite.size() > 1) { // si il s'agit de la derni�re ligne et qu'il y a plus d'un �l�ment
            w_Joueur = liste_Entite[0]; // on pointe la premi�re entit�
            w_Selection = w_Table->item(w_Table->rowCount()-1,0); // la s�lection pointe le dernier �l�ment
            // protection contre la s�lection de la ligne de r�f�rence
            if(w_Selection->row() == 0)    validiteBouton(false); // les boutons sont invalid�s
        }
        else { // sinon, c'est qu'il n'y a plus d'entit�s
            w_Joueur = NULL;
            w_Selection = w_Table->item(0,0); // la s�lection pointe la premi�re ligne
            validiteBouton(false); // les boutons sont invalid�s
        }
    }

    // on supprime l'entit� correspondant � la ligne
    delete liste_Entite[ligne-1];
    supprimerElementListeEntite(ligne-1);

    // si le pointeur w_Joueur devait rester sur la m�me case
    if(pasBouger) {
        w_Joueur = liste_Entite[ligne-1]; // alors w_Joueur pointe vers l'�l�ment qui remplace l'entit� supprim�e
        w_Selection = w_Table->item(ligne,0); // et la s�lection pointe vers ce dernier
    }

    // le bouton pour passer au tour suivant peut �tre rendu inactif
    if(liste_Entite.size() <= 1) w_PassageTour->setEnabled(false);
    // puis affichage de la table
    affichageTable();
}



// Affiche la fenetre d'ajout d'entit�
void fenetre::affFenetreCreerEntite() {
    // cr�ation du tableau � envoyer en arg()
    bool tab[VOCABULATEUR_NB_STATUT];
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        tab[i] = 0;
    // cr�ation de la fenetre
    fenEntite wEnti(vocab, tab, true, this);
    // ex�cution de la fenetre
    wEnti.exec();
}


// Affiche la fenetre de modification d'entit�
void fenetre::affFenetreModifEntite() {
    // protection contre la non s�lection : si la liste des items s�lectionn�s est vide ou si la ligne s�lectionn�e est la premi�re, ou pas dans la table
    if(w_Selection->row() <= 0)  return;
    // cr�ation du tableau � envoyer en arg()
    bool tab[VOCABULATEUR_NB_STATUT];
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        tab[i] = liste_Entite[w_Selection->row()-1]->getStatut(i);
    // cr�ation de la fenetre
    fenEntite wEnti(vocab, tab, false, this);
    // ex�cution de la fenetre
    wEnti.exec();
}


// Affiche la fenetre d'ajout d'entit�
void fenetre::affFenetreOptions() {
    // cr�ation de la fenetre
    fenOptions wOpt(vocab, this);
    // ex�cution de la fenetre
    wOpt.exec();
}



// Affiche la boite de dialogue causant du programme
void fenetre::OuvertureAPropos() {
    AboutFen APropos(this);
    APropos.exec();
}

// Vide la table d'entit�
void fenetre::reinitialisationPrgm() {
    // on vide la m�moire
    for(unsigned int i = 0; i < liste_Entite.size(); i++) delete liste_Entite[i];
    // on retire les cases de la liste
    while(liste_Entite.size() > 0)  liste_Entite.pop_back();
    // et on affiche la table !
    affichageTable();
}

// Re�ois la config de la table d'option
void fenetre::recevoirConfig(bool *tabOptions) {
    // s�curit�
    w_Selection = NULL;
    // acutalisation de la liste d'options
    for(int i = 0; i < OPT_NB_OPTIONS; i++)
        w_BoolOption[i] = tabOptions[i];
    w_Table->setColumnCount(0); // aucune colonne
    while(w_Colonnes.size() > 0) w_Colonnes.pop_back(); // suppression de l'index des colonnes
    initialisationColonne(); // on initialise le nombre de colonnes
    w_Table->setColumnCount(w_Colonnes.size()); // cr�ation des colonnes
    // on initialise la table
    initialisation_Table();
    // on affiche son contenu !
    affichageTable();
}


// Appel� par le bouton Quit, il g�re la m�moire en fin de programme
void fenetre::FinPRGM() {
    // on vide la m�moire
    for(unsigned int i = 0; i < liste_Entite.size(); i++) delete liste_Entite[i];
    // on retire les cases de la liste
    while(liste_Entite.size() > 0)  liste_Entite.pop_back();
    // pas besoin de g�rer les allocations m�moires d'objets Qt : il se d�charge lui-m�me.
    qApp->quit(); // on quitte l'application
}


// ==============================================
//              METHODES FENETRE
// ==============================================
// lis la liste d'entit�, et les affiche rang�es dans la table
void fenetre::affichageTable() {
    // sauvegarde de l'endroit s�lectionn� par l'utilisateur
    int ligne = -1;
    if(w_Selection != NULL)     ligne = w_Selection->row();
    // Suppression du contenu de la table (on ne garde que la premi�re ligne)
    w_Table->setRowCount(1);
    // Puis on lui donne sa v�ritable taille
    w_Table->setRowCount(1+liste_Entite.size());
    // Triage du vector selon priorit�s
    triageListeEntite();
    // affichage des entit�s dans la table
    remplissageTable();
    // coloration des lignes
    colorerTable();
    // on res�lectionne ce qu'on avait s�lectionn�, ou rien si l'a ligne n'existe plus (ce qui ne devrais pas se produire)
    if(ligne == -1) return; // si yavais rien de s�lectionn�, pas la peine d'effectuer les lignes suivantes
    if(ligne < w_Table->rowCount()) {
        w_Selection = w_Table->item(ligne, 0);
        if(ligne == 0)  validiteBouton(false);
        else            validiteBouton(true);
    }
    else {
        w_Selection = w_Table->item(0, 0);
        validiteBouton(false);
    }
}


// supprime l'�l�ment d'ID envoy� en argument dans la liste d'entit�, ainsi que la case elle-m�me
void fenetre::supprimerElementListeEntite(int ID) {
    vector<entite*> inter;
    for(unsigned int i = 0; i < liste_Entite.size(); i++) {
        if(i != (unsigned int)ID)
            inter.push_back(liste_Entite[i]);
    }
    CopieContenuVector(inter, liste_Entite);
}


// remplacement du vocabulaire vide par les noms g�n�riques
void fenetre::correctionVocabulaire() {
    // cr�ation du tableau du vocabulaire par d�faut
    QString vocab_defaut[VOCABULATEUR_NB_MOT] = {"entit�", "Nom", "Figurine", "Priorit�", "Camp", "PJ", "Alli�", "Ennemi", "Autre", "Statut",
    "Statut0", "Statut1", "Statut2", "Statut3", "Statut4", "Statut5", "Statut6", "Statut7", "Statut8", "Statut9", "Statut10", "Statut11"};
    // Parcours du vocabulaire renvoy� par le vocabulateur, qui rapellons-le renvoit une chaine vide si l'utilisateur n'a rien donn�
    for(int i = 0; i < VOCABULATEUR_NB_MOT; i++) {
        if(vocab[i] == "") {
            vocab[i] = vocab_defaut[i];
        }
    }
}


// g�re la validit� de certains boutons suivant le bol�en
void fenetre::validiteBouton(bool activer) {
    w_EditEntite->setEnabled(activer);
    w_SuprEntite->setEnabled(activer);
    w_DefJoueur->setEnabled(activer);
}


// ==============================================
//              METHODES ENTITES
// ==============================================
// renvois une chaine contenant les noms des statut exprim� chez l'entit� en arg()
string fenetre::getStatut(entite *ent) {
    string result = "";
    for(int  i = 0; i < VOCABULATEUR_NB_STATUT; i++) {
        if(ent->getStatut(i)) { // si ce statut est activ�
            result += qstr2Str(vocab[i+10]); // ajout du vocabulaire de statut, �gal au num�ro de case, +10 (car le premier statut est le 10�me num�ro du vocabulaire)
            if(i != VOCABULATEUR_NB_STATUT-1)   result += ", "; // s'il ne s'agit pas de la derni�re case
        }
    }
    return result;
}
