#include "main.h"

using namespace std;


// ==============================================
//              CONSTRUCTEUR
// ==============================================
entite::entite(string nom, string figurine, int priorite, string camps, bool* stat) {
    e_Nom = nom;
    e_Figurine = figurine;
    e_Priorite = priorite;
    e_Camps = camps;
    for(int i = 0; i < VOCABULATEUR_NB_STATUT; i++)
        e_Statuts[i] = stat[i]; // les status sont remplis selon le tableau envoyé en arg()
}




// ==============================================
//              SURCHARGES D'OPERATEURS
// ==============================================
bool entite::operator<(entite &B) {
    if(getPriorite() < B.getPriorite())
        return true;
    return false;
}
bool entite::operator>(entite &B) {
    if(getPriorite() > B.getPriorite())
        return true;
    return false;
}
bool entite::operator==(entite &B) {
    if(getPriorite() == B.getPriorite())
        return true;
    return false;
}


// ==============================================
//              ACCESSEURS
// ==============================================
void entite::SetNom(string nom) {e_Nom = nom;}
string entite::getNom() {return e_Nom;}

void entite::SetFigurine(string figurine) {e_Figurine = figurine;}
string entite::getFigurine() {return e_Figurine;}

void entite::SetPriorite(int priorite) {e_Priorite = priorite;}
int entite::getPriorite() {return e_Priorite;}

void entite::SetCamps(string camps) {e_Camps = camps;}
string entite::getCamps() {return e_Camps;}

void entite::SetStatut(int numStatut, bool etat) {
    if(numStatut >= 0 && numStatut < VOCABULATEUR_NB_STATUT)
        e_Statuts[numStatut] = etat;
}

bool entite::getStatut(int numStatut) {
    if(numStatut >= 0 && numStatut < VOCABULATEUR_NB_STATUT)
        return e_Statuts[numStatut];
    return false;
}

