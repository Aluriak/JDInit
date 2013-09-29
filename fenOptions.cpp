#include "main.h"

using namespace std;



// ==============================================
//              CONSTRUCTEUR
// ==============================================
fenOptions::fenOptions(QString vocab_parent[], QWidget *parent) : QDialog(parent) {
    setWindowTitle("Options de " + str2Qstr(PRGM_NOM)); // titre de la fenetre
    setFixedSize(PRGM_LARGEUR_FENETRE_OPTIONS, PRGM_HAUTEUR_FENETRE_OPTIONS); // dimension de la fenetre.

    // recopie du vocabulaire
    for(int i = 0; i < VOCABULATEUR_NB_MOT; i++)
        vocab[i] = vocab_parent[i];

    // QCheckBox
    initialisationTabOpt();         // lit FILE_OPTIONS et en déduit l'intialisation du tableau e_opt
    initialisationQCheckBox();      // gère les QCheckBox
    // QPushButtons
    e_Quit = new QPushButton("Fermer", this);
    e_Save = new QPushButton("Fermer et sauvegarder", this);

    QVBoxLayout *LayoutAffichageTable = new QVBoxLayout; // contient les widgets relatifs à l'afichage de la table
        LayoutAffichageTable->addWidget(e_affFig);
        LayoutAffichageTable->addWidget(e_affStatut);
        LayoutAffichageTable->addWidget(e_affCamp);
        QGroupBox *groupeAffichageTable = new QGroupBox("Table des " + vocab[VOC_ENTITE] + "s", this); // contient les options relatives à l'affichage de la table
            groupeAffichageTable->setLayout(LayoutAffichageTable);

    QHBoxLayout *LayoutAffichageFenOption = new QHBoxLayout; // contient les widgets relatifs à la fenetre d'option elle-même
        LayoutAffichageFenOption->addWidget(e_Quit);
        LayoutAffichageFenOption->addWidget(e_Save);
        QGroupBox *groupeFenOption = new QGroupBox(this); // contient les boutons de fenetre
            groupeFenOption->setLayout(LayoutAffichageFenOption);

    QVBoxLayout *LayFen = new QVBoxLayout(this); // contient l'ensemble des QGroupBox
        LayFen->addWidget(groupeAffichageTable);
        LayFen->addWidget(groupeFenOption);
    // CONNEXIONS
    QObject::connect(this, SIGNAL(envoisParametreParent(bool*)), parent, SLOT(recevoirConfig(bool*)));
    QObject::connect(e_Quit, SIGNAL(clicked()), this, SLOT(accept()));          // quitter la fenetre sans rien changer
    QObject::connect(e_Save, SIGNAL(clicked()), this, SLOT(enregistrerConfiguration()));          // quitter la fenetre avec sauvegarde
}









// =============================
//      SLOTS
// =============================
// appelé lorsque le bouton d'enregistrement est cliqué. Ferme la fenêtre et envois le signal de modifs des paramètres de la fenetre
void fenOptions::enregistrerConfiguration() {
    // chaque paramètre est équivalent au boléen du checkbox associé
    e_opt[OPT_AFF_FIG] = e_affFig->isChecked();
    e_opt[OPT_AFF_STATUT] = e_affStatut->isChecked();
    e_opt[OPT_AFF_CAMP] = e_affCamp->isChecked();
    actualisationFichier(); // inscription dans le fichiers de ces paramètres.
    emettreSignal();        // émission du signal
    accept();               // quitter la fenetre
}






// =============================
//      METHODES
// =============================
// inscrit dans le fichier FILE_OPTIONS les valeurs de configuration
void fenOptions::actualisationFichier() {
    ofstream opt(FILE_OPTIONS); // on ouvre en écriture, en supprimant l'ancien contenu
    for(int i = 0; i < OPT_NB_OPTIONS; i++)
        opt << num2str(e_opt[i]) << endl;
    // le fichier est donc composé d'une suite de lignes ne comportant qu'un zéro ou qu'un un.
}


// émet de le signal selon les attributs de la fenetre
void fenOptions::emettreSignal() {
    emit envoisParametreParent(e_opt);
}


// gère les QCheckBox en lisant dans le fichier FILE_OPTIONS
void fenOptions::initialisationQCheckBox() {
    e_affFig = new QCheckBox("Gestion des " + vocab[VOC_FIGURINE] + "s", this);
        e_affFig->setChecked(e_opt[OPT_AFF_FIG]); // on checke si le fichier à dit qu'il l'était
    e_affStatut = new QCheckBox("Gestion des " + vocab[VOC_STATUT] + "s", this);
        e_affStatut->setChecked(e_opt[OPT_AFF_STATUT]); // on checke si le fichier à dit qu'il l'était
    e_affCamp = new QCheckBox("Gestion des " + vocab[VOC_CAMP] + "s", this);
        e_affCamp->setChecked(e_opt[OPT_AFF_CAMP]); // on checke si le fichier à dit qu'il l'était
}


// lit FILE_OPTIONS et en déduit l'intialisation du tableau e_opt
void fenOptions::initialisationTabOpt() {
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
                e_opt[compteur] = false;
            else
                e_opt[compteur] = true;
        }
        else { // arrivés là, c'est que la ligne était plus longue que prévus. Le fichiers a été édité ou écrasé par autre chose que le programme.
            FLUX_ERREUR("GESTION D'OPTIONS", "Fichier File/Config.Alk Corrompu.");
            e_opt[compteur] = false;
        }
        compteur++;
    }
    opt.close(); // fermeture du fichier
}


