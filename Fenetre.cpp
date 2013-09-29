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
    // on vérifie maintenant ce qu'on obtient : le vocabulateur renvoie des chaînes vides s'il ne lit rien !
    //      Dans ce cas, on remplace par le nom générique
    correctionVocabulaire();

    // TABLE
    initialisationOptions(); // lecture des options
    initialisationColonne(); // calcul du nombre de colonne en fonction des options

    w_Table = new QTableWidget(0, w_Colonnes.size(), this); // 0 lignes et 3 colonnes
        w_Table->setSelectionBehavior(QAbstractItemView::SelectRows); // l'utilisateur ne peut sélectionner que les lignes
        // mettre la table dans un conteneur
        QVBoxLayout *LayTable = new QVBoxLayout;
            LayTable->addWidget(w_Table);
        QGroupBox *groupeTable = new QGroupBox("Table des " + vocab[VOC_ENTITE] + "s", this);
            groupeTable->setLayout(LayTable);

    initialisation_Table(); // initialisation de la table selon le fichier FILE_OPTIONS

    // liste d'entités
    w_Joueur = NULL; // entité qui commence : aucune pour le moment
    w_Selection = NULL; // Aucune ligne n'est sélectionnée au tout début
    affichageTable();

    // QPUSHBUTTONS
    constructionBoutons();

    // LAYOUTS
    QHBoxLayout *LayFen = new QHBoxLayout(this); // layout principal de fenêtre

    QVBoxLayout *LayButtonDroit = new QVBoxLayout; // Layout contenant les layouts contenant les boutons à droite
        QVBoxLayout *LayButtonDroitEntite = new QVBoxLayout; // Layout contenant les boutons à droite relatifs à l'entité
            LayButtonDroitEntite->addWidget(w_NouvEntite);
            LayButtonDroitEntite->addWidget(w_ChargerGroupe);
            LayButtonDroitEntite->addWidget(w_EditEntite);
            LayButtonDroitEntite->addWidget(w_SuprEntite);
        QVBoxLayout *LayButtonDroitTour = new QVBoxLayout; // Layout contenant les boutons à droite relatifs aux tours de jeu
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
    QObject::connect(w_Quit, SIGNAL(clicked()), this, SLOT(FinPRGM())); // quitter avec gestion mémoire liée
    QObject::connect(w_APropos, SIGNAL(clicked()), this, SLOT(OuvertureAPropos())); // déclencher l'ouverture d'une boite de dialogue à propos du programme
    QObject::connect(w_Reset, SIGNAL(clicked()), this, SLOT(reinitialisationPrgm())); // déclencher la vidange de la table
    QObject::connect(w_Options, SIGNAL(clicked()), this, SLOT(affFenetreOptions())); // déclencher l'ouverture de la fenetre d'options
    // boutons volet droit
    QObject::connect(w_NouvEntite, SIGNAL(clicked()), this, SLOT(affFenetreCreerEntite())); // affichage de la fenetre de création
    QObject::connect(w_ChargerGroupe, SIGNAL(clicked()), this, SLOT(ajoutGroupeEntite())); // chargement des entités de groupe
    QObject::connect(w_EditEntite, SIGNAL(clicked()), this, SLOT(affFenetreModifEntite())); // affichage de la fenetre d'édition
    QObject::connect(w_SuprEntite, SIGNAL(clicked()), this, SLOT(supressionEntite())); // amorçage de la suppression d'entité sélectionnée
    QObject::connect(w_PassageTour, SIGNAL(clicked()), this, SLOT(passageTourSuivant())); // amorçage de la suppression d'entité sélectionnée
    QObject::connect(w_DefJoueur, SIGNAL(clicked()), this, SLOT(definirJoueur())); // amorçage de la suppression d'entité sélectionnée
    // lorsque l'on clique sur un item de la table, on le sélectionne
    QObject::connect(w_Table, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(selectionEntite(QTableWidgetItem*)));
}


// construit les boutons lors de la création de la fenetre
void fenetre::constructionBoutons() {
    w_Quit = new QPushButton("Quitter", this);
        w_Quit->setToolTip("Ferme JDInit");
    w_APropos = new QPushButton("A Propos", this);
        w_APropos->setToolTip("Ouvre une fenêtre d'information sur JDInit");
    w_Options = new QPushButton("Options", this);
        w_Options->setToolTip("Ouvre une fenêtre de configuration de JDInit");
    w_Reset = new QPushButton("Réinitialiser", this);
        w_Reset->setToolTip("Supprime l'ensemble des " + vocab[VOC_ENTITE] + " de la table");
    w_PassageTour = new QPushButton("Joueur suivant", this);
        w_PassageTour->setToolTip("Fait évoluer le marqueur dans la table jusqu'au prochain joueur");
    w_DefJoueur = new QPushButton("Définir comme joueur", this);
        w_DefJoueur->setToolTip("Définition de " + vocab[VOC_ENTITE] + " comme joueur");
    w_NouvEntite = new QPushButton("Ajouter " + vocab[VOC_ENTITE] + "s", this);
        w_NouvEntite->setToolTip("Ouvre la fenetre d'ajout de " + vocab[VOC_ENTITE]);
    w_ChargerGroupe = new QPushButton("Ajouter groupe", this);
        w_ChargerGroupe->setToolTip("Ajoute dans la table les " + vocab[VOC_ENTITE] + "s contenu dans le fichier Groupe.Alk");
    w_EditEntite = new QPushButton("Editer", this);
        w_EditEntite->setToolTip("Ouvre la fenetre de modification de " + vocab[VOC_ENTITE]);
    w_SuprEntite = new QPushButton("Supprimer", this);
        w_SuprEntite->setToolTip("Suppression de " + vocab[VOC_ENTITE]);

    // Parce qu'aucune ligne n'est sélectionnée au début
    w_EditEntite->setEnabled(false);
    w_SuprEntite->setEnabled(false);
    w_DefJoueur->setEnabled(false);
    w_PassageTour->setEnabled(false); // et qu'il n'y a pas d'entité prédéfinie
}


// initialise les boléen d'options en fonction du contenu du fichier FILE_OPTIONS
void fenetre::initialisationOptions() {
    string ligne = "";
    int compteur = 0;
    // lecture du fichier pour savoir lesquels sont activés/désactivés
    ifstream opt(FILE_OPTIONS);
    // gestion erreur d'ouverture
    if(!opt) {
        FLUX_ERREUR("GESTION D'OPTIONS", "Erreur d'ouverture du fichier File/Config.Alk en lecture.");
        return;
    }
    // lecture du fichier
    while(getline(opt, ligne)) {
        if(ligne.size() == 1) {
            // on met une valeur égale à 0 ou 1 (avec le décalage en ASCII)
            if((ligne[0] - 48) == 0)
                w_BoolOption[compteur] = false;
            else
                w_BoolOption[compteur] = true;
        }
        else { // arrivés là, c'est que la ligne était plus longue que prévus. Le fichiers a été édité ou écrasé par autre chose que le programme.
            FLUX_ERREUR("GESTION D'OPTIONS", "Fichier File/Config.Alk Corrompu.");
            w_BoolOption[compteur] = false;
        }
        compteur++;
    }
    opt.close(); // fermeture du fichier
}

// initialise le vector de colonne en fonction des boléen
void fenetre::initialisationColonne() {
    w_Colonnes.push_back(qstr2Str(vocab[VOC_NOM]));             // création de la colonne pour le nom, obligatoire
    if(w_BoolOption[OPT_AFF_FIG])                               // si c'est demandé, on met la colonne figurine
        w_Colonnes.push_back(qstr2Str(vocab[VOC_FIGURINE]));
    w_Colonnes.push_back(qstr2Str(vocab[VOC_PRIORITE]));         // on met la colonne de priorité
    if(w_BoolOption[OPT_AFF_STATUT])                            // si c'est demandé, on met la colonne statut
        w_Colonnes.push_back(qstr2Str(vocab[VOC_STATUT]));
    if(w_BoolOption[OPT_AFF_CAMP])                              // si c'est demandé, on met la colonne camp
        w_Colonnes.push_back(qstr2Str(vocab[VOC_CAMP]));
}





// =============================
//      SLOTS
// =============================
// créé l'entité selon arg() et la place dans la table
void fenetre::ajoutEntite(QString nom, QString fig, int prio, QString camps, bool* opt) {
    // création d'une nouvelle entité
    liste_Entite.push_back(new entite(qstr2Str(nom), qstr2Str(fig), prio, qstr2Str(camps), opt));
    // test pour savoir si cette entité est la première, et donc l'entité à qui c'est le tour
    if(liste_Entite.size() == 1) w_Joueur = liste_Entite[0];
    // le bouton pour passer au tour suivant peut être actif
    if(liste_Entite.size() > 1) w_PassageTour->setEnabled(true);
    // puis affichage de la table
    affichageTable();
}


// modifie l'entité sélectionnée selon arg()
void fenetre::modifEntite(QString nom, QString fig, int prio, QString camps, bool* opt) {
    // protection contre la non sélection
    if(w_Selection == NULL) return;
    // localisation de l'entité sélectionnée
    int ligne = w_Selection->row();
    // protection contre la non sélection : si la ligne sélectionnée est la première, ou n'est pas dans la table
    if(ligne <= 0)     return;
    entite *etude = liste_Entite[ligne-1];
    // modification des attributs, si quelque chose est changé
    if(nom != "Inchangé")   etude->SetNom(qstr2Str(nom));
    if(fig != "Inchangé")   etude->SetFigurine(qstr2Str(fig));
    if(prio != -1)          etude->SetPriorite(prio);
    if(camps != "Inchangé") etude->SetCamps(qstr2Str(camps));
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        etude->SetStatut(i,opt[i]); // modif de la valeur de statut
    // puis affichage de la table
    affichageTable();
}

// Ajoute le groupe d'entité décrites dans le fichier FILE_GROUPE
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
                // si on est au premier champ (compteur à 0)
                if(compteur == 0)
                    nom = mot; // attribution de l'expression lue au nom
                else
                    fig = mot; // attribution de l'expression lue à la figurine
                mot = "";   // on vide l'expression en cours
                compteur++;
            }
            else
                mot += ligne[i]; // on ajoute le caractère lu.
        }
        // la ligne est parcourue : il ne reste plus qu'à créer l'entité correspondante.
        bool opt[VOCABULATEUR_NB_STATUT]; // création et initialisation du tableau
        for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++) opt[i] = 0;
        liste_Entite.push_back(new entite(nom, fig, 0, qstr2Str(vocab[VOC_PJ]), opt));
        // les variables sont remises à zéro. sinon c'est le dawa.
        compteur = 0;
        fig = nom = mot = "";
    }
    // enfin, affichage de la table
    affichageTable();
}


// Supression de l'entité sélectionnée
void fenetre::supressionEntite() {
    // protection contre la non sélection
    if(w_Selection == NULL) return;
    int ligne = w_Selection->row();
    // protection contre la non sélection : si la ligne sélectionnée est la première, ou n'est pas dans la table
    if(ligne <= 0)     return;
    bool pasBouger = false; // vrai si la ligne supprimée est celle de l'entité joueuse

    // si l'entité qu'on supprime est celle à qui c'était le tour
    if(w_Joueur == liste_Entite[ligne-1]) {
        // ET qu'il ne s'agit pas de la dernière ligne
        if((unsigned int)ligne < liste_Entite.size())
            pasBouger = true;
        else if(liste_Entite.size() > 1) { // si il s'agit de la dernière ligne et qu'il y a plus d'un élément
            w_Joueur = liste_Entite[0]; // on pointe la première entité
            w_Selection = w_Table->item(w_Table->rowCount()-1,0); // la sélection pointe le dernier élément
            // protection contre la sélection de la ligne de référence
            if(w_Selection->row() == 0)    validiteBouton(false); // les boutons sont invalidés
        }
        else { // sinon, c'est qu'il n'y a plus d'entités
            w_Joueur = NULL;
            w_Selection = w_Table->item(0,0); // la sélection pointe la première ligne
            validiteBouton(false); // les boutons sont invalidés
        }
    }

    // on supprime l'entité correspondant à la ligne
    delete liste_Entite[ligne-1];
    supprimerElementListeEntite(ligne-1);

    // si le pointeur w_Joueur devait rester sur la même case
    if(pasBouger) {
        w_Joueur = liste_Entite[ligne-1]; // alors w_Joueur pointe vers l'élément qui remplace l'entité supprimée
        w_Selection = w_Table->item(ligne,0); // et la sélection pointe vers ce dernier
    }

    // le bouton pour passer au tour suivant peut être rendu inactif
    if(liste_Entite.size() <= 1) w_PassageTour->setEnabled(false);
    // puis affichage de la table
    affichageTable();
}



// Affiche la fenetre d'ajout d'entité
void fenetre::affFenetreCreerEntite() {
    // création du tableau à envoyer en arg()
    bool tab[VOCABULATEUR_NB_STATUT];
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        tab[i] = 0;
    // création de la fenetre
    fenEntite wEnti(vocab, tab, true, this);
    // exécution de la fenetre
    wEnti.exec();
}


// Affiche la fenetre de modification d'entité
void fenetre::affFenetreModifEntite() {
    // protection contre la non sélection : si la liste des items sélectionnés est vide ou si la ligne sélectionnée est la première, ou pas dans la table
    if(w_Selection->row() <= 0)  return;
    // création du tableau à envoyer en arg()
    bool tab[VOCABULATEUR_NB_STATUT];
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        tab[i] = liste_Entite[w_Selection->row()-1]->getStatut(i);
    // création de la fenetre
    fenEntite wEnti(vocab, tab, false, this);
    // exécution de la fenetre
    wEnti.exec();
}


// Affiche la fenetre d'ajout d'entité
void fenetre::affFenetreOptions() {
    // création de la fenetre
    fenOptions wOpt(vocab, this);
    // exécution de la fenetre
    wOpt.exec();
}



// Affiche la boite de dialogue causant du programme
void fenetre::OuvertureAPropos() {
    AboutFen APropos(this);
    APropos.exec();
}

// Vide la table d'entité
void fenetre::reinitialisationPrgm() {
    // on vide la mémoire
    for(unsigned int i = 0; i < liste_Entite.size(); i++) delete liste_Entite[i];
    // on retire les cases de la liste
    while(liste_Entite.size() > 0)  liste_Entite.pop_back();
    // et on affiche la table !
    affichageTable();
}

// Reçois la config de la table d'option
void fenetre::recevoirConfig(bool *tabOptions) {
    // sécurité
    w_Selection = NULL;
    // acutalisation de la liste d'options
    for(int i = 0; i < OPT_NB_OPTIONS; i++)
        w_BoolOption[i] = tabOptions[i];
    w_Table->setColumnCount(0); // aucune colonne
    while(w_Colonnes.size() > 0) w_Colonnes.pop_back(); // suppression de l'index des colonnes
    initialisationColonne(); // on initialise le nombre de colonnes
    w_Table->setColumnCount(w_Colonnes.size()); // création des colonnes
    // on initialise la table
    initialisation_Table();
    // on affiche son contenu !
    affichageTable();
}


// Appelé par le bouton Quit, il gère la mémoire en fin de programme
void fenetre::FinPRGM() {
    // on vide la mémoire
    for(unsigned int i = 0; i < liste_Entite.size(); i++) delete liste_Entite[i];
    // on retire les cases de la liste
    while(liste_Entite.size() > 0)  liste_Entite.pop_back();
    // pas besoin de gérer les allocations mémoires d'objets Qt : il se décharge lui-même.
    qApp->quit(); // on quitte l'application
}


// ==============================================
//              METHODES FENETRE
// ==============================================
// lis la liste d'entité, et les affiche rangées dans la table
void fenetre::affichageTable() {
    // sauvegarde de l'endroit sélectionné par l'utilisateur
    int ligne = -1;
    if(w_Selection != NULL)     ligne = w_Selection->row();
    // Suppression du contenu de la table (on ne garde que la première ligne)
    w_Table->setRowCount(1);
    // Puis on lui donne sa véritable taille
    w_Table->setRowCount(1+liste_Entite.size());
    // Triage du vector selon priorités
    triageListeEntite();
    // affichage des entités dans la table
    remplissageTable();
    // coloration des lignes
    colorerTable();
    // on resélectionne ce qu'on avait sélectionné, ou rien si l'a ligne n'existe plus (ce qui ne devrais pas se produire)
    if(ligne == -1) return; // si yavais rien de sélectionné, pas la peine d'effectuer les lignes suivantes
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


// supprime l'élément d'ID envoyé en argument dans la liste d'entité, ainsi que la case elle-même
void fenetre::supprimerElementListeEntite(int ID) {
    vector<entite*> inter;
    for(unsigned int i = 0; i < liste_Entite.size(); i++) {
        if(i != (unsigned int)ID)
            inter.push_back(liste_Entite[i]);
    }
    CopieContenuVector(inter, liste_Entite);
}


// remplacement du vocabulaire vide par les noms génériques
void fenetre::correctionVocabulaire() {
    // création du tableau du vocabulaire par défaut
    QString vocab_defaut[VOCABULATEUR_NB_MOT] = {"entité", "Nom", "Figurine", "Priorité", "Camp", "PJ", "Allié", "Ennemi", "Autre", "Statut",
    "Statut0", "Statut1", "Statut2", "Statut3", "Statut4", "Statut5", "Statut6", "Statut7", "Statut8", "Statut9", "Statut10", "Statut11"};
    // Parcours du vocabulaire renvoyé par le vocabulateur, qui rapellons-le renvoit une chaine vide si l'utilisateur n'a rien donné
    for(int i = 0; i < VOCABULATEUR_NB_MOT; i++) {
        if(vocab[i] == "") {
            vocab[i] = vocab_defaut[i];
        }
    }
}


// gère la validité de certains boutons suivant le boléen
void fenetre::validiteBouton(bool activer) {
    w_EditEntite->setEnabled(activer);
    w_SuprEntite->setEnabled(activer);
    w_DefJoueur->setEnabled(activer);
}


// ==============================================
//              METHODES ENTITES
// ==============================================
// renvois une chaine contenant les noms des statut exprimé chez l'entité en arg()
string fenetre::getStatut(entite *ent) {
    string result = "";
    for(int  i = 0; i < VOCABULATEUR_NB_STATUT; i++) {
        if(ent->getStatut(i)) { // si ce statut est activé
            result += qstr2Str(vocab[i+10]); // ajout du vocabulaire de statut, égal au numéro de case, +10 (car le premier statut est le 10ème numéro du vocabulaire)
            if(i != VOCABULATEUR_NB_STATUT-1)   result += ", "; // s'il ne s'agit pas de la dernière case
        }
    }
    return result;
}
