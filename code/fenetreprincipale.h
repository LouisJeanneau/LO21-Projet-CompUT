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
#include <QLCDNumber>
#include <QMap>
#include <QByteArray>
#include "Pile.h"
#include "Interpreteur.h"
#include "Litterale.h"
#include "Computer.h"
#include "Exception.h"
#include "Persistence.h"
#include "vueVariable.h"
#include "vueProgramme.h"
#include "vueParametre.h"

class vueParametre;
class vueProgramme;
class vueVariable;

class fenetrePrincipale : public QWidget
{
    Q_OBJECT
    QLineEdit *message;
    QTableWidget *vuePile;
    unsigned int nombreItemAAfficher;
    QLineEdit *commande;
    Pile& pile=Pile::obtenirPile();
    Controleur *controleur;
    vueParametre *vueParametre;
    vueVariable* vueVariable;
    vueProgramme* vueProgramme;
    Persistence* persistence;
    // Pour les vues
    QPushButton *boutonVariable;
    QPushButton *boutonProgramme;
    QPushButton *boutonParametre;
    // Pour le claviers
    QPushButton *afficherClavierCalculateur;
    QPushButton *afficherClavierVariable;
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
    //Pour l'affichage :
    QVBoxLayout* couche;
    QHBoxLayout* affichageClaviers;
    QHBoxLayout* placeClaviers;
    QGridLayout *clavierNumerique;
    QHBoxLayout *affichageVues;

    public:
    explicit fenetrePrincipale(QWidget *parent = 0);
    ~fenetrePrincipale() {
        //delete pile;
        delete controleur;
    }
    unsigned int getNombreItemAAfficher(){return nombreItemAAfficher;};
    void setNombreItemAAfficher(unsigned int i){nombreItemAAfficher = i;};
    fenetrePrincipale *getFenetrePrincipale(){return this;};
    void refreshMethode();
    void setVariable(QString atome,QString variable){persistence->setMapVariable(atome,variable);};
    QMap<QString,QString> getMapVariable(){return persistence->getMapVariable();};

    public slots:
    void refresh();
    void getNextCommande();
    void empile1(){commande->setText("1"); getNextCommande();};
    void empile2(){commande->setText("2"); getNextCommande();};
    void empile3(){commande->setText("3"); getNextCommande();};
    void empile4(){commande->setText("4"); getNextCommande();};
    void empile5(){commande->setText("5"); getNextCommande();};
    void empile6(){commande->setText("6"); getNextCommande();};
    void empile7(){commande->setText("7"); getNextCommande();};
    void empile8(){commande->setText("8"); getNextCommande();};
    void empile9(){commande->setText("9"); getNextCommande();};
    void empile0(){commande->setText("0"); getNextCommande();};
    void empilePLUS(){commande->setText("+"); getNextCommande();};
    void empileMOINS(){commande->setText("-"); getNextCommande();};
    void empileFOIS(){commande->setText("*"); getNextCommande();};
    void empileDIV(){commande->setText("/"); getNextCommande();};
    void empileCLEAR(){commande->clear();};
    void empileEVAL(){getNextCommande();}

    void affichageClavierCalculateur();

    void ouvertureVueVariable();
    void ouvertureVueProgramme();
    void ouvertureVueParametre();
};
#endif // FENETREPRINCIPALE_H
