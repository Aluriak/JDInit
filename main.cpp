#include "main.h"

using namespace std;



// =============================
//      MAIN
// =============================
int main(int argc, char *argv[]) {
    // vider le fichier d'erreur
    ofstream err(FILE_ERR);
    err.close();
    // QApplication
    QApplication app(argc, argv);
    // gestion du splashscreen
    QPixmap pixmap(PRGM_SPLASH_SCREEN); // chargement de l'image
    if(pixmap.isNull()) // si l'image n'a pas �t� charg�e
    FLUX_ERREUR("MAIN:", "L'image Img/SplashScreen.png n'a pas �t� charg�e");
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint); // cr�ation du splashscreen avec l'image
    splash.show(); // on montre le splashscreen
    //app.processEvents(); // utiliser un thread pour optimiser le temps de chargement (inutile ici)

    fenetre w;
    w.show();
    splash.finish(&w); // s'arr�ter lorsque la fen�tre w est pr�te
    return app.exec();
 }




// =============================
//      FONCTIONS ANNEXES
// =============================
// renvois le nombre �crit en format ascii-cha�ne, ou 0 si c'est pas un nombre
int str2num(string str) {
    int var = 0;

    // boucle de v�rification
    for(unsigned int i = 0; i < str.size(); i++)     {
        if(str[i] < 48 || str[i] > 57)
            return 0; // si c'est pas un nombre en ASCII, on retourne 0.
    }

    // deuxi�me boucle : cette fois-ci on lit vraiment le nombre
    for(unsigned int i = 0; i < str.size(); i++)     {
        var += (str[i] - 48) * pow(10, str.size() - (i+1)); // on ajoute progressivement � var les bonne valeurs.
    }
    return var;
}


// renvois a^b
int pow(int a, int b) {
    int result = 1;
    while(b) {
        result *= a;
        b--;
    }
    return result;
}

// renvois sous forme de string le nombre envoy� en argument
string num2str(int nb) {
    // cr�er un flux de sortie
    ostringstream oss;
    // �crire un nombre dans le flux
    oss << nb;
    // r�cup�rer une cha�ne de caract�res
    return oss.str();
}

// renvois la cha�ne sous forme de QString
QString str2Qstr(string str) {
    QString inter("");

    for(unsigned int i = 0; i < str.size(); i++)     {
        inter += str[i];
    }
    return inter;
}


// renvois la QString sous forme de string
string qstr2Str(QString str) {
    string inter("");
    inter = str.toStdString();
    return inter;
}


// copie dans dest les valeur de src
void CopieContenuVector(vector<entite*> &src, vector<entite*> &dest) {
    dest.resize(0); // on vide la destination
    // on remplie !
    for(unsigned int i = 0; i < src.size(); i++) {
        dest.push_back(src[i]);
    }
}


// inscrit dans le fichier d'erreur les erreurs re�ues en argument
void FLUX_ERREUR(string source, string erreur) {
    ofstream err(FILE_ERR, ios::app);
    err << source << ": " << erreur << endl;
    err.close();
}

