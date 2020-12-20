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

class fenetrePrincipale : public QWidget
{

    Q_OBJECT
    QLineEdit *message;
    QTableWidget *vuePile;
    unsigned int NbItemAAfficher;
    QLineEdit *commande;
    Pile& pile=Pile::obtenirPile();
    Controleur *controleur;
    vueParametre *vue_param;
    vueVariable *vue_variable;
    vueProgramme *vue_programme;
    Persistence *persistence;
    // Pour les vues
    QPushButton *bouton_Variable;
    QPushButton *bouton_Programme;
    QPushButton *bouton_Parametre;
    // Pour le claviers
    QPushButton *afficherClavierCalculateur;
    QPushButton *afficherClavierVariable;
    QPushButton *bouton_0;
    QPushButton *bouton_1;
    QPushButton *bouton_2;
    QPushButton *bouton_3;
    QPushButton *bouton_4;
    QPushButton *bouton_5;
    QPushButton *bouton_6;
    QPushButton *bouton_7;
    QPushButton *bouton_8;
    QPushButton *bouton_9;
    QPushButton *bouton_CLEAR;
    QPushButton *bouton_EVAL;
    QPushButton *bouton_PLUS;
    QPushButton *bouton_MOINS;
    QPushButton *bouton_FOIS;
    QPushButton *bouton_DIV;
    //Pour l'affichage :
    QVBoxLayout* couche;
    QHBoxLayout* affichageClaviers;
    QHBoxLayout* placeClaviers;
    QGridLayout *clavierNumerique;
    QHBoxLayout *layout_vues;

    public:
    explicit fenetrePrincipale(QWidget *parent = 0);
    ~fenetrePrincipale() {
        //delete pile;
        delete controleur;
    }
    unsigned int getNombreItemAAfficher(){return NbItemAAfficher;};
    void setNombreItemAAfficher(unsigned int i){NbItemAAfficher = i;};
    fenetrePrincipale *getComputer(){return this;};
    void refreshMethode();
    void setVariable(QString atome,QString variable){persistence->setMapVariable(atome,variable);};
    QMap<QString,QString> getMapVariable(){return persistence->getMapVariable();};

    public slots:
    void refresh();
    void getNextCommande();
    void empile_1(){commande->setText("1"); getNextCommande();};
    void empile_2(){commande->setText("2"); getNextCommande();};
    void empile_3(){commande->setText("3"); getNextCommande();};
    void empile_4(){commande->setText("4"); getNextCommande();};
    void empile_5(){commande->setText("5"); getNextCommande();};
    void empile_6(){commande->setText("6"); getNextCommande();};
    void empile_7(){commande->setText("7"); getNextCommande();};
    void empile_8(){commande->setText("8"); getNextCommande();};
    void empile_9(){commande->setText("9"); getNextCommande();};
    void empile_0(){commande->setText("0"); getNextCommande();};
    void empile_PLUS(){commande->setText("+"); getNextCommande();};
    void empile_MOINS(){commande->setText("-"); getNextCommande();};
    void empile_FOIS(){commande->setText("*"); getNextCommande();};
    void empile_DIV(){commande->setText("/"); getNextCommande();};
    void empile_CLEAR(){commande->clear();};
    void empile_EVAL(){getNextCommande();}

    void affichageClavierCalculateur();

    void ouverture_vue_variable();
    void ouverture_vue_programme();
    void ouverture_vue_parametre();
};
#endif // FENETREPRINCIPALE_H
