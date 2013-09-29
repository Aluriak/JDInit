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
// retourne la chaine lue à la ligne indiquée du fichier
string vocabulateur::getVocab(int ligne) {
    return e_Vocab[ligne];
}






// ==============================================
//              METHODE
// ==============================================
// parcours le fichier de vocabulaire, et remplis les attributs de l'objet en conséquence
void vocabulateur::RechercheVocabulaire() {
    ifstream voc(FILE_VOCAB);
    // gestion erreur d'ouverture
    if(!voc) {
        FLUX_ERREUR("VOCABULATEUR", "Erreur d'ouverture du fichier File/Vocabulaire.Alk en lecture.");
        return;
    }

    string ligne(""), cont(""); // string contenant la ligne, et le mot de vocabulaire
    bool modeLecture = false; // vrai lorsqu'on commence à enregistrer un mot de vocabulaire
    int compteur = 0; // égal à la ligne actuellement traitée

    // parcours du fichier, du début à la fin, ou jusqu'à ce qu'on ait atteint le nombre de mot fixé par le vocabulaire
    while(getline(voc, ligne) && compteur < VOCABULATEUR_NB_MOT) {
        // parcours de la ligne
        for(unsigned int i = 0; i < ligne.size(); i++) {
            if(modeLecture) {
                cont += ligne[i]; // on ajoute le caractère lu au conteneur
            } else if(ligne[i] == ':') { // si pas en mode lecture, et qu'on voit le séparateur
                modeLecture = true;
            }
        }
        // si la chaine est valable, alors la case du tableau correspondant à la ligne actuelle est remplie par la chaine
        if(cont.size() != 0 && cont != " ") e_Vocab[compteur] = cont;

        // contrôle de la boucle
        compteur++; // on passe à la ligne suivant
        modeLecture = false; // on arrête de lire
        cont = ""; // le conteneur est vidé.
    }
}



