#ifndef VUEPROGRAMME_H
#define VUEPROGRAMME_H
#include "fenetreprincipale.h"

class vueProgramme : public QWidget {
Q_OBJECT
    QLineEdit *entreeAtomePG;
    QLineEdit *entreeProgramme;
    QPushButton *validerCreationPG;
    QHBoxLayout *layoutSaisiePG;
    QVBoxLayout *listeProgramme;
    QLabel *texteCreationProgramme;
    QLabel *texteProgrammeEnregistre;
    fenetrePrincipale *fenetrePrincipale;
public:
explicit vueProgramme(QWidget *parent = 0);
    ~vueProgramme(){};
    void setFenetrePrincipale(class fenetrePrincipale* fenetrePrincipaleCopie){fenetrePrincipale = fenetrePrincipaleCopie;};
    class fenetrePrincipale *getFenetrePrincipale(){return fenetrePrincipale;};
public slots:
void ajouterProgramme();
};

#endif // VUEPROGRAMME_H
