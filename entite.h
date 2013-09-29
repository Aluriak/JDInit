#ifndef ENTITE_H_INCLUDED
#define ENTITE_H_INCLUDED

#include "main.h"


class entite {
    public:
    // Constructeur
        entite(std::string nom, std::string figurine, int priorite, std::string camps, bool* stat);

    // Accesseurs
        void SetNom(std::string nom);
            std::string getNom();
        void SetFigurine(std::string figurine);
            std::string getFigurine();
        void SetPriorite(int priorite);
            int getPriorite();
        void SetCamps(std::string camps);
            std::string getCamps();
        void SetStatut(int numStatut, bool etat);
            bool getStatut(int numStatut);

    // Surcharge d'opérateurs
        bool operator<(entite &B);
        bool operator>(entite &B);
        bool operator==(entite &B);
    private:
    // Attributs
        std::string e_Nom;
        std::string e_Figurine;
        int e_Priorite;
        std::string e_Camps;
        bool e_Statuts[VOCABULATEUR_NB_STATUT];
};



#endif // ENTITE_H_INCLUDED
