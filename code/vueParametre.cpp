#include "vueParametre.h"

vueParametre::vueParametre(QWidget *parent) :
        QWidget(parent) {
    setWindowTitle("Paramètres");
    setWindowModality(Qt::ApplicationModal);
    choixNb = new QSpinBox;
    messageParametre = new QLabel("Entrez le nombre d'étages de Pile à afficher :");
    layoutParametre = new QHBoxLayout;
    choixNb->setRange(0, 1000);
    choixNb->setSingleStep(1);
    choixNb->setValue(5);

    layoutParametre->addWidget(messageParametre);
    layoutParametre->addWidget(choixNb);
    setLayout(layoutParametre);

    QObject::connect(choixNb, SIGNAL(valueChanged(int)), this, SLOT(changerNbAfficherPile()));
}

void vueParametre::changerNbAfficherPile() {
    //QComputer fenetre = getComputer();
    unsigned int Number = choixNb->text().toInt();
    QMessageBox msgBox;
    //msgBox.setText(choixNb->text()+Number);
    //msgBox.exec();
    fenetrePrincipale->setNombreItemAAfficher(Number);
    fenetrePrincipale->refreshMethode();
}


vueParametre::~vueParametre() {
}
