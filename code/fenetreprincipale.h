#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QDebug>
#include <QPushButton>
#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QMap>
#include <QSignalMapper>
#include <QComboBox>
#include <QShortcut>
#include <QValidator>
#include <QRegularExpression>
#include <QIcon>
#include "Pile.h"
#include "Interpreteur.h"
#include "Litterale.h"
#include "Exception.h"
#include "Persistance.h"
#include "vueVariable.h"
#include "vueProgramme.h"
#include "vueParametre.h"
#include "Sauvegarde.h"

class vueParametre;

class vueProgramme;

class vueVariable;

class Sauvegarde;

class fenetrePrincipale : public QWidget {
Q_OBJECT
    QLineEdit *message;
    QTableWidget *vuePile;
    int nombreItemAAfficher;
    QLineEdit *commande;
    Pile &pile = Pile::obtenirPile();
    Persistance &persistance = Persistance::obtenirPersistance();
    //Controleur *controleur;
    Sauvegarde *sauvegarde;

    Interpreteur *refIntp;
    vueParametre *vueParametre;
    vueVariable *vueVariable;
    vueProgramme *vueProgramme;
    // Pour les vues
    QPushButton *boutonVariable;
    QPushButton *boutonProgramme;
    QPushButton *boutonParametre;
    // Pour le claviers
    QPushButton *afficherClavierCalculateur;
    QPushButton *afficherClavierVariable;
    QPushButton *cacherClavierCalculateur;
    QPushButton *cacherClavierVariable;
    QPushButton *bouton0;
    QPushButton *bouton1;
    QPushButton *bouton2;
    QPushButton *bouton3;
    QPushButton *bouton4;
    QPushButton *bouton5;
    QPushButton *bouton6;
    QPushButton *bouton7;
    QPushButton *bouton8;
    QPushButton *bouton9;
    QPushButton *boutonCLEAR;
    QPushButton *boutonEVAL;
    QPushButton *boutonPLUS;
    QPushButton *boutonMOINS;
    QPushButton *boutonFOIS;
    QPushButton *boutonDIVISER;
    //Clavier Variable :
    QTableWidget *tableBoutonVariableProgramme;
    //Pour l'affichage :
    QVBoxLayout *couche;
    QHBoxLayout *affichageClaviers;
    QHBoxLayout *placeClaviers;
    QGridLayout *clavierNumerique;
    QHBoxLayout *affichageVues;

public:
    fenetrePrincipale(QWidget *parent = 0);

    ~fenetrePrincipale() = default;

    int getNombreItemAAfficher() { return nombreItemAAfficher; };

    void setNombreItemAAfficher(int i) { nombreItemAAfficher = i; };

    fenetrePrincipale *getFenetrePrincipale() { return this; };

    void refreshMethode();

    void creerNouveauBoutonVariable(int i, QString key, QString value);

    void creerNouveauBoutonProgramme(int i, QString key, QString value);

    QLineEdit *obtenirCommande() { return commande; };

    void focusCommande() { commande->setFocus(); }

public slots:

    void refresh();

    void getNextCommande();

    void empile_1() {
        commande->setText("1");
        getNextCommande();
    };

    void empile_2() {
        commande->setText("2");
        getNextCommande();
    };

    void empile_3() {
        commande->setText("3");
        getNextCommande();
    };

    void empile_4() {
        commande->setText("4");
        getNextCommande();
    };

    void empile_5() {
        commande->setText("5");
        getNextCommande();
    };

    void empile_6() {
        commande->setText("6");
        getNextCommande();
    };

    void empile_7() {
        commande->setText("7");
        getNextCommande();
    };

    void empile_8() {
        commande->setText("8");
        getNextCommande();
    };

    void empile_9() {
        commande->setText("9");
        getNextCommande();
    };

    void empile_0() {
        commande->setText("0");
        getNextCommande();
    };

    void empile_PLUS() {
        commande->setText("+");
        getNextCommande();
    };

    void empile_MOINS() {
        commande->setText("-");
        getNextCommande();
    };

    void empile_FOIS() {
        commande->setText("*");
        getNextCommande();
    };

    void empile_DIV() {
        commande->setText("/");
        getNextCommande();
    };

    void empile_CLEAR() {
        commande->setText("CLEAR");
        getNextCommande();
    };

    void empile_EVAL() {
        commande->setText("EVAL");
        getNextCommande();
    }

    void empileProgramme(QString valeur) {
        valeur.chop(1);
        valeur.remove(0, 1);
        commande->setText(valeur);
        getNextCommande();
    };

    void empileVariable(QString valeur) {
        commande->setText(valeur);
        getNextCommande();
    };

    void affichageClavierCalculateur();

    void affichageClavierVariable();

    void cacheClavierVariable();

    void cacheClavierCalculateur();

    void ouvertureVueVariable();

    void ouvertureVueProgramme();

    void ouvertureVueParametre();

    void refreshTableVariableProgramme();

    void slotFocusCommande() { commande->setFocus(); }

    void fermetureDerniereFenetre();

};

#endif // FENETREPRINCIPALE_H
