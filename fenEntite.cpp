#include "main.h"

using namespace std;




// ==============================================
//              CONSTRUCTEUR
// ==============================================
fenEntite::fenEntite(QString vocab_parent[], bool *tabStat, bool creation, QWidget *parent) : QDialog(parent), e_Creation(creation) {
    // titre de la fenetre, d�pendant de l'action � faire
    if(creation)    setWindowTitle(PRGM_NOM_FEN_ENTITE_CREAT + vocab_parent[0]);
    else            setWindowTitle(PRGM_NOM_FEN_ENTITE_MODIF + vocab_parent[0]);
    setFixedSize(PRGM_LARGEUR_FENETRE_ENTITE, PRGM_HAUTEUR_FENETRE_ENTITE); // dimension de la fenetre.

    // Gestion vocabulaire
    for(int i = 0; i < VOCABULATEUR_NB_MOT; i++) {
        vocab[i] = vocab_parent[i];
    }

    // ATTRIBUTS
    Nom = new QLineEdit(vocab[VOC_ENTITE], this);
        Nom->setToolTip(vocab[VOC_NOM] + " de " + vocab[VOC_ENTITE]);
        if(!creation) // si on �dite une entit�, on propose de ne pas changer la valeur
            Nom->setText("Inchang�");
        Nom->setMaxLength(25);

    Fig = new QLineEdit(vocab[VOC_FIGURINE], this);
        Fig->setToolTip(vocab[VOC_FIGURINE] + " de " + vocab[VOC_ENTITE]);
        if(!creation) // si on �dite une entit�, on propose de ne pas changer la valeur
            Fig->setText("Inchang�");
        Nom->setMaxLength(25);

    Prio = new QDoubleSpinBox(this);
        Prio->setToolTip(vocab[VOC_PRIORITE] + " de " + vocab[VOC_ENTITE]);
        Prio->setMaximum(100);
        if(!creation) Prio->setMinimum(-1); // si on �dite une entit�, on propose la valeur -1, correspondant au non changement d'initiative
        else          Prio->setMinimum(0);
        Prio->setDecimals(0);
        Prio->setPrefix(vocab[VOC_PRIORITE] + " : ");
        Prio->setValue(-1); // valeur d'entr�e �gale au minimum possible

    Camps = new QComboBox(this);
        Camps->setToolTip(vocab[VOC_CAMP] + " de " + vocab[VOC_ENTITE]);
        if(!creation) // si on �dite une entit�, on propose de ne pas changer la valeur
            Camps->addItem("Inchang�");
        Camps->addItem(vocab[VOC_PJ]);
        Camps->addItem(vocab[VOC_ALLIE]);
        Camps->addItem(vocab[VOC_ENNEMI]);
        Camps->addItem(vocab[VOC_AUTRE]);

    QGroupBox *groupStatuts = new QGroupBox(vocab[VOC_STATUT]);
    QVBoxLayout *LayStatutGauche = new QVBoxLayout; // contients les status � gauche
    QVBoxLayout *LayStatutDroite = new QVBoxLayout; // contients les status � droite
    QHBoxLayout *LayStatuts = new QHBoxLayout; // contients les status
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++) {
        Status[i] = new QCheckBox(vocab[i+10], this); // cr�ation du checkbox avec le texte correspondant au statut li�
        // si le tableau status indique que le checkbox doit �tre coch�
        if(tabStat[i])  Status[i]->setChecked(true);
        else            Status[i]->setChecked(false);
        // selon le num�ro de cette aptitude, on le place dans l'une ou l'autre des colonne de statut
        if(i < VOCABULATEUR_NB_STATUT/2)
            LayStatutGauche->addWidget(Status[i]);
        else
            LayStatutDroite->addWidget(Status[i]);
    }
    // on r�unis les deux colonnes de status en un layout, contenu du groupbox.
    LayStatuts->addLayout(LayStatutGauche);
    LayStatuts->addLayout(LayStatutDroite);
    groupStatuts->setLayout(LayStatuts);

    // BOUTONS
    if(creation)            Annuler = new QPushButton("Fermer", this);
    else                    Annuler = new QPushButton("Annuler modification", this);
    if(creation)            Appliquer = new QPushButton("Cr�er", this);
    else                    Appliquer = new QPushButton("Modifier", this);


    // LAYOUTS
    QHBoxLayout *LayBouton = new QHBoxLayout; // layout des boutons
        LayBouton->addWidget(Appliquer);
        LayBouton->addWidget(Annuler);
    QHBoxLayout *LayDefLine = new QHBoxLayout; // contient l'espace pour le nom et la figurine
        LayDefLine->addWidget(Nom);
        LayDefLine->addWidget(Fig);
    QHBoxLayout *LayDefBox = new QHBoxLayout; // contient l'espace pour la priorit� et le camps
        LayDefBox->addWidget(Prio);
        LayDefBox->addWidget(Camps);
    QVBoxLayout *LayDef = new QVBoxLayout; // contient les deux layouts de d�finition
        LayDef->addLayout(LayDefLine);
        LayDef->addLayout(LayDefBox);

    QGroupBox *groupDefinition = new QGroupBox("D�finition de " + vocab[VOC_ENTITE]);
        groupDefinition->setLayout(LayDef); // contient les quatres champs de d�finition

    QVBoxLayout *LayFen = new QVBoxLayout(this); // layout de la fenetre
        LayFen->addWidget(groupDefinition);
        LayFen->addWidget(groupStatuts);
        LayFen->addLayout(LayBouton);

    // CONNECTIONS
    QObject::connect(Annuler, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(Appliquer, SIGNAL(clicked()), this, SLOT(configTerminee()));

    QObject::connect(this, SIGNAL(creationTerminee(QString, QString, int, QString, bool*)), parent, SLOT(ajoutEntite(QString, QString, int, QString, bool*)));
    QObject::connect(this, SIGNAL(modifTerminee(QString, QString, int, QString, bool*)), parent, SLOT(modifEntite(QString, QString, int, QString, bool*)));
}





// ==============================================
//              METHODES DE RETOUR
// ==============================================
// �met le signal de cr�ation/modification termin�e avec les arguements collect�s dans la fenetre
void fenEntite::configTerminee() {
    QString nom = Nom->text();
    QString fig = Fig->text();
    int prio = Prio->value();
    QString camps = Camps->currentText();
    bool tabStat[VOCABULATEUR_NB_STATUT];
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        tabStat[i] = Status[i]->isChecked();

    if(e_Creation)
        emit creationTerminee(nom, fig, prio, camps, tabStat);
    else
        emit modifTerminee(nom, fig, prio, camps, tabStat);
    // afin de permettre l'ajout rapide de plusieurs entit�s, on ne quitte pas la fenetre lors de la cr�ation
    if(!e_Creation)    accept();
}




