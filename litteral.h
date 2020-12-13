#ifndef LITTERAL_H
#define LITTERAL_H

#endif // LITTERAL_H
#include <QString>
using namespace std;
//识别 创造
//动态分配 释放
//package "GroupeLitterale" {


//  class ConstructeurLitterale: public Litterale {
//    char[30] chaine;
//    public:
//      ConstructeurLitterale();
//    constructeur_entier;
//    constructeur_reel;
//    constructeur_atome;
//    constructeur_expression(Atome & a);
//  }


//ajouterAtome()


class Litterale {
public:
    virtual ~Litterale() = default;
    virtual QString versString() const = 0;
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
    ~Reel();
};

class Rationel: public Numerique{
    int if_simple=0;
    int numerateur;
    int denominateur; //不一样的要确定的才要记录
    //char slash;
public:

    //    void simplifier(int*n,int *d) {
    //      //if (denominateur == 1) // ou après  simplification ça devient un entier ：interpreteur doit le vérifier d＇ abord
    //      if(*n==1)return;//pas besion de simplifier
    //      for(int i=2;i<=*n&&i<=*d;i++)
    //      {
    //          if((*n)%i==0&&(*d)%i==0)
    //          {
    //            *n=(*n)/i;
    //            *d=(*d)/i;
    //            simplifier(&n,&d);
    //          }
    //      }
    int getNumerateur()const{return numerateur;}
    int getDenominateur()const{return denominateur;}
    int ifSimple()const{return if_simple;}
    Rationel(int n,int d)
    {
        simplifier(&n,&d);
        numerateur=n;
        denominateur=d;
    }
    ~Rationel();
};

class Entier : public Numerique{
    //char signe;
    int entier;
public:
    Entier(int i): entier(i) {}; //默认的是干嘛的
    int getEntier()const {return entier;}
    void negative() //operateur NEG
    {
        entier = -entier;
    }
    QString versString() const;
    ~Entier(); //什么时候不适用了
};

class Programme : public Litterale{
    //char crochet1,crochet2;
    QString programme;//y compris les sous-programme,il faut interpréter
    int longeur;
    int delimitateur;
    //Programme * sousProgramme = nullptr;
public:
    Programme(QString p)
    {
        strcpy(programme,p);
    }
    QString getProgramme()const {return programme;};
    ~Programme();
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
    int longeur;
    int delimitateur;
    int fonction=0; //indiquer le role joue:0:non associé（par defaut） 1 :identificateur de numerique 2:identificateur de programme
    Programme * p = nullptr;
    Numerique * n = nullptr; //au cas de bouton
    Atome * suivant=nullptr; //pour chercher:
    //Expression*??
public:
    QString getAtome()const {return atome;}
    int getfonction ()const{return fonction;}
    void Associer(Programme* pro = nullptr,Numerique* nu = nullptr){p=pro;n=nu;}//initialiser ou remplacer l'association
    Atome(QString a,int l)
    {
        strcpy(atome,a);
        longeur=l;
    }
    int ifDejaIdentifi(){return fonction==1||fonction==2 ;}; //sinon créer une expression???
    //    Remplace();
    int ifCorrectSyntaxe(QString a)
    {
        if(a[0]<'A'||a[0]>'Z')return 0;
        for(int i=1;a[i]!='\0';i++)
            if(a[i]<'A'||a[i]>'Z'||(a[i]<='9'&&a[i]>='0'))
                return 0;//pas Majuscule ,il faut rectifier

        return 1;
    }

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
    }
    //toString()
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


class Expression : public Litterale{
    //char guillmet1,guillmet2;
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

