#include "main.h"

using namespace std;


// =============================
//      INITIALISATION
// =============================
// supprime le contenu de la Table et ajoute la ligne de r�f�rence.
void fenetre::initialisation_Table() {
    // On efface toutes les lignes du tableau sauf la premi�re
    w_Table->setRowCount(1);
    // Cette premi�re ligne est la r�f�rence. Elle ne sera pas modifi�e lors du programme.
    //  on prend pas la premi�re case, car elle sera affich�e apr�s toutes les lignes, histoire d'afficher le nombre d'entit�s
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
            caseActuelle->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); // align� � gauche
        else
            caseActuelle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // align� au centre

        // gestion couleur
        QBrush background(Qt::gray); // cr�ation d'un background unis de couleur gris clair
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
// g�re le passage au tour suivant en modifiant le pointeur sur le joueur actuel
void fenetre::passageTourSuivant() {
    unsigned int nb_entite = liste_Entite.size();
    // protection contre les listes vides
    if(nb_entite == 0) return;
    // si le pointeur est � NULL, alors on prend le premier �l�ment de la liste
    if(w_Joueur == NULL) liste_Entite.front();
    // on localise l'entit� dont c'est actuellement le tour
    unsigned int ID;
    for(ID = 0; ID < nb_entite && liste_Entite[ID] != w_Joueur; ID++);

    // si on est � la derni�re entit�, ou si w_Joueur ne pointe pas d'entit�
    if(w_Joueur == liste_Entite[liste_Entite.size()-1]  ||  w_Joueur != liste_Entite[ID])
        w_Joueur = liste_Entite[0];
    else // sinon, on pointe l'entit� suivante dans le vector
        w_Joueur = liste_Entite[ID+1];

    // puis affichage de la table
    affichageTable();
}


// Modifie le pointeur vers le joueur pour qu'il pointe l'entit� s�lectionn�e par w_Selection
void fenetre::definirJoueur() {
    // protection contre la non s�lection
    if(w_Selection == NULL) return;

    int ligne = w_Selection->row();
    // protection contre la non s�lection : si la liste des items s�lectionn�s est vide ou si la ligne s�lectionn�e est la premi�re, ou n'est pas dans la table
    if(ligne <= 0)     return;
    // on a juste � mettre le pointeur w_Joueur sur l'�l�ment de la liste d'entit� correspondant � cette ligne
    w_Joueur = liste_Entite[ligne-1];

    // puis affichage de la table
    affichageTable();
}


// modifie le pointeur de s�lection d'entit� selon l'item point�
void fenetre::selectionEntite(QTableWidgetItem *item) {
    w_Selection = item;
    // si l'item est la premi�re ligne, ou en dehors de la table, les boutons sont d�sactiv�s, sinon ils ont activ�s
    if(item->row() <= 0)    validiteBouton(false);
    else                    validiteBouton(true);
}



// =============================
//      METHODES ANNEXES
// =============================
// recolore toutes les lignes de la table suivant le camp de l'entit� �tudi�e
void fenetre::colorerTable() {
    QBrush background(Qt::white); // cr�ation du brush contenant le fond.

    // boucle parcourant la table, en commancant par la seconde ligne (la premi�re est la ligne de r�f�rence, immuable)
    for(int i = 1; i < w_Table->rowCount(); i++) {
        // on r�cup�re la couleur en fonction du camps de l'entit�
        background.setColor(choixCouleurEntite(str2Qstr(liste_Entite[i-1]->getCamps())));
        // texture sp�ciale si il s'agit de l'entit� dont c'est le tour
        if(w_Joueur == liste_Entite[i-1])
            background.setStyle(PRGM_BRUSH_ENTITE_JOUEUR);
        // assignation de la couleur � toutes les cases de la ligne
        for(unsigned int y = 0; y < w_Colonnes.size(); y++)
            w_Table->item(i,y)->setBackground(background);
        background.setStyle(Qt::SolidPattern); // on enl�ve la texture
    }
}

// renvoit la couleur correspondant au camp envoy� en argument
QColor fenetre::choixCouleurEntite(QString camp) {
    QColor couleur;
    if(camp == vocab[VOC_PJ])                  // si l'entit� est un PJ
        couleur.setRgb(0,200,0,64);        // cr�ation d'un background unis de couleur verte
    else if(camp == vocab[VOC_ALLIE])             // si l'entit� est un alli�
        couleur.setRgb(0,0,200,64);        // cr�ation d'un background unis de couleur bleue
     else if(camp == vocab[VOC_ENNEMI])            // si l'entit� est un ennemi
        couleur.setRgb(200,0,0,64);       // cr�ation d'un background unis de couleur rouge
     else if(camp == vocab[VOC_AUTRE])            // si l'entit� est autre chose
        couleur.setRgb(200,200,0,64);      // cr�ation d'un background unis de couleur jaune
    return couleur;
}



// =============================
//      METHODES D'AFFICHAGE
// =============================
void fenetre::triageListeEntite() {
    int nb_entite = liste_Entite.size();
    if(nb_entite == 0 || nb_entite == 1) return; // aucun traitement n'est n�cessaire lorsqu'il n'y a qu'un �l�ment ou moins
    // premi�re �tape : on localise la plus grande priorit� avec la variable prioriteMax
    int prioriteMax = liste_Entite[0]->getPriorite();
    for(int i = 1; i < nb_entite; i++) {
        if(liste_Entite[i]->getPriorite() > prioriteMax)    prioriteMax = liste_Entite[i]->getPriorite();
    }

    // on conna�t d�sormais la priorit� maximum. Maintenant, on parcours la liste jusqu'� trouver cette priorit� maximum,
    //      et placer l'entit� trouv�e dans le vector interm�diaire. On effectue ce parcours de liste avec chaque valeur en dessous de prioriteMax
    vector<entite*> inter(0);
    for(; prioriteMax >= 0; prioriteMax--) { // pour toutes les valeurs de prioriteMax, de la + grand � la + petite
        for(int i = 0; i < nb_entite; i++) { // on lit le tableau dans son ensemble et on case dans l'interm�diaire ceux qu'on cherche
            if(liste_Entite[i]->getPriorite() == prioriteMax)   inter.push_back(liste_Entite[i]);
        }
    }

    // maintenant, on remplace les valeur de liste_Entite par celles de inter
    CopieContenuVector(inter, liste_Entite);
}



// ajoute � la table toutes les entit�s dans la liste, dans leur ordre d'apparition
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
                caseActuelle->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter); // align� � gauche
            else
                caseActuelle->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter); // align� au centre


            // insertion de l'item (fonction QTableWidget::setItem ( int row, int column, QTableWidgetItem * item ) )
            w_Table->setItem(i+1, y, caseActuelle);
        }
    }
}



