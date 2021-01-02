#ifndef VUEPARAMETRE_H
#define VUEPARAMETRE_H

#include "fenetreprincipale.h"

class vueParametre : public QWidget {
Q_OBJECT
    QLabel *messageParametre;
    QSpinBox *choixNb;
    QHBoxLayout *layoutParametre;
    fenetrePrincipale *fenetrePrincipale;
public:
    explicit vueParametre(QWidget *parent = 0);

    ~vueParametre();

    void setFenetrePrincipale(
            class fenetrePrincipale *fenetrePrincipaleCopie) { fenetrePrincipale = fenetrePrincipaleCopie; };

    class fenetrePrincipale *getFenetrePrincipale() { return fenetrePrincipale; };
public slots:

    void changerNbAfficherPile();
};

#endif // VUEPARAMETRE_H
