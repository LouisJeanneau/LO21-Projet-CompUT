#include"code/Litterale.h"
#include <QString>
#include "code/Pile.h"

QString Entier::versString() const {
    return QString::number(entier);
}

QString Reel::versString() const {
    return QString::number(reel);
}

QString Rationnel::versString() const {
    return QString::number(numerateur)+"/"+QString::number(denominateur);
}
QString Programme::versString() const {
    return "["+programme+"]";
}
QString Expression::versString() const {
    return """+this->atome->versString()+""";
}
QString Atome::versString() const {
    return atome;
}


Rationnel Rationnel::operator+(const Rationnel &r) const {
    return Rationnel(numerateur*r.denominateur + r.numerateur*denominateur, denominateur*r.denominateur);
}

void Rationnel::simplification() {
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (numerateur==0) { denominateur=1; return; }
    /* un denominateur ne devrait pas être 0;
    si c’est le cas, on sort de la méthode */
    if (denominateur==0) return;
    /* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=numerateur, b=denominateur;
    // on ne travaille qu’avec des valeurs positives...
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    // on divise le numerateur et le denominateur par le PGCD=a
    numerateur/=a; denominateur/=a;
    // si le denominateur est négatif, on fait passer le signe - au denominateur
    if (denominateur<0) { denominateur=-denominateur; numerateur=-numerateur; }
}

void Rationnel::setRationnel(int n, int d) {

    numerateur = n;
    if (d==0) {
        throw ComputerException("erreur : denominateur nul");
    }

    denominateur = d;

    simplification();
}

Item ConstructeurLitterale::distinguerConstruire(QString s) {
    int flag1=s.startsWith("[");//programme
    int flag2=s.startsWith("""");//expression
    int flag3=s.contains(".");//reel
    int flag4=s.contains("/");//rationnel
    int l=s.length();
    if(flag3)
    {
      int indexPoint=s.indexOf(".");
      int flag5=0;//la mantisse est suppoée =000...
      for(int i=indexPoint+1;i<l;i++)
       if(s[i]!=0)
          flag5=1;//la mantisse n'est pas equivalent a 000...
      if(flag5==0)
      {
        s.chop(s.length()-indexPoint);
        distinguerConstruire(s);//traité comme un entier
      }
    }
    int flag6=s.startsWith("-");
    int flag7=s.startsWith(".");//.56
    if(flag7)
        s="0"+s;


    if(flag6||(s[0]<='9'&&s[0]>='0'))//numerique
    {
        if(flag3==1)//reel
        {
            Litterale* temp = new Reel(s.toDouble());
            return Item(temp, "Reel");
            // return re;
        }
        else if(flag4==1)//rationnel
        {
            QString n1=s.section("/",0,0);
            QString d1=s.section("/",1,1);
            int n=n1.toInt();
            int d=d1.toInt();
            if (d != 1) {
                Litterale *temp = new Rationnel(n, d);
                return Item(temp, "Rationnel");
            }
            else {
                Litterale *temp = new Entier(n);
                return Item(temp, "Entier");
            }

        }
        else //entier
        {
            Litterale* temp = new Entier(s.toInt());
            return Item(temp, "Entier");

        }
    }

    else if(s[0]>='A'&&s[0]<='Z')//Atome
    {
        Litterale* temp = new Atome(s);
        return Item(temp, "Entier");

    }
    else if (flag1==1) //programme
    {
        Litterale* temp = new Programme(s.mid(1,l-2));
        return Item(temp, "Programme");
    }
    else if(flag2==1)//expression
    {
        Atome ae=Atome(s.mid(1,l-2));
        Litterale* temp = new Expression(&ae);
        return Item(temp, "Atome");
    }
    return Item(nullptr, "Vide");
}