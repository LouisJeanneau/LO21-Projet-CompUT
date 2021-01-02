#ifndef VUEPROGRAMME_H
#define VUEPROGRAMME_H
#include "fenetreprincipale.h"

class fenetrePrincipale;

class vueProgramme : public QWidget {
Q_OBJECT
    Persistence &persistence = Persistence::obtenirPersistence();
    QLineEdit *entreeAtomePG;
    QLineEdit *entreeProgramme;
    QPushButton *validerCreationPG;
    QHBoxLayout *layoutSaisiePG;
    QVBoxLayout *listeProgramme;
    QLabel *texteCreationProgramme;
    QLabel *texteProgrammeEnregistre;
    QTableWidget *tableProgramme;
    fenetrePrincipale *fenetrePrincipale;
    QLabel *texteSuppressionPG;
    QComboBox *choixSuppressionPG;
    QPushButton *validerSuppresionPG;
public:
explicit vueProgramme(QWidget *parent = 0);
    ~vueProgramme(){};
    void setFenetrePrincipale(class fenetrePrincipale* fenetrePrincipaleCopie){fenetrePrincipale = fenetrePrincipaleCopie;};
    class fenetrePrincipale *getFenetrePrincipale(){return fenetrePrincipale;};
    void refreshProgramme();
public slots:
void ajouterProgramme();
void recupererKey();
void appelRefreshProgramme();
};
#endif // VUEPROGRAMME_H
