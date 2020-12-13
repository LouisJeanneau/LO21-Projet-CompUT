#ifndef LO21_H_INCLUDED
#define LO21_H_INCLUDED
#include<string.h>

#endif // LO21_H_INCLUDED
using namespace std;
//识别 创造
//动态分配 释放
//package "GroupeLitterale" {
//
//  class Litterale {
//    char[30] str;
//    int *
//    double reel;
//    Atome * nom = nullptr;
//    public:
//      //virtual bouton();
//      distinct(); //识别
//    //virtual empiler();
//    //virtual memoriser();
//    virtual~Litterale(); //DROP
//
//  }

//  class ConstructeurLitterale: public Litterale {
//    char[30] chaine;
//    public:
//      ConstructeurLitterale();
//    constructeur_entier;
//    constructeur_reel;
//    constructeur_atome;
//    constructeur_expression(Atome & a);
//  }

  class Atome: public Litterale {
    char atome[30];//[ ] pas compris
    int longeur;
    int delimitateur;
    int fonction=0; //indiquer le role joue:0:non associé（par defaut） 1 :identificateur de numerique 2:identificateur de programme
    Programme * p = nullptr;
    Numérique * n = nullptr; //au cas de bouton
    Atome * suivant=nullptr; //pour chercher:
    //Expression*??
public:
    char* getAtome()const {return atome;}
    int getfonction ()const{return fonction;}
    void Associer(Programme* pro = nullptr,Numérique* nu = nullptr){p=pro;n=nu;}//initialiser ou remplacer l'association
    Atome(char* a,int l)
    {
        strcpy(atome,a);
        longeur=l;
    }
    int ifDejaIdentifi(return fonction==1||fonction==2); //sinon créer une expression???
//    Remplace();
    int ifCorrectSyntaxe(char* a)
    {
        if(a[0]<'A'||a[0]>'Z')return 0;
        for(int i=1;a[i]!='\0';i++)
        if(a[i]<'A'||a[i]>'Z'||(a[i]<='9'&&a[i]>='0'))
        return 0;//pas Majuscule ,il faut rectifier

        return 1;
    }

    int ifPredefini(char* a)//1:predefini,il faut rectifier
    {
        if(strcmp(a,"DIV")||\
        strcmp(a,"NEG")||\
        strcmp(a,"AND")||\
        strcmp(a,"OR")||\
        strcmp(a,"NOT")||\
        strcmp(a,"EVAL")||\
        strcmp(a,"DUP")||\
        strcmp(a,"DROP")||\
        strcmp(a,"SWAP")||\
        strcmp(a,"CLEAR")||\
        strcmp(a,"IFT")||\
        strcmp(a,"STO")||\
        strcmp(a,"FORGET"))
        return 1;
    }
    //toString()
    void afficherAtome()
    {
        for(int i=0;atome[i]!='\0'&&i<=delimitateur;i++)
        cout<<atome[i]<<endl;
        if(l>delimitateur)
        cout<<"...\n"<<endl;
    }
    ~Atome() {delete p;delete n;}//???
    void effacer(){p=nullptr;n=nullptr;}    //peuvent effacé par FORGET
  }


    //ajouterAtome()

  class Expression {
    //char guillmet1,guillmet2;
    Atome * atome; //identifier
public:
    Expression(Atome* a): atome(a) {};
    ~Expression() {//??
      delete atome;
    }
    void afficherExpression()
    {
        cout<<"'"<<endl;
       atome->afficherAtome();
        cout<<"'"<<endl;
    }
  }

  //    class Numerique:public Litterale{   //inutile??
  //
  //    }

  class Reel: public Numerique {
    double reel;
    //char point;
public:
    Reel(double d): val(d) {};
    double getReel() const {return reel;}
    void negative():val(-val){}; //l'operateur NEG???
    //simplifier();
    ~Reel();
  }

  class Rationel: public Numerique {
    int if_simple=0;
    int numerateur;
    int denominateur; //不一样的要确定的才要记录
    //char slash;
public:

    void simplifier(int *n,int *d) {
      //if (denominateur == 1) // ou après  simplification ça devient un entier ：interpreteur doit le vérifier d＇ abord
      if(*n==1)return;//pas besion de simplifier
      for(int i=2;i<=*n&&i<=*d;i++)
      {
          if((*n)%i==0&&(*d)%i==0)
          {
            *n=(*n)/i;
            *d=(*d)/i;
            simplifier(*n,*d);
          }
      }

    }
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
  }

  class Entier: public Numerique {
    //char signe;
    int entier;
public:
    Entier(int i): entier(i) {}; //默认的是干嘛的
    int getEntier()const {return entier;}
    void negative() //operateur NEG
    {
      entier = -entier;
    }
    ~Entier(); //什么时候不适用了
  }

  class Programme: public Litterale {
    //char crochet1,crochet2;
    char[30] programme;//y compris les sous-programme,il faut interpréter
    int longeur;
    int delimitateur;
    //Programme * sousProgramme = nullptr;
public:
    Programme(char* p)
    {
        strcpy(programme,p);
    }
    char* getProgramme()const {return programme;};
    ~Programme();
    void afficherProgramme()
    {
        cout<<"["<<endl;
        for(int i=0;programme[i]!='\0'&&i<=delimitateur;i++)
        cout<<programme[i]<<endl;
        if(l>delimitateur)
        cout<<"...\n"<<endl;
        cout<<"]"<<endl;
    }
  }

}
//
//
//class Item{
//
//}
//
//package "GroupeOperateur" {
//
//    class Operateur{
//
//    }
//
//}
//
//class Pile{
//
//}
//
//class Interpreter{
//
//}
//
//class Controleur{
//
//}
//
//class Persistance{
//
//}
//
//package "groupeAffichage" {
//
//    class Affichage{
//
//    }
//
//    class Qt {
//
//    }
//
//}

//Litterale <|-- Programme
//Litterale <|-- Numerique
//Litterale <|-- Expression
//Litterale <|-- Atome
//Numerique <|-- Reel
//Numerique <|-- Rationel
//Numerique <|-- Entier
//
//
//ConstructeurLitterale *-- Litterale
//Item *-- Operateur
//Item *-- Litterale
//Pile o-- Item
//Pile --> Interpreter
//Interpreter --> Controleur
//Pile --> Controleur
//Persistance --> Controleur
//Controleur --> Affichage
//Affichage --> Qt
//
//@endumleffacé p
