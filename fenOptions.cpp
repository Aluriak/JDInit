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
    initialisationTabOpt();         // lit FILE_OPTIONS et en d�duit l'intialisation du tableau e_opt
    initialisationQCheckBox();      // g�re les QCheckBox
    // QPushButtons
    e_Quit = new QPushButton("Fermer", this);
    e_Save = new QPushButton("Fermer et sauvegarder", this);

    QVBoxLayout *LayoutAffichageTable = new QVBoxLayout; // contient les widgets relatifs � l'afichage de la table
        LayoutAffichageTable->addWidget(e_affFig);
        LayoutAffichageTable->addWidget(e_affStatut);
        LayoutAffichageTable->addWidget(e_affCamp);
        QGroupBox *groupeAffichageTable = new QGroupBox("Table des " + vocab[VOC_ENTITE] + "s", this); // contient les options relatives � l'affichage de la table
            groupeAffichageTable->setLayout(LayoutAffichageTable);

    QHBoxLayout *LayoutAffichageFenOption = new QHBoxLayout; // contient les widgets relatifs � la fenetre d'option elle-m�me
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
// appel� lorsque le bouton d'enregistrement est cliqu�. Ferme la fen�tre et envois le signal de modifs des param�tres de la fenetre
void fenOptions::enregistrerConfiguration() {
    // chaque param�tre est �quivalent au bol�en du checkbox associ�
    e_opt[OPT_AFF_FIG] = e_affFig->isChecked();
    e_opt[OPT_AFF_STATUT] = e_affStatut->isChecked();
    e_opt[OPT_AFF_CAMP] = e_affCamp->isChecked();
    actualisationFichier(); // inscription dans le fichiers de ces param�tres.
    emettreSignal();        // �mission du signal
    accept();               // quitter la fenetre
}






// =============================
//      METHODES
// =============================
// inscrit dans le fichier FILE_OPTIONS les valeurs de configuration
void fenOptions::actualisationFichier() {
    ofstream opt(FILE_OPTIONS); // on ouvre en �criture, en supprimant l'ancien contenu
    for(int i = 0; i < OPT_NB_OPTIONS; i++)
        opt << num2str(e_opt[i]) << endl;
    // le fichier est donc compos� d'une suite de lignes ne comportant qu'un z�ro ou qu'un un.
}


// �met de le signal selon les attributs de la fenetre
void fenOptions::emettreSignal() {
    emit envoisParametreParent(e_opt);
}


// g�re les QCheckBox en lisant dans le fichier FILE_OPTIONS
void fenOptions::initialisationQCheckBox() {
    e_affFig = new QCheckBox("Gestion des " + vocab[VOC_FIGURINE] + "s", this);
        e_affFig->setChecked(e_opt[OPT_AFF_FIG]); // on checke si le fichier � dit qu'il l'�tait
    e_affStatut = new QCheckBox("Gestion des " + vocab[VOC_STATUT] + "s", this);
        e_affStatut->setChecked(e_opt[OPT_AFF_STATUT]); // on checke si le fichier � dit qu'il l'�tait
    e_affCamp = new QCheckBox("Gestion des " + vocab[VOC_CAMP] + "s", this);
        e_affCamp->setChecked(e_opt[OPT_AFF_CAMP]); // on checke si le fichier � dit qu'il l'�tait
}


// lit FILE_OPTIONS et en d�duit l'intialisation du tableau e_opt
void fenOptions::initialisationTabOpt() {
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
                e_opt[compteur] = false;
            else
                e_opt[compteur] = true;
        }
        else { // arriv�s l�, c'est que la ligne �tait plus longue que pr�vus. Le fichiers a �t� �dit� ou �cras� par autre chose que le programme.
            FLUX_ERREUR("GESTION D'OPTIONS", "Fichier File/Config.Alk Corrompu.");
            e_opt[compteur] = false;
        }
        compteur++;
    }
    opt.close(); // fermeture du fichier
}


