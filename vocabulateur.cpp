#include "main.h"

using namespace std;




// ==============================================
//              CONSTRUCTEUR
// ==============================================
vocabulateur::vocabulateur() {
    // initialisation
    for(int i = 0; i < VOCABULATEUR_NB_MOT; i++)
        e_Vocab[i] = "";
    RechercheVocabulaire();
}





// ==============================================
//              ACCESSEUR
// ==============================================
// retourne la chaine lue � la ligne indiqu�e du fichier
string vocabulateur::getVocab(int ligne) {
    return e_Vocab[ligne];
}






// ==============================================
//              METHODE
// ==============================================
// parcours le fichier de vocabulaire, et remplis les attributs de l'objet en cons�quence
void vocabulateur::RechercheVocabulaire() {
    ifstream voc(FILE_VOCAB);
    // gestion erreur d'ouverture
    if(!voc) {
        FLUX_ERREUR("VOCABULATEUR", "Erreur d'ouverture du fichier File/Vocabulaire.Alk en lecture.");
        return;
    }

    string ligne(""), cont(""); // string contenant la ligne, et le mot de vocabulaire
    bool modeLecture = false; // vrai lorsqu'on commence � enregistrer un mot de vocabulaire
    int compteur = 0; // �gal � la ligne actuellement trait�e

    // parcours du fichier, du d�but � la fin, ou jusqu'� ce qu'on ait atteint le nombre de mot fix� par le vocabulaire
    while(getline(voc, ligne) && compteur < VOCABULATEUR_NB_MOT) {
        // parcours de la ligne
        for(unsigned int i = 0; i < ligne.size(); i++) {
            if(modeLecture) {
                cont += ligne[i]; // on ajoute le caract�re lu au conteneur
            } else if(ligne[i] == ':') { // si pas en mode lecture, et qu'on voit le s�parateur
                modeLecture = true;
            }
        }
        // si la chaine est valable, alors la case du tableau correspondant � la ligne actuelle est remplie par la chaine
        if(cont.size() != 0 && cont != " ") e_Vocab[compteur] = cont;

        // contr�le de la boucle
        compteur++; // on passe � la ligne suivant
        modeLecture = false; // on arr�te de lire
        cont = ""; // le conteneur est vid�.
    }
}



