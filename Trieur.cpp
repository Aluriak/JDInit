#include "main.h"

using namespace std;


// =============================
//      INITIALISATION
// =============================
// supprime le contenu de la Table et ajoute la ligne de référence.
void fenetre::initialisation_Table() {
    // On efface toutes les lignes du tableau sauf la première
    w_Table->setRowCount(1);
    // Cette première ligne est la référence. Elle ne sera pas modifiée lors du programme.
    //  on prend pas la première case, car elle sera affichée après toutes les lignes, histoire d'afficher le nombre d'entités
    QTableWidgetItem *caseActuelle = NULL;

    for(unsigned int i = 0; i < w_Colonnes.size(); i++) {
        if(w_Colonnes[i] == qstr2Str(vocab[VOC_NOM]))
            caseActuelle = new QTableWidgetItem(vocab[VOC_NOM]); // si c'est la colonne nom, on configure la colonne nom
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_FIGURINE]))
            caseActuelle = new QTableWidgetItem(vocab[VOC_FIGURINE]); // si c'est la colonne figurine, on configure la colonne figurine
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_PRIORITE]))
            caseActuelle = new QTableWidgetItem(vocab[VOC_PRIORITE]); // etc...
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_CAMP]))
            caseActuelle = new QTableWidgetItem(vocab[VOC_CAMP]); // etc...
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_STATUT]))
            caseActuelle = new QTableWidgetItem(vocab[VOC_STATUT]); // etc...

        // gestion alignement
        if(i == 0) // si c'est le nom
            caseActuelle->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); // aligné à gauche
        else
            caseActuelle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // aligné au centre

        // gestion couleur
        QBrush background(Qt::gray); // création d'un background unis de couleur gris clair
        caseActuelle->setBackground(background); // assignation


        // insertion de l'item (fonction QTableWidget::setItem ( int row, int column, QTableWidgetItem * item ) )
        w_Table->setItem(0, i, caseActuelle);

        // configuration des lageurs de colonnes
        if(w_Colonnes[i] == qstr2Str(vocab[VOC_NOM]))
            w_Table->setColumnWidth(i, LARGEUR_COLONNE_NOM);
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_FIGURINE]))
            w_Table->setColumnWidth(i, LARGEUR_COLONNE_FIG);
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_PRIORITE]))
            w_Table->setColumnWidth(i, LARGEUR_COLONNE_INI);
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_CAMP]))
            w_Table->setColumnWidth(i, LARGEUR_COLONNE_CAM);
        else if(w_Colonnes[i] == qstr2Str(vocab[VOC_STATUT]))
            w_Table->setColumnWidth(i, LARGEUR_COLONNE_STA);
    }
}






// =============================
//      PASSAGE TOUR (slot)
// =============================
// gère le passage au tour suivant en modifiant le pointeur sur le joueur actuel
void fenetre::passageTourSuivant() {
    unsigned int nb_entite = liste_Entite.size();
    // protection contre les listes vides
    if(nb_entite == 0) return;
    // si le pointeur est à NULL, alors on prend le premier élément de la liste
    if(w_Joueur == NULL) liste_Entite.front();
    // on localise l'entité dont c'est actuellement le tour
    unsigned int ID;
    for(ID = 0; ID < nb_entite && liste_Entite[ID] != w_Joueur; ID++);

    // si on est à la dernière entité, ou si w_Joueur ne pointe pas d'entité
    if(w_Joueur == liste_Entite[liste_Entite.size()-1]  ||  w_Joueur != liste_Entite[ID])
        w_Joueur = liste_Entite[0];
    else // sinon, on pointe l'entité suivante dans le vector
        w_Joueur = liste_Entite[ID+1];

    // puis affichage de la table
    affichageTable();
}


// Modifie le pointeur vers le joueur pour qu'il pointe l'entité sélectionnée par w_Selection
void fenetre::definirJoueur() {
    // protection contre la non sélection
    if(w_Selection == NULL) return;

    int ligne = w_Selection->row();
    // protection contre la non sélection : si la liste des items sélectionnés est vide ou si la ligne sélectionnée est la première, ou n'est pas dans la table
    if(ligne <= 0)     return;
    // on a juste à mettre le pointeur w_Joueur sur l'élément de la liste d'entité correspondant à cette ligne
    w_Joueur = liste_Entite[ligne-1];

    // puis affichage de la table
    affichageTable();
}


// modifie le pointeur de sélection d'entité selon l'item pointé
void fenetre::selectionEntite(QTableWidgetItem *item) {
    w_Selection = item;
    // si l'item est la première ligne, ou en dehors de la table, les boutons sont désactivés, sinon ils ont activés
    if(item->row() <= 0)    validiteBouton(false);
    else                    validiteBouton(true);
}



// =============================
//      METHODES ANNEXES
// =============================
// recolore toutes les lignes de la table suivant le camp de l'entité étudiée
void fenetre::colorerTable() {
    QBrush background(Qt::white); // création du brush contenant le fond.

    // boucle parcourant la table, en commancant par la seconde ligne (la première est la ligne de référence, immuable)
    for(int i = 1; i < w_Table->rowCount(); i++) {
        // on récupère la couleur en fonction du camps de l'entité
        background.setColor(choixCouleurEntite(str2Qstr(liste_Entite[i-1]->getCamps())));
        // texture spéciale si il s'agit de l'entité dont c'est le tour
        if(w_Joueur == liste_Entite[i-1])
            background.setStyle(PRGM_BRUSH_ENTITE_JOUEUR);
        // assignation de la couleur à toutes les cases de la ligne
        for(unsigned int y = 0; y < w_Colonnes.size(); y++)
            w_Table->item(i,y)->setBackground(background);
        background.setStyle(Qt::SolidPattern); // on enlève la texture
    }
}

// renvoit la couleur correspondant au camp envoyé en argument
QColor fenetre::choixCouleurEntite(QString camp) {
    QColor couleur;
    if(camp == vocab[VOC_PJ])                  // si l'entité est un PJ
        couleur.setRgb(0,200,0,64);        // création d'un background unis de couleur verte
    else if(camp == vocab[VOC_ALLIE])             // si l'entité est un allié
        couleur.setRgb(0,0,200,64);        // création d'un background unis de couleur bleue
     else if(camp == vocab[VOC_ENNEMI])            // si l'entité est un ennemi
        couleur.setRgb(200,0,0,64);       // création d'un background unis de couleur rouge
     else if(camp == vocab[VOC_AUTRE])            // si l'entité est autre chose
        couleur.setRgb(200,200,0,64);      // création d'un background unis de couleur jaune
    return couleur;
}



// =============================
//      METHODES D'AFFICHAGE
// =============================
void fenetre::triageListeEntite() {
    int nb_entite = liste_Entite.size();
    if(nb_entite == 0 || nb_entite == 1) return; // aucun traitement n'est nécessaire lorsqu'il n'y a qu'un élément ou moins
    // première étape : on localise la plus grande priorité avec la variable prioriteMax
    int prioriteMax = liste_Entite[0]->getPriorite();
    for(int i = 1; i < nb_entite; i++) {
        if(liste_Entite[i]->getPriorite() > prioriteMax)    prioriteMax = liste_Entite[i]->getPriorite();
    }

    // on connaît désormais la priorité maximum. Maintenant, on parcours la liste jusqu'à trouver cette priorité maximum,
    //      et placer l'entité trouvée dans le vector intermédiaire. On effectue ce parcours de liste avec chaque valeur en dessous de prioriteMax
    vector<entite*> inter(0);
    for(; prioriteMax >= 0; prioriteMax--) { // pour toutes les valeurs de prioriteMax, de la + grand à la + petite
        for(int i = 0; i < nb_entite; i++) { // on lit le tableau dans son ensemble et on case dans l'intermédiaire ceux qu'on cherche
            if(liste_Entite[i]->getPriorite() == prioriteMax)   inter.push_back(liste_Entite[i]);
        }
    }

    // maintenant, on remplace les valeur de liste_Entite par celles de inter
    CopieContenuVector(inter, liste_Entite);
}



// ajoute à la table toutes les entités dans la liste, dans leur ordre d'apparition
void fenetre::remplissageTable() {
    QTableWidgetItem *caseActuelle = NULL;

    for(unsigned int i = 0; i < liste_Entite.size(); i++) {
        for(unsigned int y = 0; y < w_Colonnes.size(); y++) {
            if(w_Colonnes[y] == qstr2Str(vocab[VOC_NOM]))
                caseActuelle = new QTableWidgetItem(str2Qstr(liste_Entite[i]->getNom())); // si c'est le premier de la ligne, on prend le nom
            else if(w_Colonnes[y] == qstr2Str(vocab[VOC_FIGURINE]))
                caseActuelle = new QTableWidgetItem(str2Qstr(liste_Entite[i]->getFigurine())); // si c'est le second de la ligne, on prend la figurine
            else if(w_Colonnes[y] == qstr2Str(vocab[VOC_PRIORITE]))
                caseActuelle = new QTableWidgetItem(str2Qstr(num2str(liste_Entite[i]->getPriorite()))); // etc...
            else if(w_Colonnes[y] == qstr2Str(vocab[VOC_CAMP]))
                caseActuelle = new QTableWidgetItem(str2Qstr(liste_Entite[i]->getCamps())); // etc...
            else if(w_Colonnes[y] == qstr2Str(vocab[VOC_STATUT]))
                caseActuelle = new QTableWidgetItem(str2Qstr(getStatut(liste_Entite[i]))); // etc...

            // gestion alignement
            if(y == 0) // si c'est le nom
                caseActuelle->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); // aligné à gauche
            else
                caseActuelle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // aligné au centre


            // insertion de l'item (fonction QTableWidget::setItem ( int row, int column, QTableWidgetItem * item ) )
            w_Table->setItem(i+1, y, caseActuelle);
        }
    }
}



