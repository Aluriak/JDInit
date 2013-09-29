#ifndef VOCABULATEUR_H_INCLUDED
#define VOCABULATEUR_H_INCLUDED

#include "main.h"




// le vocabulateur lit, d�s sa cr�ation, le fichier FILE_VOCAB, et en retire des mots de vocabulaire.
//      Pour les obtenir, il suffit d'appeler les accesseurs du vocabulateur
// Au sein du fichier, il y a cinq lignes. Le vocabulateur lit ces ligne a partir du premier ':'.
//      Si il n'y a rien d'exploitable apr�s, il prend la cha�ne vide
//      Sinon, il s'agit du mot �quivalent � afficher dans le logiciel.
class vocabulateur {
    public:
    // constructeur
        vocabulateur();
    // accesseurs
        std::string getVocab(int); // retourne la chaine lue � la ligne indiqu�e du fichier
    private:
    // attributs
        std::string e_Vocab[VOCABULATEUR_NB_MOT]; // contient les mots lus dans le fichier
    // m�thodes
        void RechercheVocabulaire(); // parcours le fichier de vocabulaire, et remplis les attributs de l'objet en cons�quence
        void distributionVocabulaire(std::string tab[]); // modifie les attributs selon le tableau envoy� en argument (de taille VOCABULATEUR_NB_MOT)
};



#endif // VOCABULATEUR_H_INCLUDED
