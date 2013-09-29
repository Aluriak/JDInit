#ifndef VOCABULATEUR_H_INCLUDED
#define VOCABULATEUR_H_INCLUDED

#include "main.h"




// le vocabulateur lit, dés sa création, le fichier FILE_VOCAB, et en retire des mots de vocabulaire.
//      Pour les obtenir, il suffit d'appeler les accesseurs du vocabulateur
// Au sein du fichier, il y a cinq lignes. Le vocabulateur lit ces ligne a partir du premier ':'.
//      Si il n'y a rien d'exploitable après, il prend la chaîne vide
//      Sinon, il s'agit du mot équivalent à afficher dans le logiciel.
class vocabulateur {
    public:
    // constructeur
        vocabulateur();
    // accesseurs
        std::string getVocab(int); // retourne la chaine lue à la ligne indiquée du fichier
    private:
    // attributs
        std::string e_Vocab[VOCABULATEUR_NB_MOT]; // contient les mots lus dans le fichier
    // méthodes
        void RechercheVocabulaire(); // parcours le fichier de vocabulaire, et remplis les attributs de l'objet en conséquence
        void distributionVocabulaire(std::string tab[]); // modifie les attributs selon le tableau envoyé en argument (de taille VOCABULATEUR_NB_MOT)
};



#endif // VOCABULATEUR_H_INCLUDED
