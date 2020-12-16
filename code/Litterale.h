#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include<iostream>
using namespace std;
//package "GroupeLitterale" {


//  class ConstructeurLitterale: public Litterale {//string,distinguer le type
//    char[30] chaine;
//    public:
//    ConstructeurLitterale();
//    constructeur_entier;
//    constructeur_reel;
//    constructeur_atome;
//    constructeur_expression(Atome & a);
//  }




class Litterale {
public:
    virtual ~Litterale() = default;
    virtual QString versString() const = 0;
//    void afficher(std::ostream& f=std::cout)const
//    {
//        f << versString();
//    }
};

class Numerique:public Litterale{

};

class Reel : public Numerique{
    double reel;
    //char point;
public:
    explicit Reel(double d): reel(d) {};
    double getReel() const {return reel;}
    void negative(){reel=-reel;}; //l'operateur NEG???
    //simplifier();??
    QString versString() const;
    ~Reel() override = default;
};

class Rationnel: public Numerique{
    int if_simple=0;
    int numerateur;
    int denominateur;
    //char slash;
public:
    void simplifier(int*n,int *d) ;
    int getNumerateur()const{return numerateur;}
    int getDenominateur()const{return denominateur;}
    int ifSimple()const{return if_simple;}
    Rationnel(int* n,int* d)
    {
        simplifier(n,d);
        numerateur=*n;
        denominateur=*d;
    }
    QString versString() const;
    ~Rationnel() = default;
};

class Entier : public Numerique{
    int entier;
public:
    Entier(int i): entier(i) {};
    int getEntier()const {return entier;}
    void negative() //operateur NEG
    {
        entier = -entier;
    }
    QString versString() const;
    ~Entier() = default;
};

class Programme : public Litterale{
    //char crochet1,crochet2;
    QString programme;//y compris les sous-programme,il faut interpréter
    int delimitateur;
    //Programme * sousProgramme = nullptr;
public:
    Programme(QString s) : programme(std::move(s)) {}
    QString getProgramme()const {return programme;};
    ~Programme() = default;
    QString versString() const;
//    void afficherProgramme()
//    {
//        cout<<"["<<endl;
//        for(int i=0;programme[i]!='\0'&&i<=delimitateur;i++)
//            cout<<programme[i]<<endl;
//        if(l>delimitateur)
//            cout<<"...\n"<<endl;
//        cout<<"]"<<endl;
//    }
};


class Atome : public Litterale{
    QString atome;//[ ] pas compris
    int delimitateur;
    int fonction=0; //indiquer le role joue:0:non associé（par defaut） 1 :identificateur de numerique 2:identificateur de programme
    Programme * p = nullptr;
    Numerique * n = nullptr; //au cas de bouton
    //Atome * suivant=nullptr; //pour chercher:
    //Expression*??
public:
    QString getAtome()const {return atome;}
    int getfonction ()const{return fonction;}
    void Associer(Programme* pro = nullptr,Numerique* nu = nullptr){
        if(pro!=nullptr)
        {
            fonction=2;
            p=pro;}
        if(nu!=nullptr)
        {
            fonction=1;
            n=nu;
        }//initialiser ou remplacer l'association'
    }
    explicit Atome(QString s) : atome(std::move(s)) {}
    int ifDejaIdentifi(){return fonction==1||fonction==2 ;}; //sinon créer une expression???
//    int ifCorrectSyntaxe(QString a)
//    {
//        if(a[0]<'A'||a[0]>'Z')return 0;
//        for(int i=1;a[i]!='\0';i++)
//            if(a[i]<'A'||a[i]>'Z'||(a[i]<='9'&&a[i]>='0'))
//                return 0;//pas Majuscule ,il faut rectifier

//        return 1;
//    }

    int ifPredefini(QString a)//1:predefini,il faut rectifier
    {
        if(QString::compare(a,"DIV")||\
                QString::compare(a,"NEG")||\
                QString::compare(a,"AND")||\
                QString::compare(a,"OR")||\
                QString::compare(a,"NOT")||\
                QString::compare(a,"EVAL")||\
                QString::compare(a,"DUP")||\
                QString::compare(a,"DROP")||\
                QString::compare(a,"SWAP")||\
                QString::compare(a,"CLEAR")||\
                QString::compare(a,"IFT")||\
                QString::compare(a,"STO")||\
                QString::compare(a,"FORGET"))
            return 1;
        else return 0;
    }

//    void afficherAtome()
//    {
//        for(int i=0;atome[i]!='\0'&&i<=delimitateur;i++)
//            std::cout<<atome[i]<<endl;
//        if(l>delimitateur)
//            cout<<"...\n"<<endl;
//    }
    QString versString() const;
    ~Atome() {delete p;delete n;}//???
    void effacer(){p=nullptr;n=nullptr;}    //peuvent effacé par FORGET
};

//class ListeAtome{
//    Atome* debut;
//    ListeAtome(const ListeAtome &la) = delete;
//    ListeAtome& operator=(const ListeAtome &la) = delete;
//    static ListeAtome instance;

//public:

//    ListeAtome* ajouterAtome();
//};

class Expression : public Litterale{
    Atome * atome; //identifier
public:
    Expression(Atome* a): atome(a) {};
    ~Expression() {//??
        delete atome;
    }
//    void afficherExpression()
//    {
//        cout<<"'"<<endl;
//        atome->afficherAtome();
//        cout<<"'"<<endl;
//    }
    QString versString() const;
};

class ConstructeurLitterale{
public:
    static Litterale* distinguerConstruire(QString s);
};

#endif // LITTERAL_H

